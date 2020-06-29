#include "stdafx.h"
#include "Sniper.h"
//#include "GameManager.h"
#include "GunGenerator.h"
#include "GameCamera.h"

Sniper::Sniper()
{
	m_model.Init(L"Assets/modelData/sniper_rifle.cmo");
	m_gunGen = g_goMgr.FindGameObject<GunGenerator>(gungenerator);
	m_gunShot.Init(L"Assets/sound/sniperS.wav");
	m_sampleEffect = Effekseer::Effect::Create(
		g_goMgr.GetEffekseerManager(),
		(const EFK_CHAR*)L"Assets/effect/happou.efk"
	);
	m_aim.Init(L"Resource/sprite/SR_scope.dds", FRAME_BUFFER_W, FRAME_BUFFER_H);
	SetPostRenderPriority(true);
	m_ammo = m_gunGen->GetGunAmmo();
	m_loading = m_gunGen->GetGunLoading();
}


Sniper::~Sniper()
{
	m_gunGen->SetGunAmmo(m_ammo);
	m_gunGen->SetGunLoading(m_loading);
}

void Sniper::Update()
{
	GunUpdate(
		&m_positon,
		&m_rotation,
		&m_ammo,
		&m_loading,
		&m_maxLoading,
		&m_bulletIntervalTime,
		&m_bulletMoveSpeed,
		&m_reaction,
		&m_reloadTime,
		&m_aimingPos,
		&m_notAimPos
	);
	m_model.UpdateWorldMatrix(m_positon, m_rotation, m_scale);
}
void Sniper::SetRegistShadowCaster()
{
	g_goMgr.GetShadowMap()->RegistShadowCaster(&m_model);
}
void Sniper::Render()
{
	if (m_flug != true) {
		m_model.Draw(
			enRenderMode_Normal,
			g_camera3D.GetViewMatrix(),
			g_camera3D.GetProjectionMatrix()
		);
	}
}
void Sniper::PostRender()
{
	if (m_flug != false) {
		m_aim.Draw();
	}
	GunPostRender(
		&m_reloadTime,
		&m_ammo,
		&m_loading,
		&m_maxLoading
	);
}
void Sniper::OnShot(CVector3* position, CQuaternion* rotation)
{
	//音を再生。
	m_gunShot.Stop();
	m_gunShot.Play(false);
	
	g_goMgr.GetEffekseerManager()->StopEffect(m_playEffectHandle);
	//再生。
	CVector3 p = *position;
	p.y += 5.0f;
	CVector3 effectPos = p;
	CVector3 pos = m_gameCam->GetToTargetPos();
	pos.Normalize();
	effectPos += pos * 250.0f;

	auto effMgr = g_goMgr.GetEffekseerManager();
	m_playEffectHandle = effMgr->Play(
		m_sampleEffect,
		0.0f,
		0.0f,
		0.0f
	);
	//カメラの回転行列を求める。
	CMatrix mCameraRot;
	//カメラ行列の逆行列はカメラのワールド行列。
	mCameraRot.Inverse(g_camera3D.GetViewMatrix());
	//
	mCameraRot.m[3][0] = effectPos.x;
	mCameraRot.m[3][1] = effectPos.y;
	mCameraRot.m[3][2] = effectPos.z;

	Effekseer::Matrix43 effMat;
	for (int x = 0; x < 4; x++) {
		for (int y = 0; y < 3; y++) {
			effMat.Value[x][y] = mCameraRot.m[x][y];
		}
	}

	effMgr->SetBaseMatrix(m_playEffectHandle, effMat);
	
}
void Sniper::Aim(CVector3* position, CQuaternion* rotation, CVector3* aimingPos, CVector3* notAimPos)
{
	*position = m_gameCam->GetPosition();
	CQuaternion PosRot = *rotation;
	m_flug = false;
	//エイムしているときの銃のローカル座標。
	CVector3 aimPos = *aimingPos;
	//エイムしていないときの銃のローカル座標。
	CVector3 notaimPos = *notAimPos;

	m_gameCam->SetGameCameraViewAngle(60.0f);

	if (g_pad->IsPress(enButtonLB1)) {
		//エイムしている。
		PosRot.Multiply(aimPos);
		PosRot.Multiply(notaimPos);

		//エイムしていないときの銃のローカル座標から、
		//エイムしているときの銃のローカル座標に向かうベクトルを求める。
		m_aimMoveSpeed = aimPos - notaimPos;
		m_aimMoveSpeed /= DIVIDE_NUM;

		if (m_count < (int)DIVIDE_NUM) {
			//m_countがDIVIDE_NUMより少ないなら移動する。
			m_gunLocalPosition += m_aimMoveSpeed;
			m_gameCam->SetRotSpeed(0.1f);
			m_count++;
		}
		else {
			m_gunLocalPosition = *aimingPos;
			PosRot.Multiply(m_gunLocalPosition);
			m_gameCam->SetGameCameraViewAngle(6.0f);
			m_flug = true;
		}
	}
	else {//エイムしていない。
		if (m_count > 0) {
			//m_countが0より多いなら移動する。
			PosRot.Multiply(aimPos);
			PosRot.Multiply(notaimPos);

			m_aimMoveSpeed = aimPos - notaimPos;
			m_aimMoveSpeed /= DIVIDE_NUM;
			m_gunLocalPosition -= m_aimMoveSpeed;
			m_gameCam->SetRotSpeed(3.0f);
			m_count--;
		}
		else {
			m_gunLocalPosition = *notAimPos;
			PosRot.Multiply(m_gunLocalPosition);
		}
	}
	*position += m_gunLocalPosition;
}
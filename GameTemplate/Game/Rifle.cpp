#include "stdafx.h"
#include "Rifle.h"
#include "GameCamera.h"

Rifle::Rifle()
{
	//モデルをロード。
	m_model.Init(L"Assets/modelData/Arifle.cmo");
	//撃った時の音をロード。
	m_gunShot.Init(L"Assets/sound/raifulS.wav");
	//撃った時のエフェクトをロード。
	m_sampleEffect = Effekseer::Effect::Create(
		g_goMgr.GetEffekseerManager(),
		(const EFK_CHAR*)L"Assets/effect/gunShot.efk"
	);
	//弾数を取得。
	m_ammo = m_gunGen->GetGunAmmo();
	//装填弾数を取得。
	m_loading = m_gunGen->GetGunLoading();
	//最初は銃のインターバルタイマーはm_bulletIntervalTimeにしておく。
	m_bulletIntervalTimer = m_bulletIntervalTime;
}


Rifle::~Rifle()
{
	//GunGeneratorに弾数を保存。
	m_gunGen->SetGunAmmo(m_ammo);
	//GunGeneratorに装填弾数を保存。
	m_gunGen->SetGunLoading(m_loading);
}
void Rifle::Update()
{
	//銃の更新処理。
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

void Rifle::SetRegistShadowCaster()
{
	//シャドウキャスターにセット。
	g_goMgr.GetShadowMap()->RegistShadowCaster(&m_model);
}
void Rifle::Render()
{
	//3D描画。
	m_model.Draw(
		enRenderMode_Normal,
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}
void Rifle::PostRender()
{
	//2D描画。
	GunPostRender(
		&m_reloadTime,
		&m_ammo,
		&m_loading,
		&m_maxLoading
	);
}
void Rifle::OnShot(CVector3* position, CQuaternion* rotation)
{
	//音を再生。
	m_gunShot.Stop();
	m_gunShot.Play(false);
	g_goMgr.GetEffekseerManager()->StopEffect(m_playEffectHandle);
	//再生。
	CVector3 effectPos = *position;
	CVector3 pos = m_gameCam->GetToTargetPos();
	pos.Normalize();
	effectPos += pos * 100.0f;
	g_goMgr.SetPointLightPos(effectPos, 0);

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
void Rifle::Aim(CVector3* position, CQuaternion* rotation, CVector3* aimingPos, CVector3* notAimPos)
{
	*position = m_gameCam->GetPosition();
	CQuaternion PosRot = *rotation;
	//画角。
	float GameCameraViewAngle = m_gameCam->GetGameCameraViewAngle();
	//エイムしているときの銃のローカル座標。
	CVector3 aimPos = *aimingPos;
	//エイムしていないときの銃のローカル座標。
	CVector3 notaimPos = *notAimPos;

	if (g_pad->IsPress(enButtonLB1)) {
		//エイムしている。
		m_gunGen->SetmAimFlug(true);
		PosRot.Multiply(aimPos);
		PosRot.Multiply(notaimPos);

		//エイムしていないときの銃のローカル座標から、
		//エイムしているときの銃のローカル座標に向かうベクトルを求める。
		m_aimMoveSpeed = aimPos - notaimPos;
		//m_aimMoveSpeedを足す回数分だけ割る。
		m_aimMoveSpeed /= DIVIDE_NUM;
		if (m_count < (int)DIVIDE_NUM) {
			//m_countがDIVIDE_NUMより少ないなら移動する。
			m_gunLocalPosition += m_aimMoveSpeed;
			//画角を狭くする。
			m_gameCam->SetGameCameraViewAngle(GameCameraViewAngle - 3.0f);
			m_gameCam->SetRotSpeed(1.0f);
			m_count++;
		}
		else {
			m_gunLocalPosition = *aimingPos;
			PosRot.Multiply(m_gunLocalPosition);
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
			//画角を広くする。。
			m_gameCam->SetGameCameraViewAngle(GameCameraViewAngle + 3.0f);
			m_gameCam->SetRotSpeed(m_rotSpeed);
			m_count--;
		}
		else {
			m_gunLocalPosition = *notAimPos;
			PosRot.Multiply(m_gunLocalPosition);
		}
	}
	*position += m_gunLocalPosition;
}
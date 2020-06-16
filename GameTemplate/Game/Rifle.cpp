#include "stdafx.h"
#include "Rifle.h"
#include "GameManager.h"
#include "GunGenerator.h"
#include "GameCamera.h"

Rifle::Rifle()
{
	m_model.Init(L"Assets/modelData/riful.cmo");
	m_gunGen = g_goMgr.FindGameObject<GunGenerator>(gungenerator);
	m_gunShot.Init(L"Assets/sound/raifulS.wav");
	m_sampleEffect = Effekseer::Effect::Create(
		g_goMgr.GetEffekseerManager(),
		(const EFK_CHAR*)L"Assets/effect/happou.efk"
	);
	m_ammo = m_gunGen->GetGunAmmo();
	m_loading = m_gunGen->GetGunLoading();
}


Rifle::~Rifle()
{
	m_gunGen->SetGunAmmo(m_ammo);
	m_gunGen->SetGunLoading(m_loading);
}
void Rifle::Update()
{
	GunUpdate(
		&m_positon,
		&m_rotation,
		&m_scale,
		&m_ammo,
		&m_loading,
		&m_maxLoading,
		&m_bulletIntervalTime,
		&m_bulletMoveSpeed,
		&m_reaction,
		&m_reloadTime,
		m_gunShot
	);
	m_model.UpdateWorldMatrix(m_positon, m_rotation, m_scale);
}

void Rifle::SetRegistShadowCaster()
{
	g_goMgr.GetShadowMap()->RegistShadowCaster(&m_model);
}
void Rifle::Render()
{
	m_model.Draw(
		enRenderMode_Normal,
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}
void Rifle::PostRender()
{
	GunPostRender(
		&m_reloadTime,
		&m_ammo,
		&m_loading,
		&m_maxLoading
	);
}
void Rifle::OnShot(CVector3* position, CQuaternion* rotation)
{
	g_goMgr.GetEffekseerManager()->StopEffect(m_playEffectHandle);
	//�Đ��B
	CVector3 effectPos = *position;
	CVector3 pos = m_gameCam->GetToTargetPos();
	pos.Normalize();
	effectPos += pos * 100.0f;

	auto effMgr = g_goMgr.GetEffekseerManager();
	m_playEffectHandle = effMgr->Play(
		m_sampleEffect,
		0.0f,
		0.0f,
		0.0f
	);
	//�J�����̉�]�s������߂�B
	CMatrix mCameraRot;
	//�J�����s��̋t�s��̓J�����̃��[���h�s��B
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
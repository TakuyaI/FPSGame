#include "stdafx.h"
#include "Rifle.h"
#include "GameManager.h"
#include "GunGenerator.h"


Rifle::Rifle()
{
	m_model.Init(L"Assets/modelData/riful.cmo");
	m_gunGen = g_goMgr.FindGameObject<GunGenerator>(gungenerator);
	m_gunShot.Init(L"Assets/sound/raifulS.wav");
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
void Rifle::Render()
{
	m_model.Draw(
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
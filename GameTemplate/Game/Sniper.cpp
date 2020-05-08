#include "stdafx.h"
#include "Sniper.h"
#include "GameManager.h"
#include "GunGenerator.h"
//#include "IGunObject.h"

Sniper::Sniper()
{
	m_model.Init(L"Assets/modelData/sniper.cmo");
	m_gunGen = g_goMgr.FindGameObject<GunGenerator>(gungenerator);
	m_gunShot.Init(L"Assets/sound/sniperS.wav");
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
void Sniper::Render()
{
	m_model.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}
void Sniper::PostRender()
{
	GunPostRender(
		&m_reloadTime,
		&m_ammo,
		&m_loading,
		&m_maxLoading
	);
}
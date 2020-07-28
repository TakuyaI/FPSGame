#include "stdafx.h"
#include "Danyaku.h"
#include "Rifle.h"
#include "Shotgun.h"
#include "Sniper.h"
Danyaku::Danyaku()
{
}


Danyaku::~Danyaku()
{
}
void Danyaku::ItemEffects()
{
	m_gunGen = g_goMgr.FindGameObject<GunGenerator>(gungenerator);
	GunNumber gunNum;
	int gunAmmo = 0;
	if (m_gunGen->GetGunNum() == gunNum.RIFLE_NUMBER) {
		m_rifle = g_goMgr.FindGameObject<Rifle>(rifle);
		gunAmmo = m_rifle->GetAmmo();
		gunAmmo += 20;
		m_rifle->SetGunAmmo(gunAmmo);
	}
	else if (m_gunGen->GetGunNum() == gunNum.SHOTGUN_NUMBER) {
		m_shotGun = g_goMgr.FindGameObject<Shotgun>(shotgun);
		gunAmmo = m_shotGun->GetAmmo();
		gunAmmo += 20;
		m_shotGun->SetGunAmmo(gunAmmo);
	}
	else if (m_gunGen->GetGunNum() == gunNum.SNIPER_NUMBER) {
		m_sniper = g_goMgr.FindGameObject<Sniper>(sniper);
		gunAmmo = m_sniper->GetAmmo();
		gunAmmo += 20;
		m_sniper->SetGunAmmo(gunAmmo);
	}
}
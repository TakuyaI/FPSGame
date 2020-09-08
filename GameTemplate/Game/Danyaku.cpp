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
	//GunGeneratorのインスタンスを探す。
	m_gunGen = g_goMgr.FindGameObject<GunGenerator>(gungenerator);
	GunNumber gunNum;
	int gunAmmo = 0;
	if (m_gunGen->GetGunNum() == gunNum.RIFLE_NUMBER) {
		//ライフル。
		m_rifle = g_goMgr.FindGameObject<Rifle>(rifle);
		//今の弾数を代入する。
		gunAmmo = m_rifle->GetAmmo();
		//弾数を加算。
		gunAmmo += m_addBullet;
		//加算した弾数を設定する。
		m_rifle->SetGunAmmo(gunAmmo);
	}
	else if (m_gunGen->GetGunNum() == gunNum.SHOTGUN_NUMBER) {
		//ショットガン。
		m_shotGun = g_goMgr.FindGameObject<Shotgun>(shotgun);
		//今の弾数を代入する。
		gunAmmo = m_shotGun->GetAmmo();
		//弾数を加算。
		gunAmmo += m_addBullet;
		//加算した弾数を設定する。
		m_shotGun->SetGunAmmo(gunAmmo);
	}
	else if (m_gunGen->GetGunNum() == gunNum.SNIPER_NUMBER) {
		//スナイパー。
		m_sniper = g_goMgr.FindGameObject<Sniper>(sniper);
		//今の弾数を代入する。
		gunAmmo = m_sniper->GetAmmo();
		//弾数を加算。
		gunAmmo += m_addBullet;
		//加算した弾数を設定する。
		m_sniper->SetGunAmmo(gunAmmo);
	}
}
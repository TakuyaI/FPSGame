#include "stdafx.h"
#include "GunGenerator.h"
#include "GameManager.h"
#include "Rifle.h"
#include "Shotgun.h"
#include "Sniper.h"

GunGenerator::GunGenerator()
{
	m_sprite.Init(L"Resource/sprite/zyuzi.dds", 256.0f, 144.0f);
}
GunGenerator::~GunGenerator()
{
	GunNumber gunNum;
	if (m_nextnum == gunNum.RIFLE_NUMBER) {
		g_goMgr.DeleteGameObject(m_rifle);
	}
	else if (m_nextnum == gunNum.SHOTGUN_NUMBER) {
		g_goMgr.DeleteGameObject(m_shotgun);
	}
	else if (m_nextnum == gunNum.SNIPER_NUMBER) {
		g_goMgr.DeleteGameObject(m_sniper);
	}
}
int GunGenerator::GetGunAmmo()
{
	GunNumber gunNum;
	if (m_nextnum == gunNum.RIFLE_NUMBER) {
		return m_rifleAmmo;
	}
	else if (m_nextnum == gunNum.SHOTGUN_NUMBER) {
		return m_shotgunAmmo;
	}
	else if (m_nextnum == gunNum.SNIPER_NUMBER) {
		return m_sniperAmmo;
	}
}
void GunGenerator::SetGunAmmo(int ammo)
{
	GunNumber gunNum;
	if (m_num == gunNum.RIFLE_NUMBER) {
		m_rifleAmmo = ammo;
	}
	else if (m_num == gunNum.SHOTGUN_NUMBER) {
		m_shotgunAmmo = ammo;
	}
	else if (m_num == gunNum.SNIPER_NUMBER) {
		m_sniperAmmo = ammo;
	}
}
int GunGenerator::GetGunLoading()
{
	GunNumber gunNum;
	if (m_nextnum == gunNum.RIFLE_NUMBER) {
		return m_rifulLoading;
	}
	else if (m_nextnum == gunNum.SHOTGUN_NUMBER) {
		return m_shotgunLoading;
	}
	else if (m_nextnum == gunNum.SNIPER_NUMBER) {
		return m_sniperLoading;
	}
}
void GunGenerator::SetGunLoading(int loading)
{
	GunNumber gunNum;
	if (m_num == gunNum.RIFLE_NUMBER) {
		m_rifulLoading = loading;
	}
	else if (m_num == gunNum.SHOTGUN_NUMBER) {
		m_shotgunLoading = loading;
	}
	else if (m_num == gunNum.SNIPER_NUMBER) {
		m_sniperLoading = loading;
	}
}
void GunGenerator::Update()
{
	if (m_initGunFlug != true) {
		//最初に装備する銃。
		m_rifle = g_goMgr.NewGameObject<Rifle>(rifle);
		m_initGunFlug = true;

	}
	if (m_reloadFlug != true) {
		if (g_pad->IsTrigger(enButtonY)) {
			//Yボタンで銃を切り替える。
			if (m_shootingBulletFlug != true) {
				//弾を発射していない。
				m_num = m_nextnum;
				m_nextnum++;
				GunNumber gunNum;
				if (m_nextnum >= gunNum.END_NUMBER) {
					//m_nextnumが最後の番号に来たら、
					//最初の番号に戻す。
					m_nextnum = gunNum.RIFLE_NUMBER;
				}
				if (m_nextnum == gunNum.RIFLE_NUMBER) {
					g_goMgr.DeleteGameObject(m_sniper);
					m_rifle = g_goMgr.NewGameObject<Rifle>(rifle);
					m_rifleAmmo = m_rifle->GetAmmo();
					m_rifulLoading = m_rifle->GetBlaze();
				}
				else if (m_nextnum == gunNum.SHOTGUN_NUMBER) {
					g_goMgr.DeleteGameObject(m_rifle);
					m_shotgun = g_goMgr.NewGameObject<Shotgun>(shotgun);
					m_shotgunAmmo = m_shotgun->GetAmmo();
					m_shotgunLoading = m_shotgun->GetBlaze();
				}
				else if (m_nextnum == gunNum.SNIPER_NUMBER) {
					g_goMgr.DeleteGameObject(m_shotgun);
					m_sniper = g_goMgr.NewGameObject<Sniper>(sniper);
					m_sniperAmmo = m_sniper->GetAmmo();
					m_sniperLoading = m_sniper->GetBlaze();
				}
			}
		}
	}
}
void GunGenerator::PostRender()
{
	m_sprite.Draw();
}

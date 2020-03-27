#include "stdafx.h"
#include "GunGenerator.h"
#include "GameManager.h"
#include "Gun.h"
#include "GameCamera.h"

GunGenerator::GunGenerator()
{
	m_sprite.Init(L"Resource/sprite/zyuzi.dds", 256.0f, 144.0f);
}
GunGenerator::~GunGenerator()
{
	g_goMgr.DeleteGameObject(m_gun);
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
int GunGenerator::GetGunBlaze()
{
	GunNumber gunNum;
	if (m_nextnum == gunNum.RIFLE_NUMBER) {
		return m_rifulBlaze;
	}
	else if (m_nextnum == gunNum.SHOTGUN_NUMBER) {
		return m_shotgunBlaze;
	}
	else if (m_nextnum == gunNum.SNIPER_NUMBER) {
		return m_sniperBlaze;
	}
}
void GunGenerator::Update()
{
	if (a != true) {
		m_gun = g_goMgr.NewGameObject<Gun>(gun);
		a = true;
	}
	if (m_gun->GetReloadFlug() != true) {
		if (g_pad->IsTrigger(enButtonY)) {
			//Yボタンで銃を切り替える。
			//m_gameCam = g_goMgr.FindGameObject<GameCamera>(gamecamera);
			if (m_gun->GetShootingBulletFlug() != true) {
				GunNumber gunNum;
				if (m_nextnum == gunNum.RIFLE_NUMBER) {
					m_rifleAmmo = m_gun->GetAmmo();
					m_rifulBlaze = m_gun->GetBlaze();
				}
				else if (m_nextnum == gunNum.SHOTGUN_NUMBER) {
					m_shotgunAmmo = m_gun->GetAmmo();
					m_shotgunBlaze = m_gun->GetBlaze();
				}
				else if (m_nextnum == gunNum.SNIPER_NUMBER) {
					m_sniperAmmo = m_gun->GetAmmo();
					m_sniperBlaze = m_gun->GetBlaze();
				}
				//弾を発射していない。
				g_goMgr.DeleteGameObject(m_gun);
				m_nextnum++;

				if (m_nextnum >= gunNum.END_NUMBER) {
					m_nextnum = gunNum.RIFLE_NUMBER;
				}
				m_gun = g_goMgr.NewGameObject<Gun>(gun);
			}
		}
	}
}
void GunGenerator::PostRender()
{
	m_sprite.Draw();
}

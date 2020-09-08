#include "stdafx.h"
#include "GunGenerator.h"
#include "Rifle.h"
#include "Shotgun.h"
#include "Sniper.h"

const CVector2 SCOPE_SPRITE_SIZE = { 256.0f, 144.0f };
GunGenerator::GunGenerator()
{
	//銃の照準の画像をロード。
	m_sprite.Init(L"Resource/sprite/zyuzi.dds", SCOPE_SPRITE_SIZE.x, SCOPE_SPRITE_SIZE.y);
}
GunGenerator::~GunGenerator()
{
	//銃のインスタンスを削除。
	g_goMgr.DeleteGameObject(m_gun);
}

int GunGenerator::GetGunAmmo()
{
	GunNumber gunNumber;
	if (m_gunNum == gunNumber.RIFLE_NUMBER) {
		//銃の番号がライフル。
		return m_rifleAmmo;
	}
	else if (m_gunNum == gunNumber.SHOTGUN_NUMBER) {
		//銃の番号がショットガン。
		return m_shotgunAmmo;
	}
	else if (m_gunNum == gunNumber.SNIPER_NUMBER) {
		//銃の番号がスナイパー。
		return m_sniperAmmo;
	}
}
void GunGenerator::SetGunAmmo(int ammo)
{
	GunNumber gunNumber;
	if (m_beforeGunNum == gunNumber.RIFLE_NUMBER) {
		//前の銃の番号がライフル。
		m_rifleAmmo = ammo;
	}
	else if (m_beforeGunNum == gunNumber.SHOTGUN_NUMBER) {
		//前の銃の番号がショットガン。
		m_shotgunAmmo = ammo;
	}
	else if (m_beforeGunNum == gunNumber.SNIPER_NUMBER) {
		//前の銃の番号がスナイパー。
		m_sniperAmmo = ammo;
	}
}
int GunGenerator::GetGunLoading()
{
	GunNumber gunNumber;
	if (m_gunNum == gunNumber.RIFLE_NUMBER) {
		//銃の番号がライフル。
		return m_rifulLoading;
	}
	else if (m_gunNum == gunNumber.SHOTGUN_NUMBER) {
		//銃の番号がショットガン。
		return m_shotgunLoading;
	}
	else if (m_gunNum == gunNumber.SNIPER_NUMBER) {
		//銃の番号がスナイパー。
		return m_sniperLoading;
	}
}
void GunGenerator::SetGunLoading(int loading)
{
	GunNumber gunNumber;
	if (m_beforeGunNum == gunNumber.RIFLE_NUMBER) {
		//前の銃の番号がライフル。
		m_rifulLoading = loading;
	}
	else if (m_beforeGunNum == gunNumber.SHOTGUN_NUMBER) {
		//前の銃の番号がショットガン。
		m_shotgunLoading = loading;
	}
	else if (m_beforeGunNum == gunNumber.SNIPER_NUMBER) {
		//前の銃の番号がスナイパー。
		m_sniperLoading = loading;
	}
}
bool GunGenerator::Start()
{
	//ライフルのインスタンスを生成。
	m_gun = g_goMgr.NewGameObject<Rifle>(rifle);
	return true;
}
void GunGenerator::Update()
{
	if (g_pad->IsTrigger(enButtonY)) {
		//Yボタンで銃を切り替える。
		if (
			g_goMgr.GetShotFlug() != true && //弾を発射していない。
			m_aimFlug != true &&             //エイムしていない。
			m_reloadFlug != true &&          //リロードしていない。
			m_PutAwayFlug != true &&         //銃をしまっている最中でない。
			m_PutOutFlug != true             //銃を出している最中でない。
			) {
			//銃をしまっているフラグを立てる。
			m_PutAwayFlug = true;
			m_switchFlug = true;
		}
	}

	if (
		m_switchFlug != false &&   //銃の切り替えフラグが立った。
		m_PutOutFlug != false      //銃をしまい終えた。
		) {
		//換える前の銃の番号を補完しておく。
		m_beforeGunNum = m_gunNum;
		m_gunNum++;
		GunNumber gunNumber;
		if (m_gunNum >= gunNumber.END_NUMBER) {
			//m_nextnumが最後の番号に来たら、
			//最初の番号に戻す。
			m_gunNum = gunNumber.RIFLE_NUMBER;
		}
		//銃のインスタンスを削除。
		g_goMgr.DeleteGameObject(m_gun);
		if (m_gunNum == gunNumber.RIFLE_NUMBER) {
			//ライフル。
			m_gun = g_goMgr.NewGameObject<Rifle>(rifle);
		}
		else if (m_gunNum == gunNumber.SHOTGUN_NUMBER) {
			//ショットガン。
			m_gun = g_goMgr.NewGameObject<Shotgun>(shotgun);
		}
		else if (m_gunNum == gunNumber.SNIPER_NUMBER) {
			//スナイパー。
			m_gun = g_goMgr.NewGameObject<Sniper>(sniper);
		}

		m_switchFlug = false;
	 }
}
void GunGenerator::PostRender()
{
	//2D描画。
	m_sprite.Draw();
}

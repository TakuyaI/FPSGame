#include "stdafx.h"
#include "GunGenerator.h"
#include "GameManager.h"
#include "Gun.h"
#include "GameCamera.h"

GunGenerator::GunGenerator()
{
}
GunGenerator::~GunGenerator()
{
}

void GunGenerator::Update()
{
	if (a != true) {
		m_gun = g_goMgr.NewGameObject<Gun>(gun);
		a = true;
	}

	if (g_pad->IsTrigger(enButtonX)) {
		//Xボタンで銃を切り替える。
		m_gameCam = g_goMgr.FindGameObject<GameCamera>(gamecamera);
		if (m_gun->GetShootingBulletFlug() != true) {
			//弾を発射していない。
			g_goMgr.DeleteGameObject(m_gun);
			m_nextnum++;
			GunNumber gunNum;
			if (m_nextnum >= gunNum.END_NUMBER) {
				m_nextnum = gunNum.RIFLE_NUMBER;
			}
			m_gun = g_goMgr.NewGameObject<Gun>(gun);
		}
	}
}
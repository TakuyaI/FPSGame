#include "stdafx.h"
#include "EnemyGenerator.h"
#include "GameManager.h"


EnemyGenerator::EnemyGenerator()
{

}


EnemyGenerator::~EnemyGenerator()
{
}

Enemy* EnemyGenerator::GetEnemy()
{
	if (m_flug != 0) {
		if (m_gameCam->GetFlug() != true) {
			m_playerPos = m_player->GetPosition();
			for (int i = 0; i < m_enemyNum; i++) {
				CVector3 leg = m_playerPos - m_enemy[i]->GetPosition();
				float diff = leg.Length();
				if (diff < m_kyori) {
					m_kyori = diff;
					n = i;
				}
			}
			m_kyori = 1000000.0f;
		}
		return m_enemy[n];
	}
}

void EnemyGenerator::Update()
{
	m_timer++;
	if (m_enemyNum < m_enemyMax) {
		if (m_timer == 60) {
			m_enemy[m_enemyNum] = g_goMgr.NewGameObject<Enemy>();
			m_enemy[m_enemyNum]->SetPosition(pos);
			pos.x += 30.0f;
			m_enemyNum++;
			m_flug = 1;
			m_timer = 0;
		}
	}

	if (m_enemyNum >= m_enemyMax) {
		t++;
		if (t == 30) {
			g_goMgr.DeleteGameObject(m_enemy[1]);
			m_enemyNum--;
			t = 0;
			for (int i = 1; i < m_enemyNum; i++) {
				m_enemy[i] = m_enemy[i + 1];
			}
		}
	}
}
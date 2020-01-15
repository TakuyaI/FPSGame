#include "stdafx.h"
#include "EnemyGenerator.h"
#include "GameManager.h"

const float RESET_KYORI = 1000000.0f; //“K“–‚É‚Å‚©‚¢”’l‚ğ“ü‚ê‚Ä‚¨‚­B
EnemyGenerator::EnemyGenerator()
{

}


EnemyGenerator::~EnemyGenerator()
{
}

Enemy* EnemyGenerator::GetClosestEnemyToPlayer()
{
	m_player = g_goMgr.FindGameObject<Player>(player);
	m_gameCam = g_goMgr.FindGameObject<GameCamera>(gamecamera);
	if (m_enemyOccurrenceFlug != false) {
		if (m_gameCam->LockOnTargetFlug() != true) {
			m_playerPos = m_player->GetPosition();
			for (int i = 0; i < m_enemyNum; i++) {
				CVector3 leg = m_playerPos - m_enemy[i]->GetPosition();
				float diff = leg.Length();
				if (diff < m_kyori) {
					m_kyori = diff;
					n = i;
				}
			}
			m_kyori = RESET_KYORI;
		}
		return m_enemy[n];
	}
}

void EnemyGenerator::Update()
{

	if (m_enemyNum <= 0) {
		m_enemyOccurrenceFlug = false;
	}
	m_timer++;
	if (m_enemyNum < m_enemyMax) {
		if (m_timer == 60) {
			m_enemy[m_enemyNum] = g_goMgr.NewGameObject<Enemy>(enemy);
			m_enemy[m_enemyNum]->SetPosition(m_enemyInitPos);
			m_enemyInitPos.x += 300.0f;
			m_enemyNum++;
			m_enemyOccurrenceFlug = true;
			m_timer = 0;
		}
	}
	

	/*m_timer++;
	if (m_enemyNum < m_enemyMax) {
		if (m_timer == 60) {
			m_enemy[m_enemyNum] = g_goMgr.NewGameObject<Enemy>(enemy);
			m_enemyInitPos.x = g_goMgr.Lerp(-1000.0f, 1000.0f);
			m_enemyInitPos.z = g_goMgr.Lerp(-1000.0f, 1000.0f);
			
			m_enemy[m_enemyNum]->SetPosition(m_enemyInitPos);
			
			m_enemyNum++;
			m_enemyOccurrenceFlug = true;
			m_timer = 0;
		}
	}*/

}
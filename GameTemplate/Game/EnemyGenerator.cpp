#include "stdafx.h"
#include "EnemyGenerator.h"
#include "GameManager.h"
#include "Bullet.h"
const float RESET_KYORI = 1000000.0f; //適当にでかい数値を入れておく。
const int ENEMY_OCCURRENCE_TIME = 60; //敵が出現するまでの時間。
EnemyGenerator::EnemyGenerator()
{

}


EnemyGenerator::~EnemyGenerator()
{
	for (int i = 0; i < m_enemyNumber; i++) {
		g_goMgr.DeleteGameObject(m_enemy[i]);
	}
}
void EnemyGenerator::DeleteEnemy()
{
	for (int i = m_enToBuNum; i < m_enemyNumber; i++) {
		m_enemy[i] = m_enemy[i + 1];
	}
}
Enemy* EnemyGenerator::GetClosestEnemyToPlayer()
{

	m_player = g_goMgr.FindGameObject<Player>(player);
	m_gameCam = g_goMgr.FindGameObject<GameCamera>(gamecamera);
	if (m_enemyOccurrenceFlug != false) {
		//Enemyが出現した。
		if (m_gameCam->LockOnTargetFlug() != true) {
			//Enemyをロックオンしていない。
			m_playerPos = m_player->GetPosition();
			for (int i = 0; i < m_enemyNumber; i++) {
				CVector3 leg = m_playerPos - m_enemy[i]->GetPosition();
				float diff = leg.Length();
				if (diff < m_kyori) {
					m_kyori = diff;
					m_enToPlNum = i;
				}
			}
			m_kyori = RESET_KYORI;
		}
		return m_enemy[m_enToPlNum];
	}
}

Enemy* EnemyGenerator::GetClosestEnemyToBullet(CVector3 bulletPos)
{
	float toBullet = 1000000.0f;
	for (int i = 0; i < m_enemyNumber; i++) {
		CVector3 lig = bulletPos - m_enemy[i]->GetPosition();
		float diff = lig.Length();
		if (diff < toBullet) {
			toBullet = diff;
			m_enToBuNum = i;
		}
	}
	toBullet = RESET_KYORI;
	return m_enemy[m_enToBuNum];
}

void EnemyGenerator::Update()
{

	if (m_enemyNumber <= 0) {
		m_enemyOccurrenceFlug = false;
	}

	/*if (m_enemyNumber < m_enemyMax) {
		m_timer++;
		if (m_timer == ENEMY_OCCURRENCE_TIME) {
			m_enemy[m_enemyArrayNum] = g_goMgr.NewGameObject<Enemy>(enemy);
			m_enemy[m_enemyArrayNum]->SetPosition(m_enemyInitPos);
			m_enemyInitPos.x += 300.0f;
			m_enemyArrayNum++;
			m_enemyNumber++;
			m_enemyOccurrenceFlug = true;
			m_timer = 0;
		}
	}*/
	
	if (m_enemyNumber < m_enemyMax) {
	    m_timer++;
		if (m_timer == ENEMY_OCCURRENCE_TIME) {
			m_enemy[m_enemyArrayNum] = g_goMgr.NewGameObject<Enemy>(enemy);
			m_enemyInitPos.x = g_goMgr.Lerp(-2000.0f, 2000.0f);
			m_enemyInitPos.z = g_goMgr.Lerp(-2000.0f, 2000.0f);
			
			m_enemy[m_enemyArrayNum]->SetPosition(m_enemyInitPos);
			
			m_enemyArrayNum++;
			m_enemyNumber++;
			m_enemyOccurrenceFlug = true;
			m_timer = 0;
		}
	}
	
}
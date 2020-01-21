#include "stdafx.h"
#include "Bullet.h"
#include "GameManager.h"
#include "Enemy.h"
#include "GameCamera.h"
#include "GunGenerator.h"
#include "EnemyGenerator.h"
struct BulletInformation {
	const int RIFLE_BULLET_POWER = 10;
	const int SHOTGUN_BULLET_POWER = 7;
	const int SNIPER_BULLET_POWER = 20;
};
Bullet::Bullet()
{
	m_enemyGen = g_goMgr.FindGameObject<EnemyGenerator>(enemygenerator);
	m_gunGen = g_goMgr.FindGameObject<GunGenerator>(gungenerator);
	GunNumber gunNum;
	BulletInformation bulletInf;
	if (m_gunGen->GetNextNum() == gunNum.RIFLE_NUMBER) {
		m_model.Init(L"Assets/modelData/bullet_test.cmo");
		m_bulletPower = bulletInf.RIFLE_BULLET_POWER;
	}
	else if (m_gunGen->GetNextNum() == gunNum.SHOTGUN_NUMBER) {
		m_model.Init(L"Assets/modelData/shotgun_bullet.cmo");
		m_bulletPower = bulletInf.SHOTGUN_BULLET_POWER;
	}
	else if (m_gunGen->GetNextNum() == gunNum.SNIPER_NUMBER) {
		m_model.Init(L"Assets/modelData/sniper_bullet.cmo");
		m_bulletPower = bulletInf.SNIPER_BULLET_POWER;
	}
}


Bullet::~Bullet()
{
}

void Bullet::Update()
{
	if (m_enemyGen->GetEnemyOccurrenceFlug() != false) {
		m_enemy = /*g_goMgr.FindGameObject<Enemy>(enemy);*/m_enemyGen->GetClosestEnemyToBullet(m_position);
		CVector3 enemyPos = m_enemy->GetPosition();
		enemyPos.y += 100.0f;
		CVector3 v = enemyPos - m_position;
		if (v.Length() <= 100.0f) {
			int enemyhp = m_enemy->GetEnemyHp();
			m_enemy->SetEnemyHp(enemyhp - m_bulletPower);
			if (enemyhp <= 0) {
				g_goMgr.DeleteGameObject(m_enemy);
				int enemyNum = m_enemyGen->GetEnemyNumber();
				m_enemyGen->SetEnemyNumber(--enemyNum);
				int enemyArrayNum = m_enemyGen->GetEnemyArrayNum();
				m_enemyGen->SetEnemyArrayNum(--enemyArrayNum);
				m_enemyGen->DeleteEnemy();
			}
			g_goMgr.DeleteGameObject(this);
		}
	}
	m_timer++;
	m_position += m_moveSpeed;
	if (m_timer >= 5) {
		g_goMgr.DeleteGameObject(this);
	}
	m_gun = g_goMgr.FindGameObject<Gun>(gun);
	m_model.UpdateWorldMatrix(m_position, m_gun->GetRotation(), CVector3::One());
	
}
void Bullet::Render()
{
	m_model.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}
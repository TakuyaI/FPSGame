#include "stdafx.h"
#include "Bullet.h"
#include "GameManager.h"
#include "Enemy.h"
#include "GameCamera.h"
#include "GunGenerator.h"
#include "EnemyGenerator.h"
Bullet::Bullet()
{
	m_enemyGen = g_goMgr.FindGameObject<EnemyGenerator>(enemygenerator);
	m_gunGen = g_goMgr.FindGameObject<GunGenerator>(gungenerator);
	if (m_gunGen->GetNextNum() == 0) {
		m_model.Init(L"Assets/modelData/bullet_test.cmo");
	}
	else if (m_gunGen->GetNextNum() == 1) {
		m_model.Init(L"Assets/modelData/shotgun_bullet.cmo");
	}
}


Bullet::~Bullet()
{
}

void Bullet::Update()
{
	if (m_enemyGen->GetEnemyOccurrenceFlug() != false) {
		m_enemy = g_goMgr.FindGameObject<Enemy>(enemy);
		CVector3 enemyPos = m_enemy->GetPosition();
		enemyPos.y += 100.0f;
		CVector3 v = enemyPos - m_position;
		if (v.Length() <= 100.0f) {
			int hp = m_enemy->GetEnemyHp();
			m_enemy->SetEnemyHp(hp - 10);
			if (hp <= 0) {
				g_goMgr.DeleteGameObject(m_enemy);
				int a = m_enemyGen->GetEnemyNum();
				m_enemyGen->SetEnemyNum(--a);
			}
			g_goMgr.DeleteGameObject(this);
		}
	}
	m_timer++;
	m_position += m_moveSpeed;
	if (m_timer >= 10) {
		g_goMgr.DeleteGameObject(this);
	}

	m_model.UpdateWorldMatrix(m_position, CQuaternion::Identity(), CVector3::One());
	m_model.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}
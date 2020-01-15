#pragma once
class Enemy;
//class GunGenerator;
#include "IGameObject.h"
#include "Gun.h"
class Bullet : public IGameObject
{
public:
	Bullet();
	~Bullet();

	void Update();

	void SetPosition(CVector3 pos)
	{
		m_position = pos;
	}
	CVector3 GetPosition()
	{
		return m_position;
	}
	
	void SetMoveSpeed(CVector3 moveSpeed)
	{
		m_moveSpeed = moveSpeed;
	}
private:
	Gun * m_gun;
	Enemy* m_enemy;
	GameCamera* m_gameCam;
	GunGenerator* m_gunGen;
	EnemyGenerator* m_enemyGen;
	SkinModel m_model;
	CVector3 m_position = CVector3::Zero();
	CVector3 m_moveSpeed = CVector3::Zero();
	int m_timer = 0;
};


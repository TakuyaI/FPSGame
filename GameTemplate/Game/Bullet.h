#pragma once
class Enemy;
class Item;
//class GunGenerator;
#include "IGameObject.h"
#include "Gun.h"
#include "Game.h"
class Bullet : public IGameObject
{
public:
	Bullet();
	~Bullet();

	void Update();
	void Render();

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
	Item* m_item;
	Game* m_game;

	SkinModel m_model;
	CVector3 m_position = CVector3::Zero();
	CVector3 m_moveSpeed = CVector3::Zero();
	int m_timer = 0;
	bool m_deleteEenmyFlug = false;
	int m_bulletPower = 0;
	float m_bulletAccuracy = 0.0f;
	int m_knockDownEnemyNum = 0; //ì|ÇµÇ∑ìGÇÃêîÅB
};


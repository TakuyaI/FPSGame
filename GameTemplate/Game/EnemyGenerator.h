#pragma once
class Gun;
class GameCamera;
#include "IGameObject.h"
#include "Enemy.h"
#include "Gun.h"
#include "GameCamera.h"
#include "Game.h"
#include "Player.h"
class EnemyGenerator : public IGameObject
{
public:
	EnemyGenerator();
	~EnemyGenerator();

	int GetEnemyOccurrenceFlug()
	{
		return m_enemyOccurrenceFlug;
	}
	CVector3 GetEnemyInitPos()
	{
		return m_enemyInitPos;
	}
	void SetEnemyNum(int enemynum)
	{
		m_enemyNum = enemynum;
	}
	int GetEnemyNum()
	{
		return m_enemyNum;
	}
	void SetAttackFlug(bool flug)
	{
		m_attackFlug = flug;
	}
	bool GetAttackFlug()
	{
		return m_attackFlug;
	}
	
	Enemy* GetClosestEnemyToPlayer(); //PlayerÇ∆1î‘ãﬂÇ¢EnemyÅB
	void Update();
private:
	Enemy * m_enemy[50];
	Gun* m_gun;
	GameCamera* m_gameCam;
	Game* m_game;
	Player* m_player;

	CVector3 m_playerPos = CVector3::Zero();
	float m_kyori = 1000000.0f;
	int n = 0;

	bool m_enemyOccurrenceFlug = false;
	int m_timer = 0;
	int m_enemyNum = 0;
	const int m_enemyMax = 50;
	CVector3 m_enemyInitPos = { 0.0f, 0.0f, 300.0f };
	int t = 0;
	bool m_attackFlug = false;
};


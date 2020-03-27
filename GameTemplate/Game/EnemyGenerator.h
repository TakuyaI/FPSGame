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
	void SetEnemyArrayNum(int enemynum)
	{
		m_enemyArrayNum = enemynum;
	}
	int GetEnemyArrayNum()
	{
		return m_enemyArrayNum;
	}
	void SetEnemyNumber(int num)
	{
		m_enemyNumber = num;
	}
	int GetEnemyNumber()
	{
		return m_enemyNumber;
	}
	void SetAttackFlug(bool flug)
	{
		m_attackFlug = flug;
	}
	bool GetAttackFlug()
	{
		return m_attackFlug;
	}

	void DeleteEnemy();
	//Playerと1番近いEnemy。
	Enemy* GetClosestEnemyToPlayer();
	//Bulletと1番近いEnemy。
	Enemy* GetClosestEnemyToBullet(CVector3 bulletPos);
	void Update();
private:
	Enemy * m_enemy[50];
	Gun* m_gun;
	GameCamera* m_gameCam;
	Game* m_game;
	Player* m_player;
	Bullet* m_bullet;

	CVector3 m_playerPos = CVector3::Zero();
	float m_kyori = 1000000.0f;
	int m_enToPlNum = 0;//Playerと1番近いEnemyの配列ナンバー。
	int m_enToBuNum = 0;//Bulletと1番近いEnemyの配列ナンバー。
	bool m_enemyOccurrenceFlug = false;
	int m_timer = 0;
	int m_enemyArrayNum = 0; //Enemyの配列ナンバー。
	const int m_enemyMax = 10;
	CVector3 m_enemyInitPos = { 0.0f, 0.0f, 300.0f };
	int t = 0;
	bool m_attackFlug = false;
	int m_enemyNumber = 0;  //Enemyの数。
};


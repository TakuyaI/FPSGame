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

	void SetGameCamera(GameCamera* gc)
	{
		m_gameCam = gc;
	}

	void SetPlayer(Player* pl)
	{
		m_player = pl;
	}

	int GetFlug()
	{
		return m_flug;
	}

	Enemy* GetEnemy();

	void Update();
private:
	Enemy * m_enemy[5];
	Gun* m_gun;
	GameCamera* m_gameCam;
	Game* m_game;
	Player* m_player;

	CVector3 m_playerPos = CVector3::Zero();
	float m_kyori = 1000000.0f;
	int n = 0;

	int m_flug = 0;
	int m_timer = 0;
	int m_enemyNum = 0;
	int m_enemyMax = 5;
	CVector3 pos = { 0.0f, 0.0f, 300.0f };
	int t = 0;
};


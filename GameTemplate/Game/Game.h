#pragma once
class Gun;
class GameCamera;
class EnemyGenerator;
#include "IGameObject.h"
#include "Player.h"
#include "BackGround.h"
#include "GameCamera.h"
#include "Enemy.h"
#include "EnemyGenerator.h"
#include "Gun.h"
class Game : public IGameObject
{
public:
	Game();
	~Game();

	void Update();

private:
	Player* m_player;
	BackGround* m_backGro;
	GameCamera* m_gameCam;
	Enemy* m_enemy;
	EnemyGenerator* m_enemyGen;
	Gun* m_gun;
};


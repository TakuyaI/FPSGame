#pragma once
class Gun;
class GameCamera;
class EnemyGenerator;
class Sprite;
class GunGenerator;
#include "IGameObject.h"
#include "Player.h"
#include "BackGround.h"
#include "GameCamera.h"
#include "Enemy.h"
#include "EnemyGenerator.h"
#include "Gun.h"
#include "Sprite.h"
#include "FontRender.h"
class Game : public IGameObject
{
public:
	Game();
	~Game();


	void Update();
	void PostRender();
	 
	void SetFlug(bool flug)
	{
		m_flug = flug;
	}
	bool GetFlug()
	{
		return m_flug;
	}

private:
	FontRender m_font;
	Player* m_player;
	BackGround* m_backGro;
	GameCamera* m_gameCam;
	Enemy* m_enemy;
	EnemyGenerator* m_enemyGen;
	Gun* m_gun;
	GunGenerator* m_gunGen;
	Sprite m_sprite;
	int m_gameOverTime = 0;
	bool m_flug = false;
};


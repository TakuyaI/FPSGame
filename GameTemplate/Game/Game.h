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
class Game : public IGameObject
{
public:
	Game();
	~Game();

	void Update();
	void PostRender();

private:
	Player* m_player;
	BackGround* m_backGro;
	GameCamera* m_gameCam;
	Enemy* m_enemy;
	EnemyGenerator* m_enemyGen;
	Gun* m_gun;
	GunGenerator* m_gunGen;
	Sprite m_sprite;
	CVector3 pos = CVector3::Zero();
	CVector3 scale =CVector3::One();
	CQuaternion m_rotation = CQuaternion::Identity();
};


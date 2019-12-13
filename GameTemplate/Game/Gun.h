#pragma once
class GameCamera;
class Bullet;
#include "IGameObject.h"
#include "Player.h"
#include "Enemy.h"
#include "GameCamera.h"
#include "Bullet.h"
class Gun : public IGameObject
{
public:
	Gun();
	~Gun();
	
	void Update();


	void SetPlayer(Player* pl)
	{
		m_player = pl;
	}
	void SetEenmy(Enemy* en)
	{
		m_enemy = en;
	}
	void SetGameCamera(GameCamera* gc)
	{
		m_gameCam = gc;
	}
	Bullet* GetBullet()
	{
		return m_bullet;
	}
	CVector3 Getpostion()
	{
		return m_position;
	}
private:
	SkinModel m_model;
	Player* m_player;
	Enemy* m_enemy;
	GameCamera* m_gameCam;
	Bullet* m_bullet;

	CVector3 m_position = CVector3::Zero();
	CVector3 m_Pos = { 15.0f, -8.0f, 10.0f };
	CVector3 m_gunLocalPosition = { 15.0f, -8.0f, 10.0f };
	CVector3 m_bulletPos = CVector3::Zero();
	CQuaternion m_rotation = CQuaternion::Identity();
	float m_angle = 0.0f;
	float m_angle2 = 0.0f;
};


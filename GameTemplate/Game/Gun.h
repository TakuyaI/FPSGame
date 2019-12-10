#pragma once
class GameCamera;
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
private:
	SkinModel m_model;
	Player* m_player;
	Enemy* m_enemy;
	GameCamera* m_gameCam;
	Bullet* m_bullet;

	CVector3 m_position = CVector3::Zero();
	CQuaternion m_rotation = CQuaternion::Identity();
	CVector3 m_pos = CVector3::Zero();
	float m_angle = 0.0f;
	float m_angle2 = 0.0f;
	CQuaternion rotation = CQuaternion::Identity();
	CQuaternion m_rot = CQuaternion::Identity();

	CVector3 m_toTarget = CVector3::Zero();
	CVector3 m_Pos = { 15.0f, -8.0f, 10.0f };
	CVector3 m_gunLocalPosition = { 15.0f, -8.0f, 10.0f };
};


#pragma once
class GameCamera;
class Bullet;
class GunGenerator;
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

	CVector3 Getpostion()
	{
		return m_position;
	}
	void SetNum(int num)
	{
		m_setNum = num;
	}
	int GetNum()
	{
		return m_setNum;
	}
	void SetShootingBulletFlug(bool shootingbullet)
	{
		m_shootingBulletFlug = shootingbullet;
	}
	bool GetShootingBulletFlug()
	{
		return m_shootingBulletFlug;
	}
	CQuaternion GetRotation()
	{
		return m_rotation;
	}
private:
	SkinModel m_model;
	Player* m_player;
	Enemy* m_enemy;
	GameCamera* m_gameCam;
	Bullet* m_bullet;
	GunGenerator* m_gunGen;

	CVector3 m_position = CVector3::Zero();
	CVector3 m_Pos = { 15.0f, -8.0f, 10.0f };
	CVector3 m_gunLocalPosition = { 15.0f, -8.0f, 10.0f };
	CVector3 m_bulletPos = CVector3::Zero();
	CQuaternion m_rotation = CQuaternion::Identity();
	float m_angle = 0.0f;
	float m_angle2 = 0.0f;
	int m_bulletIntervalTimer = 5;
	int m_bulletIntervalTime;
	float m_bulletMoveSpeed;
	int m_setNum = 0;
	bool m_shootingBulletFlug = false; //íeÇåÇÇ¡ÇƒÇ¢ÇÈÇ©Ç«Ç§Ç©ÅB
};


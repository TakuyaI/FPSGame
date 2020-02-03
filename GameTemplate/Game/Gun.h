#pragma once
class GameCamera;
class Bullet;
class GunGenerator;
class Sprite;
#include "IGameObject.h"
#include "Player.h"
#include "Enemy.h"
#include "GameCamera.h"
#include "Bullet.h"
#include "Sprite.h"
class Gun : public IGameObject
{
public:
	Gun();
	~Gun();

	void Update();
	void Render();
	void PostRender();

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
	int GetAmmo()
	{
		return m_ammo;
	}
	int GetBlaze()
	{
		return m_blaze;
	}
	bool GetReloadFlug()
	{
		return m_reloadFlug;
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
	int m_ammo = 0; //�e���B
	int m_blaze = 0;//�A�˒e���B
	int m_usedBullet = 0; //�g���I�����e�B
	int m_maxBlaze = 0;//�ő�A�˒e���B
	float m_reaction = 0.0f;   //�e�̔����B
	int m_reloadTimer = 0;  //�����[�h�^�C�}�[�B
	int m_reloadTime = 0;  //�����[�h�^�C���B
	bool m_reloadFlug = false; //�����[�h���Ă��邩�ǂ����B
	bool m_shootingBulletFlug = false; //�e�������Ă��邩�ǂ����B



	Sprite m_sprite;
	CVector3 pos = CVector3::Zero();
	CVector3 scale = { 0.6f, 0.1f, 1.0f };
};


#pragma once
class Enemy;
class Game;
#include "IGameObject.h"
#include "PhysicsGhostObject.h"
#include "Rifle.h"
#include "Shotgun.h"
#include "Sniper.h"
#include "BackGround.h"
class Bullet : public IGameObject
{
public:
	Bullet();
	~Bullet();

	void InitGhost();
	bool Start();
	void Update();
	void SetRegistShadowCaster();
	void Render();

	void SetPosition(CVector3 pos)
	{
		m_position = pos;
	}
	CVector3 GetPosition()
	{
		return m_position;
	}
	
	void SetMoveSpeed(CVector3 moveSpeed)
	{
		m_moveSpeed = moveSpeed;
	}
	CharacterController* GetCharaCon()
	{
		return &m_charaCon;
	}
private:
	/// <summary>
	/// íeä€Ç∆ìGÇÃè’ìÀîªíË
	/// </summary>
	void CollisionBulletToEnemy();
	void CollisionBulletToDogEnemy();
private:
	Enemy* m_enemy;
	GameCamera* m_gameCam;
	GunGenerator* m_gunGen;
	EnemyGenerator* m_enemyGen;
	Game* m_game;
	BackGround* m_backGro;
	Rifle* m_rifle;
	Shotgun* m_shotgun;
	Sniper* m_sniper;

	SkinModel m_model;
	CVector3 m_position = CVector3::Zero();
	CVector3 m_moveSpeed = CVector3::Zero();
	int m_timer = 0;
	bool m_deleteEenmyFlug = false;
	int m_bulletPower = 0;
	int m_knockDownEnemyNum = 0; //ì|Ç∑ìGÇÃêîÅB
	CQuaternion m_rotation = CQuaternion::Identity();
	PhysicsGhostObject m_GhostObject;
	CharacterController m_charaCon;
	CVector3 m_hitJudgmentRange = CVector3::Zero(); //íeÇÃìñÇΩÇËîªíËÇÃîÕàÕÅB
};


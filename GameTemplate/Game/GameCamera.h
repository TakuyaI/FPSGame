#pragma once
class Game;
class Player;
class EnemyGenerator;
class Enemy;
#include "IGameObject.h"
#include "Player.h"
#include "Enemy.h"
#include "EnemyGenerator.h"
class GameCamera : public IGameObject
{
public:
	GameCamera();
	~GameCamera();

	void ToTarget();

	void Update();
	void Render();
	/// <summary>
	/// 注視点の座標を取得。
	/// </summary>
	CVector3 GetTarget()
	{
		return m_target;
	}
	/// <summary>
	/// 視点の座標を取得。
	/// </summary>
	CVector3 GetPosition()
	{
		return m_position;
	}
	CVector3 GetToTargetPos()
	{
		return m_toTargetPos;
	}

	CVector3 GetTargetPos()
	{
		return m_target;
	}

	bool LockOnTargetFlug()
	{
		return m_lockOnTargetFlug;
	}
	
	CVector3 GetToTarget()
	{
		return m_toTarget;
	}
	const CQuaternion GetRotation() const
	{
		return m_rotation;
	}
private:
	Player* m_player;
	Enemy* m_enemy;
	EnemyGenerator* m_enemyGen;
	Gun* m_gun;
	Game* m_game;

	CVector3 m_toTargetPos = CVector3::Zero();
	CVector3 m_enemyPos = CVector3::Zero();
	CVector3 m_position = CVector3::Zero();     //視点。
	CVector3 m_target = CVector3::Zero();       //注視点。
	CVector3 m_toTarget = CVector3::Zero();
	float m_angle = 0.0f;                             //回転。
	float m_angle2 = 0.0f;
	CQuaternion m_rotation;
	bool m_lockOnTargetFlug = false;

	CVector3 m_cameraOffset = { 0.0f, 100.0f, 0.0f };

};


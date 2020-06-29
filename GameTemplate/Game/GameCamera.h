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

	/// <summary>
	/// リコイル。
	/// </summary>
	void Recoil();

	bool Start();
	void Update();
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
	
	CVector3 GetToTarget()
	{
		return m_toTarget;
	}
	const CQuaternion GetRotation() const
	{
		return m_rotation;
	}
	CVector3 GetmBazePos()
	{
		return m_bazePos;
	}
	void SetAngle2(float angle2)
	{
		m_angle2 = angle2;
	}
	float GetAngle2()
	{
		return m_angle2;
	}
	void SetRotSpeed(float speed)
	{
		m_rotSpeed = speed;
	}
	float GetRotSpeed()
	{
		return m_rotSpeed;
	}
	void SetGameCameraViewAngle(float viewAngle)
	{
		m_viewAngle = viewAngle;
	}
	float GetGameCameraViewAngle()
	{
		return m_viewAngle;
	}

	void SetShotFlug(float a)
	{
		m_shotFlug = a;
	}
private:
	Player* m_player;
	Enemy* m_enemy;
	EnemyGenerator* m_enemyGen;
	Game* m_game;

	CVector3 m_toTargetPos = CVector3::Zero();
	CVector3 m_enemyPos = CVector3::Zero();
	CVector3 m_position = CVector3::Zero();     //視点。
	CVector3 m_target = CVector3::Zero();       //注視点。
	CVector3 m_toTarget = CVector3::Zero();
	float m_angle = 0.0f;                             //回転。
	float m_angle2 = 0.0f;
	CQuaternion m_rotation;
	float m_rotSpeed = 3.0f; //カメラが回転するスピード。

	CVector3 m_cameraOffset = { 0.0f, 150.0f, 0.0f };

	int m_count = 0;
	CVector3 m_zoomV = CVector3::Zero();
	CVector3 m_bazePos = CVector3::Zero();//ベースとなるカメラの座標。
	float m_viewAngle = 60.0f;//画角。
	
	bool m_shotFlug = false; //弾を撃ったかどうか。
	float m_shotCount = 0.0f;//弾を撃った時にカウントする。

	float m_width = 0.0f;//リコイルの横幅。
};


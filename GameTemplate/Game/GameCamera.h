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
	/// ���R�C���B
	/// </summary>
	void Recoil();

	bool Start();
	void Update();
	/// <summary>
	/// �����_�̍��W���擾�B
	/// </summary>
	CVector3 GetTarget()
	{
		return m_target;
	}
	/// <summary>
	/// ���_�̍��W���擾�B
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
	CVector3 m_position = CVector3::Zero();     //���_�B
	CVector3 m_target = CVector3::Zero();       //�����_�B
	CVector3 m_toTarget = CVector3::Zero();
	float m_angle = 0.0f;                             //��]�B
	float m_angle2 = 0.0f;
	CQuaternion m_rotation;
	float m_rotSpeed = 3.0f; //�J��������]����X�s�[�h�B

	CVector3 m_cameraOffset = { 0.0f, 150.0f, 0.0f };

	int m_count = 0;
	CVector3 m_zoomV = CVector3::Zero();
	CVector3 m_bazePos = CVector3::Zero();//�x�[�X�ƂȂ�J�����̍��W�B
	float m_viewAngle = 60.0f;//��p�B
	
	bool m_shotFlug = false; //�e�����������ǂ����B
	float m_shotCount = 0.0f;//�e�����������ɃJ�E���g����B

	float m_width = 0.0f;//���R�C���̉����B
};


#pragma once
//class EnemyGenerator;
//class Enemy;
#include "character/CharacterController.h"
#include "IGameObject.h"
#include "GameCamera.h"
class GameCamera;
class Player:public IGameObject
{
public:
	Player();
	~Player();
	void Update();
	void Render();

	/// <summary>
	/// ���W��ݒ�B
	/// </summary>
	void SetPosition(CVector3 pos)
	{
		m_position = pos;
	}
	/// <summary>
	/// ���W���擾�B
	/// </summary>
	CVector3 GetPosition()
	{
		return m_position;
	}
	void SetMoveSpeed(CVector3 movespeed)
	{
		m_moveSpeed = movespeed;
	}
	CVector3 GetMoveSpeed()
	{
		return m_moveSpeed;
	}
	bool GetJumpFlug()
	{
		return m_jumpFlag;
	}
	void SetPushAwayFlug(bool t)
	{
		m_pushAwayFlug = t;
	}
	bool GetPushAwayFlug()
	{
		return m_pushAwayFlug;
	}
private:
	GameCamera* m_gameCamera;
	EnemyGenerator* m_enemyGen;
	Enemy* m_enemy;

	CVector3 m_position = CVector3::Zero(); //���W�B
	SkinModel m_model;						//�X�L�����f���B
	float ySpeed = 0.0f;                    //�d�́B
	CVector3 m_moveSpeed = CVector3::Zero();//���[�u�X�s�[�h�B
	CharacterController m_charaCon;         //�L�����N�^�[�R���g���[���[�B
	bool m_jumpFlag = false;                     //�W�����v�t���O�B
	float m_playerSpeed = 20.0f;            //Player�̃X�s�[�h�B
	int a = 0;
	bool m_pushAwayFlug = false;
};
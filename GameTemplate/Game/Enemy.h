#pragma once
//class EnemyGenerator;
#include "IGameObject.h"
#include "Player.h"
class Enemy : public IGameObject
{
public:
	Enemy();
	~Enemy();

	void Loitering();
	void Tracking();
	void Attack();

	void Update();
	void Render();

	void SetPosition(CVector3 pos)
	{
		m_position = pos;
	}
	CVector3 GetPosition()
	{
		return m_position;
	}
	void SetInitPos(CVector3 initpos)
	{
		m_initPos = initpos;
	}
	CVector3 GetInitPos()
	{
		return m_initPos;
	}
	bool GetAttackFlug()
	{
		return m_attackFlug;
	}
	void SetEnemyHp(int enemyhp)
	{
		m_enemyHp = enemyhp;
	}
	int GetEnemyHp()
	{
		return m_enemyHp;
	}
	CharacterController CharaCon()
	{
		return m_charaCon;
	}
	float GetEnemyAttackPow()
	{
		return m_enemyAttackPow;
	}
	float GetDamage()
	{
		return m_damage;
	}
	void SetDamageFlug(bool damageFlug)
	{
		m_damageFlug = damageFlug;
	}
	bool GetDamageFlug()
	{
		return m_damageFlug;
	}

private:
	SkinModel m_model;                                //�X�L�����f���B
	Player* m_player;                                 //Player�̃C���X�^���X�B
	EnemyGenerator* enemyGen;                         //EnemyGenerator�̃C���X�^���X�B

	CVector3 m_moveSpeed = CVector3::Zero();          //���[�u�X�s�[�h�B
	CVector3 m_position = CVector3::Zero();           //���W�B
	CVector3 m_initPos = CVector3::Zero();            //�������W�B
	CVector3 m_toPlayerVec = CVector3::Zero();        //Enemy����Player�֌������x�N�g���B
	CQuaternion m_rotation = CQuaternion::Identity(); //��]�B
	CharacterController m_charaCon;                   //�L�����N�^�[�R���g���[���[�B
	int m_state = 0;                                  //Enemy�̏�ԁB
	bool m_attackFlug = false;                        //�U���t���O�B
	float m_pushAwaySpeed = 100.0f;                   //�˂��������X�y�[�h�B
	bool m_endPushAwayflug = false;                   //�˂������I�������ǂ����B
	int m_enemyHp = 50;                               //Enemy��HP�B
	float m_playerHp = 100.0f;
	int m_AttackTimer = 0;
	float m_enemyAttackPow = 10.0f;
	float m_damage = 0.0f;
	bool m_damageFlug = false;
};


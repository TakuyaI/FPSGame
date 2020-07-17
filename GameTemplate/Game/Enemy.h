#pragma once
//class EnemyGenerator;
#include "IEnemyObject.h"
class Enemy : public IEnemyObject
{
public:
	Enemy();
	~Enemy();

	bool Start();
	void Update();
	void SetRegistShadowCaster();
	void Render();

	void Saty(CVector3* position, CVector3* initPos);
	void Attack(float AttackPow);

	void SetPosition(CVector3 pos)
	{
		m_position = pos;
	}
	CVector3 GetPosition()
	{
		return m_position;
	}
	void SetRotation(CQuaternion rotation)
	{
		m_rotation = rotation;
	}
	CharacterController* CharaCon()
	{
		return &m_charaCon;
	}
private:
	SkinModel m_model;                                //�X�L�����f���B
	CVector3 m_position = CVector3::Zero();
	CVector3 m_initPos = CVector3::Zero();
	CQuaternion m_rotation = CQuaternion::Identity();
	float m_attackPow = 10.0f; //�U���́B
	float m_speed = 10.0f;
	CharacterController m_charaCon;                   //�L�����N�^�[�R���g���[���[�B
	AnimationClip m_animationClip[enAnimationCrip_Num]; //�A�j���[�V�����N���b�v�B
	Animation m_animation;                    //�A�j���[�V�����B
	int m_deathAnimTime = 60; //���S���̃A�j���[�V�����̎��ԁB
};


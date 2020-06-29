#pragma once
#include "IEnemyObject.h"
#include "Game.h"
class DogEnemy : public IEnemyObject
{
public:
	DogEnemy();
	~DogEnemy();

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
	CQuaternion m_rotation = CQuaternion::Identity();
	CharacterController m_charaCon;                   //�L�����N�^�[�R���g���[���[�B
	AnimationClip m_animationClip[enAnimationCrip_Num]; //�A�j���[�V�����N���b�v�B
	Animation m_animation;                    //�A�j���[�V�����B
	int m_deathAnimTime = 10; //���S���̃A�j���[�V�����̎��ԁB
};


#pragma once
#include "IEnemyObject.h"
class DogEnemy : public IEnemyObject
{
public:
	DogEnemy();
	~DogEnemy();

	bool Start();
	void Update();
	void Render();

private:
	SkinModel m_model;                                //�X�L�����f���B
	CVector3 m_position = CVector3::Zero();
	CQuaternion m_rotation = CQuaternion::Identity();
	CharacterController m_charaCon;                   //�L�����N�^�[�R���g���[���[�B
	AnimationClip m_animationClip[enAnimationCrip_Num]; //�A�j���[�V�����N���b�v�B
	Animation m_animation;                    //�A�j���[�V�����B
};


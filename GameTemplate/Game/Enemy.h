#pragma once
#include "IEnemyObject.h"
class Enemy : public IEnemyObject
{
public:
	/// <summary>
	/// �R���X�g���N�^�B
	/// </summary>
	Enemy();
	/// <summary>
	/// �f�X�g���N�^�B
	/// </summary>
	~Enemy();
	/// <summary>
	/// �X�^�[�g�֐��B
	/// </summary>
	/// <returns></returns>
	bool Start();
	/// <summary>
	/// �X�V�֐��B
	/// </summary>
	void Update();
	/// <summary>
	/// �V���h�E�L���X�^�[�֐��B
	/// </summary>
	void SetRegistShadowCaster();
	/// <summary>
	/// 3D�`��֐��B
	/// </summary>
	void Render();
	/// <summary>
	/// �ҋ@���B
	/// </summary>
	/// <param name="position">���W�B</param>
	/// <param name="initPos">�������W�B</param>
	void Saty(CVector3* position, CVector3* initPos);
	/// <summary>
	/// �U���B
	/// </summary>
	/// <param name="AttackPow">�U���́B</param>
	void Attack(float AttackPow);
	/// <summary>
	/// ���W��ݒ�B
	/// </summary>
	/// <param name="pos">���W�B</param>
	void SetPosition(CVector3 pos)
	{
		m_position = pos;
	}
	/// <summary>
	/// ���W��Ԃ��B
	/// </summary>
	/// <returns></returns>
	CVector3 GetPosition()
	{
		return m_position;
	}
	/// <summary>
	///��]��ݒ�B
	/// </summary>
	/// <param name="rotation">��]�B</param>
	void SetRotation(CQuaternion rotation)
	{
		m_rotation = rotation;
	}
	/// <summary>
	/// �L�����R����Ԃ��B
	/// </summary>
	/// <returns></returns>
	CharacterController* CharaCon()
	{
		return &m_charaCon;
	}
private:
	SkinModel m_model;                                  //�X�L�����f���B
	CVector3 m_position = CVector3::Zero();             //���W�B
	CVector3 m_initPos = CVector3::Zero();              //�G�̏������W�B
	CQuaternion m_rotation = CQuaternion::Identity();   //��]�B
	float m_attackPow = 10.0f;                          //�U���́B
	float m_speed = 10.0f;                              //���x�B
	CharacterController m_charaCon;                     //�L�����N�^�[�R���g���[���[�B
	AnimationClip m_animationClip[enAnimationCrip_Num]; //�A�j���[�V�����N���b�v�B
	Animation m_animation;                              //�A�j���[�V�����B
	int m_deathAnimTime = 60;                           //���S���̃A�j���[�V�����̎��ԁB
	const float m_controllerRadius = 50.0f;             //�L�����R���̔��a�B
	const float m_controllerHeight = 250.0f;            //�L�����R���̍����B
	const float m_initPosRange = 15.0f;                 //�������W�͈́B
	const int m_AttackTime = 30;                        //�U������܂ł̊Ԋu�B
};


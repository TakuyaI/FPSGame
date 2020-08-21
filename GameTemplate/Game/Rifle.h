#pragma once
#include "IGunObject.h"
class Rifle : public IGunObject
{
public:
	/// <summary>
	/// �R���X�g���N�^�B
	/// </summary>
	Rifle();
	/// <summary>
	/// �f�X�g���N�^�B
	/// </summary>
	~Rifle();
	/// <summary>
	/// �X�V�֐��B
	/// </summary>
	void Update();
	/// <summary>
	/// �V���h�E�L���X�^�[�֐��B
	/// </summary>
	void SetRegistShadowCaster();
	/// <summary>
	/// 3D�`��B
	/// </summary>
	void Render();
	/// <summary>
	/// 2D�`��B
	/// </summary>
	void PostRender();
	/// <summary>
	/// �e����ݒ肷��B
	/// </summary>
	/// <param name="ammo"></param>
	void SetGunAmmo(int ammo)
	{
		m_ammo = ammo;
	}
	/// <summary>
	/// �e����Ԃ��B
	/// </summary>
	/// <returns></returns>
	int GetAmmo()
	{
		return m_ammo;
	}
	/// <summary>
	/// ��]��Ԃ��B
	/// </summary>
	/// <returns></returns>
	CQuaternion GetRotation()
	{
		return m_rotation;
	}
	/// <summary>
	/// �e�̓����蔻��͈̔͂�Ԃ��B
	/// </summary>
	/// <returns></returns>
	CVector3 GetHitJudgmentRange()
	{
		return m_hitJudgmentRange;
	}
	/// <summary>
	/// �e�̉��ƃG�t�F�N�g���ĂԊ֐��B
	/// </summary>
	/// <param name="position">���W�B</param>
	/// <param name="rotation">��]�B</param>
	void OnShot(CVector3* position, CQuaternion* rotation);
	/// <summary>
	/// �G�C���B
	/// </summary>
	/// <param name="position">���W�B</param>
	/// <param name="rotation">��]�B</param>
	/// <param name="aimingPos">�G�C�����Ă���Ƃ��̍��W�B</param>
	/// <param name="notAimaos">�G�C�����Ă��Ȃ��Ƃ��̍��W�B</param>
	void Aim(CVector3* position, CQuaternion* rotation, CVector3* aimingPos, CVector3* notAimaos);
private:
	SkinModel m_model;                                                 //�X�L�����f���B
	CVector3 m_positon = CVector3::Zero();                             //���W�B
	CQuaternion m_rotation = CQuaternion::Identity();                  //��]�B
	CVector3 m_scale = CVector3::One();                                //�T�C�Y�B
	int m_ammo = 0;                                                    //�e���B
	int m_loading = 0;                                                 //���U�e���B
	int m_maxLoading = 50;                                             //�ő呕�U�e���B
	int m_bulletIntervalTime = 3;                                      //�e�̃C���^�[�o���B
	float m_bulletMoveSpeed = 400.0f;                                  //�e�̑��x�B
	float m_reaction = 1.0f;                                           //�e�̔����B
	int m_reloadTime = 60;                                             //�����[�h���ԁB
	CSoundSource m_gunShot;                                            //�e���̉��B
	CVector3 m_aimingPos = { 0.0f, -13.0f, 10.0f };                    //�G�C�����Ă���Ƃ��̍��W�B
	CVector3 m_notAimPos = { 8.0f, -15.0f, 0.0f };                     //�G�C�����Ă��Ȃ��Ƃ��̍��W�B
	CVector3 m_hitJudgmentRange = { 50.0f, 50.0f, m_bulletMoveSpeed }; //�e�̓����蔻��͈̔́B
	AnimationClip m_animationClip[enAnimationCrip_num];                //�A�j���[�V�����N���b�v�B
	Animation m_animation;                                             //�A�j���[�V�����B
	Effekseer::Effect* m_sampleEffect = nullptr;
};


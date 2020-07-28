#pragma once
#include "IGunObject.h"
class Shotgun : public IGunObject
{
public:
	Shotgun();
	~Shotgun();

	void Update();
	void SetRegistShadowCaster();
	void Render();
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
	void OnShot(CVector3* position, CQuaternion* rotation);
	void Aim(CVector3* position, CQuaternion* rotation, CVector3* aimingPos, CVector3* notAimaos);
private:

	SkinModel m_model;
	CVector3 m_positon = CVector3::Zero();            //���W�B
	CQuaternion m_rotation = CQuaternion::Identity(); //��]�B
	CVector3 m_scale = CVector3::One();               //�T�C�Y�B
	int m_ammo = 0;                                   //�e���B
	int m_loading = 0;                                //���U�e���B
	int m_maxLoading = 2;                            //�ő呕�U�e���B
	int m_bulletIntervalTime = 20;                     //�e�̃C���^�[�o���B
	float m_bulletMoveSpeed = 300.0f;                 //�e�̑��x�B
	float m_reaction = 10.0f;                          //�e�̔����B
	int m_reloadTime = 120;                            //�����[�h���ԁB
	CSoundSource m_gunShot; //�e���̉��B
	CVector3 m_aimingPos = { 0.0f, -7.0f, 10.0f };
	CVector3 m_notAimPos = { 15.0f, -8.0f, 0.0f };
	Effekseer::Effect* m_sampleEffect = nullptr;
	CVector3 m_hitJudgmentRange = { 200.0f, 200.0f, m_bulletMoveSpeed }; //�e�̓����蔻��͈̔́B

};


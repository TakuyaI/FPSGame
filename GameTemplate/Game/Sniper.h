#pragma once
#include "IGunObject.h"
class Sniper : public IGunObject
{
public:
	Sniper();
	~Sniper();
	void Update();
	void SetRegistShadowCaster();
	void Render();
	void PostRender();

	int GetAmmo()
	{
		return m_ammo;
	}
	int GetBlaze()
	{
		return m_loading;
	}
	CQuaternion GetRotation()
	{
		return m_rotation;
	}
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
	int m_maxLoading = 4;                            //�ő呕�U�e���B
	int m_bulletIntervalTime = 30;                     //�e�̃C���^�[�o���B
	float m_bulletMoveSpeed = 700.0f;                 //�e�̑��x�B
	float m_reaction = 10.0f;                          //�e�̔����B
	int m_reloadTime = 90;                            //�����[�h���ԁB
	CSoundSource m_gunShot; //�e���̉��B
	CVector3 m_aimingPos = { -1.5f, -14.0f, 35.0f };
	CVector3 m_notAimPos = { 15.0f, -15.0f, 20.0f };
	Effekseer::Effect* m_sampleEffect = nullptr;
	CVector3 m_hitJudgmentRange = { 20.0f, 20.0f, m_bulletMoveSpeed }; //�e�̓����蔻��͈̔́B

	Sprite m_aim;
	bool m_flug = false;
};


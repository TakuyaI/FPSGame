#pragma once
class GunGenerator;
#include "IGunObject.h"
#include "GunGenerator.h"
class Rifle : public IGunObject
{
public:
	Rifle();
	~Rifle();

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
	CVector3 GetPosition()
	{
		return m_positon;
	}
	CQuaternion GetRotation()
	{
	return m_rotation;
	}
	void OnShot(CVector3* position, CQuaternion* rotation);

	void Aim(CVector3* position, CQuaternion* rotation, CVector3* aimingPos, CVector3* notAimaos);
private:

	SkinModel m_model;
	GunGenerator* m_gunGen;
	CVector3 m_positon = CVector3::Zero();            //���W�B
	CQuaternion m_rotation = CQuaternion::Identity(); //��]�B
	CVector3 m_scale = CVector3::One();               //�T�C�Y�B
	int m_ammo = 0;                                   //�e���B
	int m_loading = 0;                                //���U�e���B
	int m_maxLoading = 50;                            //�ő呕�U�e���B
	int m_bulletIntervalTime = 3;                     //�e�̃C���^�[�o���B
	float m_bulletMoveSpeed = 400.0f;                 //�e�̑��x�B
	float m_reaction = 1.0f;                          //�e�̔����B
	int m_reloadTime = 80;                            //�����[�h���ԁB
	CSoundSource m_gunShot; //�e���̉��B
	CVector3 m_aimingPos = { 0.0f, -12.0f, 10.0f };
	CVector3 m_notAimPos = { 15.0f, -15.0f, 0.0f };//{ 15.0f, -15.0f, 0.0f };
	Effekseer::Effect* m_sampleEffect = nullptr;
};


#pragma once
class GunGenerator;
#include "IGunObject.h"
#include "GunGenerator.h"
class Sniper : public IGunObject
{
public:
	Sniper();
	~Sniper();
	void Update();
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
	/*CQuaternion GetRotation()
	{
	return m_rotation;
	}*/
private:

	SkinModel m_model;
	GunGenerator* m_gunGen;
	CVector3 m_positon = CVector3::Zero();            //���W�B
	CQuaternion m_rotation = CQuaternion::Identity(); //��]�B
	CVector3 m_scale = CVector3::One();               //�T�C�Y�B
	int m_ammo = 0;                                   //�e���B
	int m_loading = 0;                                //���U�e���B
	int m_maxLoading = 4;                            //�ő呕�U�e���B
	int m_bulletIntervalTime = 30;                     //�e�̃C���^�[�o���B
	float m_bulletMoveSpeed = 500.0f;                 //�e�̑��x�B
	float m_reaction = 10.0f;                          //�e�̔����B
	int m_reloadTime = 90;                            //�����[�h���ԁB
	CSoundSource m_gunShot; //�e���̉��B
};


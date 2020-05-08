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
	CVector3 m_positon = CVector3::Zero();            //座標。
	CQuaternion m_rotation = CQuaternion::Identity(); //回転。
	CVector3 m_scale = CVector3::One();               //サイズ。
	int m_ammo = 0;                                   //弾数。
	int m_loading = 0;                                //装填弾数。
	int m_maxLoading = 50;                            //最大装填弾数。
	int m_bulletIntervalTime = 3;                     //弾のインターバル。
	float m_bulletMoveSpeed = 400.0f;                 //弾の速度。
	float m_reaction = 1.0f;                          //銃の反動。
	int m_reloadTime = 60;                            //リロード時間。
	CSoundSource m_gunShot; //銃声の音。
};


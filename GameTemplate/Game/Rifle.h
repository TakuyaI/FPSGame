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
	CVector3 m_positon = CVector3::Zero();            //座標。
	CQuaternion m_rotation = CQuaternion::Identity(); //回転。
	CVector3 m_scale = CVector3::One();               //サイズ。
	int m_ammo = 0;                                   //弾数。
	int m_loading = 0;                                //装填弾数。
	int m_maxLoading = 50;                            //最大装填弾数。
	int m_bulletIntervalTime = 3;                     //弾のインターバル。
	float m_bulletMoveSpeed = 400.0f;                 //弾の速度。
	float m_reaction = 1.0f;                          //銃の反動。
	int m_reloadTime = 80;                            //リロード時間。
	CSoundSource m_gunShot; //銃声の音。
	CVector3 m_aimingPos = { 0.0f, -12.0f, 10.0f };
	CVector3 m_notAimPos = { 15.0f, -15.0f, 0.0f };//{ 15.0f, -15.0f, 0.0f };
	Effekseer::Effect* m_sampleEffect = nullptr;
};


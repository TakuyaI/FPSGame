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
	CVector3 m_positon = CVector3::Zero();            //座標。
	CQuaternion m_rotation = CQuaternion::Identity(); //回転。
	CVector3 m_scale = CVector3::One();               //サイズ。
	int m_ammo = 0;                                   //弾数。
	int m_loading = 0;                                //装填弾数。
	int m_maxLoading = 4;                            //最大装填弾数。
	int m_bulletIntervalTime = 30;                     //弾のインターバル。
	float m_bulletMoveSpeed = 700.0f;                 //弾の速度。
	float m_reaction = 10.0f;                          //銃の反動。
	int m_reloadTime = 90;                            //リロード時間。
	CSoundSource m_gunShot; //銃声の音。
	CVector3 m_aimingPos = { -1.5f, -14.0f, 35.0f };
	CVector3 m_notAimPos = { 15.0f, -15.0f, 20.0f };
	Effekseer::Effect* m_sampleEffect = nullptr;
	CVector3 m_hitJudgmentRange = { 20.0f, 20.0f, m_bulletMoveSpeed }; //弾の当たり判定の範囲。

	Sprite m_aim;
	bool m_flug = false;
};


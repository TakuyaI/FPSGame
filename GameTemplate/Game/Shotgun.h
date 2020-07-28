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
	/// 弾数を設定する。
	/// </summary>
	/// <param name="ammo"></param>
	void SetGunAmmo(int ammo)
	{
		m_ammo = ammo;
	}
	/// <summary>
	/// 弾数を返す。
	/// </summary>
	/// <returns></returns>
	int GetAmmo()
	{
		return m_ammo;
	}
	/// <summary>
	/// 回転を返す。
	/// </summary>
	/// <returns></returns>
	CQuaternion GetRotation()
	{
		return m_rotation;
	}
	/// <summary>
	/// 弾の当たり判定の範囲を返す。
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
	CVector3 m_positon = CVector3::Zero();            //座標。
	CQuaternion m_rotation = CQuaternion::Identity(); //回転。
	CVector3 m_scale = CVector3::One();               //サイズ。
	int m_ammo = 0;                                   //弾数。
	int m_loading = 0;                                //装填弾数。
	int m_maxLoading = 2;                            //最大装填弾数。
	int m_bulletIntervalTime = 20;                     //弾のインターバル。
	float m_bulletMoveSpeed = 300.0f;                 //弾の速度。
	float m_reaction = 10.0f;                          //銃の反動。
	int m_reloadTime = 120;                            //リロード時間。
	CSoundSource m_gunShot; //銃声の音。
	CVector3 m_aimingPos = { 0.0f, -7.0f, 10.0f };
	CVector3 m_notAimPos = { 15.0f, -8.0f, 0.0f };
	Effekseer::Effect* m_sampleEffect = nullptr;
	CVector3 m_hitJudgmentRange = { 200.0f, 200.0f, m_bulletMoveSpeed }; //弾の当たり判定の範囲。

};


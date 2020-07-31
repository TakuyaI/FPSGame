#pragma once
#include "IGunObject.h"
class Sniper : public IGunObject
{
public:
	/// <summary>
	/// コンストラクタ。
	/// </summary>
	Sniper();
	/// <summary>
	/// デストラクタ。
	/// </summary>
	~Sniper();
	/// <summary>
	/// 更新関数。
	/// </summary>
	void Update();
	/// <summary>
	/// シャドウキャスター関数。
	/// </summary>
	void SetRegistShadowCaster();
	/// <summary>
	/// 3D描画。
	/// </summary>
	void Render();
	/// <summary>
	/// 2D描画。
	/// </summary>
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
	/// <summary>
	/// 銃の音とエフェクトを呼ぶ関数。
	/// </summary>
	/// <param name="position">座標。</param>
	/// <param name="rotation">回転。</param>
	void OnShot(CVector3* position, CQuaternion* rotation);
	/// <summary>
	/// エイム。
	/// </summary>
	/// <param name="position">座標。</param>
	/// <param name="rotation">回転。</param>
	/// <param name="aimingPos">エイムしているときの座標。</param>
	/// <param name="notAimaos">エイムしていないときの座標。</param>
	void Aim(CVector3* position, CQuaternion* rotation, CVector3* aimingPos, CVector3* notAimaos);
private:

	SkinModel m_model;                                                 //スキンモデル。
	CVector3 m_positon = CVector3::Zero();                             //座標。
	CQuaternion m_rotation = CQuaternion::Identity();                  //回転。
	CVector3 m_scale = CVector3::One();                                //サイズ。
	int m_ammo = 0;                                                    //弾数。
	int m_loading = 0;                                                 //装填弾数。
	int m_maxLoading = 4;                                              //最大装填弾数。
	int m_bulletIntervalTime = 30;                                     //弾のインターバル。
	float m_bulletMoveSpeed = 700.0f;                                  //弾の速度。
	float m_reaction = 10.0f;                                          //銃の反動。
	int m_reloadTime = 80;                                             //リロード時間。
	CSoundSource m_gunShot;                                            //銃声の音。
	CVector3 m_aimingPos = { -1.5f, -14.0f, 35.0f };                   //エイムしているときの座標。
	CVector3 m_notAimPos = { 15.0f, -15.0f, 35.0f };                   //エイムしていないときの座標。
	CVector3 m_hitJudgmentRange = { 20.0f, 20.0f, m_bulletMoveSpeed }; //弾の当たり判定の範囲。
	Sprite m_aim;                                                      //スコープの画像。
	bool m_aimFlug = false;                                            //エイムしたかどうか。
	AnimationClip m_animationClip[enAnimationCrip_num];                //アニメーションクリップ。
	Animation m_animation;                                             //アニメーション。
	Effekseer::Effect* m_sampleEffect = nullptr;
};


#pragma once
#include "IEnemyObject.h"
class DogEnemy : public IEnemyObject
{
public:
	/// <summary>
	/// コンストラクタ。
	/// </summary>
	DogEnemy();
	/// <summary>
	/// デストラクタ。
	/// </summary>
	~DogEnemy();
	/// <summary>
	/// スタート関数。
	/// </summary>
	/// <returns></returns>
	bool Start();
	/// <summary>
	/// 更新関数。
	/// </summary>
	void Update();
	/// <summary>
	/// シャドウキャスター関数。
	/// </summary>
	void SetRegistShadowCaster();
	/// <summary>
	/// 3D描画関数。
	/// </summary>
	void Render();
	/// <summary>
	/// 待機中。
	/// </summary>
	/// <param name="position">座標。</param>
	/// <param name="initPos">初期座標。</param>
	void Saty(CVector3* position, CVector3* initPos);
	/// <summary>
	/// 攻撃。
	/// </summary>
	/// <param name="AttackPow">攻撃力。</param>
	void Attack(float AttackPow);
	/// <summary>
	/// 座標を設定。
	/// </summary>
	/// <param name="pos">座標。</param>
	void SetPosition(CVector3 pos)
	{
		m_position = pos;
	}
	/// <summary>
	/// 座標を返す。
	/// </summary>
	/// <returns></returns>
	CVector3 GetPosition()
	{
		return m_position;
	}
	/// <summary>
	///回転を設定。
	/// </summary>
	/// <param name="rotation">回転。</param>
	void SetRotation(CQuaternion rotation)
	{
		m_rotation = rotation;
	}
	/// <summary>
	/// キャラコンを返す。
	/// </summary>
	/// <returns></returns>
	CharacterController* CharaCon()
	{
		return &m_charaCon;
	}
private:
	SkinModel m_model;                                  //スキンモデル。
	CVector3 m_position = CVector3::Zero();             //座標。
	CVector3 m_initPos = CVector3::Zero();              //敵の初期座標。
	CQuaternion m_rotation = CQuaternion::Identity();   //回転。
	float m_attackPow = 7.0f;                           //攻撃力。
	float m_speed = 20.0f;                              //速度。
	CharacterController m_charaCon;                     //キャラクターコントローラー。
	AnimationClip m_animationClip[enAnimationCrip_Num]; //アニメーションクリップ。
	Animation m_animation;                              //アニメーション。
	int m_deathAnimTime = 10;                           //死亡時のアニメーションの時間。
	const float m_controllerRadius = 50.0f;             //キャラコンの半径。
	const float m_controllerHeight = 150.0f;            //キャラコンの高さ。
	const float m_lockOnRange = 1500.0f;                //ロックオン範囲。
	const float m_initPosRange = 15.0f;                 //初期座標範囲。
	const int m_AttackTime = 20;                        //攻撃するまでの間隔。
};


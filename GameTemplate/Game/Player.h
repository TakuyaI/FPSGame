#pragma once
class Sprite;
class Enemy;
#include "IGameObject.h"
#include "GameCamera.h"
#include "Sprite.h"
#include "FontRender.h"
#include "Enemy.h"
class GameCamera;
class Player:public IGameObject
{
public:
	/// <summary>
	/// コンストラクタ。
	/// </summary>
	Player();
	/// <summary>
	/// デストラクタ。
	/// </summary>
	~Player();
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
	/// 3D描画。
	/// </summary>
	void Render();
	/// <summary>
	/// 2D描画。
	/// </summary>
	void PostRender();
	/// <summary>
	/// 座標を設定する。
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
	/// 回転を設定する。
	/// </summary>
	/// <param name="rotation">回転。</param>
	void SetRotation(CQuaternion rotation)
	{
		m_rotation = rotation;
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
	/// 敵を突き飛ばしたかどうかのフラグを設定する。
	/// </summary>
	/// <param name="flug">フラグ。</param>
	void SetPushAwayFlug(bool flug)
	{
		m_pushAwayFlug = flug;
	}
	/// <summary>
	/// 敵を突き飛ばしたかどうかのフラグを返す。
	/// </summary>
	/// <returns></returns>
	bool GetPushAwayFlug()
	{
		return m_pushAwayFlug;
	}
	/// <summary>
	/// プレイヤーが受けるダメージ量を設定する。
	/// </summary>
	/// <param name="d">ダメージ量。</param>
	void SetDamage(float d)
	{
		m_damage = d;
	}
	/// <summary>
	/// プレイヤーが受けるダメージ量を返す。
	/// </summary>
	/// <returns></returns>
	float GetDamage()
	{
		return m_damage;
	}
	/// <summary>
	/// HPの変化量を設定する。
	/// </summary>
	/// <param name="hpChanges">HPの変化量。</param>
	void SetHpChanges(float hpChanges)
	{
		m_hpChanges = hpChanges;
	}
	/// <summary>
	/// ダメージを受けたかどうかのフラグを設定する。
	/// </summary>
	/// <param name="damageFlug">フラグ。</param>
	void SetDamageFlug(bool damageFlug) 
	{
		m_damageFlug = damageFlug;
	}
	/// <summary>
	/// ダメージを受けたかどうかのフラグを返す。
	/// </summary>
	/// <returns></returns>
	bool GetDamageFlug()
	{
		return m_damageFlug;
	}
	/// <summary>
	/// プレイヤーが死亡したかどうかのフラグを返す。
	/// </summary>
	/// <returns></returns>
	bool GetDeathFlug()
	{
		return m_deathFlug;
	}
	/// <summary>
	/// Playerが止まっているかどうかを設定する。
	/// </summary>
	/// <param name="flug">フラグ。</param>
	void SetStopFlug(bool flug)
	{
		m_stopFlug = flug;
	}
	/// <summary>
	/// Playerが止まっているかどうかを返す。
	/// </summary>
	/// <returns></returns>
	bool GetStopFlug()
	{
		return m_stopFlug;
	}
	/// <summary>
	/// プレイヤーのHPを返す。
	/// </summary>
	/// <returns></returns>
	float GetPlayerHp()
	{
		return m_playerHp;
	}
private:
	SkinModel m_model;					                 	//スキンモデル。
	GameCamera* m_gameCamera;                               //GameCameraのインスタンス。
	Enemy* m_enemy;                                         //Enemyのインスタンス。
	CVector3 m_position = CVector3::Zero();                 //座標。
	CQuaternion m_rotation = CQuaternion::Identity();       //回転。
	CVector3 m_moveSpeed = CVector3::Zero();                //ムーブスピード。
	CharacterController m_charaCon;                         //キャラクターコントローラー。
	float ySpeed = 0.0f;                                    //重力。
	float m_playerSpeed = 20.0f;                            //Playerのスピード。
	float m_playerHp = 100.0f;                              //プレイヤーのHP。
	float m_pushAwayNum = 0;                                //一定値になったら、敵を突き飛ばす。
	float m_hpChanges = 0;                                  //HPの変化量。
	float m_damage = 0.0f;                                  //プレイヤーが受けるダメージ量。
	Sprite m_damageSprite;                                  //ダメージを受けたときに表示されるスプライト。
	Sprite m_greenSprite;                                   //HPバーのスプライト。
	Sprite m_hpBlackSprite;                                 //HPバーの後ろのバーのスプライト。
	CVector3 m_greenScale = CVector3::One();                //HPバーのスプライトの大きさ。
	CVector3 m_blackScale = CVector3::One();                //HPバーの後ろのバーのスプライトの大きさ。
	CVector3 m_gaugePos = { -500.0f, -300.0f, 0.0f };       //HPバーのスプライトの座標。
	CVector3 m_blackGaugePos = { -500.0f, -301.0f, 0.0f };  //HPバーの後ろのバーのスプライト座標。
	bool m_deathFlug = false;                               //プレイヤーが死亡したかどうか。
	bool m_stopFlug = false;                                //Playerが止まっているかどうか。
	bool m_damageFlug = false;                              //ダメージを受けたかどうか。
	bool m_moveStickFlug = false;                           //スティックをうごかしたかどうか。スティックを左右に動かすとtrue、上下に動かすとfalseになる。
	bool m_pushAwayFlug = false;                            //敵を突き飛ばしたかどうか。
};
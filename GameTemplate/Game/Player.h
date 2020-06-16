#pragma once
class Sprite;
#include "IGameObject.h"
#include "GameCamera.h"
#include "Sprite.h"
#include "FontRender.h"
class GameCamera;
class Player:public IGameObject
{
public:
	Player();
	~Player();
	bool Start();
	void Update();
	void SetRegistShadowCaster();
	void Render();
	void PostRender();
	/// <summary>
	/// 座標を設定。
	/// </summary>
	void SetPosition(CVector3 pos)
	{
		m_position = pos;
	}
	/// <summary>
	/// 座標を取得。
	/// </summary>
	CVector3 GetPosition()
	{
		return m_position;
	}
	void SetRotation(CQuaternion rotation)
	{
		m_rotation = rotation;
	}
	CQuaternion GetRotation()
	{
		return m_rotation;
	}
	void SetMoveSpeed(CVector3 movespeed)
	{
		m_moveSpeed = movespeed;
	}
	CVector3 GetMoveSpeed()
	{
		return m_moveSpeed;
	}
	bool GetJumpFlug()
	{
		return m_jumpFlag;
	}
	void SetPushAwayFlug(bool t)
	{
		m_pushAwayFlug = t;
	}
	bool GetPushAwayFlug()
	{
		return m_pushAwayFlug;
	}
	void SetDamage(float d)
	{
		m_damage = d;
	}
	float GetDamage()
	{
		return m_damage;
	}
	void SetRedDamage(float d)
	{
		m_redDamage = d;
	}
	float GetRedDamage()
	{
		return m_redDamage;
	}
	void SetDamageFlug(bool damageFlug) 
	{
		m_damageFlug = damageFlug;
	}
	bool GetDamageFlug()
	{
		return m_damageFlug;
	}
	bool GetDeathFlug()
	{
		return m_deathFlug;
	}
	void SetStopFlug(bool flug)
	{
		m_stopFlug = flug;
	}
	bool GetStopFlug()
	{
		return m_stopFlug;
	}
private:
	GameCamera* m_gameCamera;
	EnemyGenerator* m_enemyGen;
	Enemy* m_enemy;

	SkinModel m_model;						//スキンモデル。
	CVector3 m_position = CVector3::Zero(); //座標。
	CQuaternion m_rotation = CQuaternion::Identity(); //回転。
	float ySpeed = 0.0f;                    //重力。
	CVector3 m_moveSpeed = CVector3::Zero();//ムーブスピード。
	CharacterController m_charaCon;         //キャラクターコントローラー。
	bool m_jumpFlag = false;                     //ジャンプフラグ。
	float m_playerSpeed = 20.0f;            //Playerのスピード。
	int a = 0;
	bool m_pushAwayFlug = false;
	float m_damage = 0.0f;
	float m_redDamage = 0.0f;
	int m_recoveryTimer = 0;
	bool m_damageFlug = false;
	Sprite m_greenSprite;
	Sprite m_hpBlackSprite;
	Sprite m_redSprite;
	
	CVector3 m_greenScale = CVector3::One();
	CVector3 m_redScale = CVector3::One();
	CVector3 m_blackScale = CVector3::One();
	CVector3 m_gaugePos = { -500.0f, -300.0f, 0.0f };
	CVector3 m_blackGaugePos = { -500.0f, -301.0f, 0.0f };
	
	bool m_flug = false;
	bool m_dashFlug = false;
	bool m_deathFlug = false;
	bool m_stopFlug = false; //Playerが止まっているかどうか。



	bool test = false;
};
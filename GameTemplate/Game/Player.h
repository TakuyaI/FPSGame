#pragma once
//class EnemyGenerator;
//class Enemy;
#include "character/CharacterController.h"
#include "IGameObject.h"
#include "GameCamera.h"
class GameCamera;
class Player:public IGameObject
{
public:
	Player();
	~Player();
	void Update();
	void Render();

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
private:
	GameCamera* m_gameCamera;
	EnemyGenerator* m_enemyGen;
	Enemy* m_enemy;

	CVector3 m_position = CVector3::Zero(); //座標。
	SkinModel m_model;						//スキンモデル。
	float ySpeed = 0.0f;                    //重力。
	CVector3 m_moveSpeed = CVector3::Zero();//ムーブスピード。
	CharacterController m_charaCon;         //キャラクターコントローラー。
	bool m_jumpFlag = false;                     //ジャンプフラグ。
	float m_playerSpeed = 20.0f;            //Playerのスピード。
	int a = 0;
	bool m_pushAwayFlug = false;
};
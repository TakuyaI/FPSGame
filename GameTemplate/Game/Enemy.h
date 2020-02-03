#pragma once
//class EnemyGenerator;
#include "IGameObject.h"
#include "Player.h"
class Enemy : public IGameObject
{
public:
	Enemy();
	~Enemy();

	void Loitering();
	void Tracking();
	void Attack();

	void Update();
	void Render();

	void SetPosition(CVector3 pos)
	{
		m_position = pos;
	}
	CVector3 GetPosition()
	{
		return m_position;
	}
	void SetInitPos(CVector3 initpos)
	{
		m_initPos = initpos;
	}
	CVector3 GetInitPos()
	{
		return m_initPos;
	}
	bool GetAttackFlug()
	{
		return m_attackFlug;
	}
	void SetEnemyHp(int enemyhp)
	{
		m_enemyHp = enemyhp;
	}
	int GetEnemyHp()
	{
		return m_enemyHp;
	}
	CharacterController CharaCon()
	{
		return m_charaCon;
	}
	float GetEnemyAttackPow()
	{
		return m_enemyAttackPow;
	}
	float GetDamage()
	{
		return m_damage;
	}
	void SetDamageFlug(bool damageFlug)
	{
		m_damageFlug = damageFlug;
	}
	bool GetDamageFlug()
	{
		return m_damageFlug;
	}

private:
	SkinModel m_model;                                //スキンモデル。
	Player* m_player;                                 //Playerのインスタンス。
	EnemyGenerator* enemyGen;                         //EnemyGeneratorのインスタンス。

	CVector3 m_moveSpeed = CVector3::Zero();          //ムーブスピード。
	CVector3 m_position = CVector3::Zero();           //座標。
	CVector3 m_initPos = CVector3::Zero();            //初期座標。
	CVector3 m_toPlayerVec = CVector3::Zero();        //EnemyからPlayerへ向かうベクトル。
	CQuaternion m_rotation = CQuaternion::Identity(); //回転。
	CharacterController m_charaCon;                   //キャラクターコントローラー。
	int m_state = 0;                                  //Enemyの状態。
	bool m_attackFlug = false;                        //攻撃フラグ。
	float m_pushAwaySpeed = 100.0f;                   //突き放されるスペード。
	bool m_endPushAwayflug = false;                   //突き放し終えたかどうか。
	int m_enemyHp = 50;                               //EnemyのHP。
	float m_playerHp = 100.0f;
	int m_AttackTimer = 0;
	float m_enemyAttackPow = 10.0f;
	float m_damage = 0.0f;
	bool m_damageFlug = false;
};


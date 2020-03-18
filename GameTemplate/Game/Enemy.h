#pragma once
//class EnemyGenerator;
#include "IGameObject.h"
#include "Player.h"
#include "graphics\animation\AnimationClip.h"
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
	void SetReceiveDamageFlug(bool receiveDamageFlug)
	{
		m_receiveDamageFlug = receiveDamageFlug;
	}
	void SetDeathFlug(bool deathflug)
	{
		m_death = deathflug;
	}
private:
	SkinModel m_model;                                //スキンモデル。
	Player* m_player;                                 //Playerのインスタンス。
	EnemyGenerator* m_enemyGen;                         //EnemyGeneratorのインスタンス。

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
	bool m_damageFlug = false; //ダメージを与えたかどうか。
	bool m_receiveDamageFlug = false; //ダメージを受けたかどうか。
	int m_scaredTimer = 0; //怯む時間。
	bool m_death = false; //死亡フラグ。
	int m_deathAnimtime = 0; //死亡アニメーションタイム。
	CVector3 m_toTargetVec = CVector3::Zero();
	CVector3 m_targetPos = CVector3::Zero();

	const enum anim {
		enAnimationCrip_stay,   //待機。
		enAnimationCrip_run,    //走る。
		enAnimationCrip_attack, //攻撃。
		enAnimationCrip_hirumu, //怯む。
		enAnimationCrip_death,  //死亡。
		enAnimationCrip_Num     //アニメーションクリップの数。
	};
	int m_animationFlug = 0;
	AnimationClip m_animationClip[enAnimationCrip_Num]; //アニメーションクリップ。
	Animation m_animation;                    //アニメーション。

};


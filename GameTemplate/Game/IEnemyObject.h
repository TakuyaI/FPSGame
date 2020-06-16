#pragma once
class EnemyGenerator;
#include "IGameObject.h"
#include "Item.h"
#include "IEnemyObject.h"
#include "graphics\animation\AnimationClip.h"
class IEnemyObject : public IGameObject
{
public:
	IEnemyObject();
	~IEnemyObject();
	void Saty();
	void Tracking();
	void Attack();

	void EnemyUpdate(CVector3* position, CVector3* initPos, CQuaternion* rotation, CharacterController& charaCon);
	void Update();


	/*CVector3 GetPosition()
	{
		return m_position;
	}*/
	void SetInitPos(CVector3 initpos)
	{
		m_initPos = initpos;
	}
	CVector3 GetInitPos()
	{
		return m_initPos;
	}
	/*void SetRotation(CQuaternion rotation)
	{
		m_rotation = rotation;
	}*/
	CQuaternion GetRoation()
	{
		return m_rotation;
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
	/*CharacterController* CharaCon()
	{
		return &m_charaCon;
	}*/
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
protected:
	const enum anim {
		enAnimationCrip_stay,   //待機。
		enAnimationCrip_run,    //走る。
		enAnimationCrip_attack, //攻撃。
		enAnimationCrip_hirumu, //怯む。
		enAnimationCrip_death,  //死亡。
		enAnimationCrip_Num     //アニメーションクリップの数。
	};
	int m_animationFlug = 0;
	const float ENEMY_CONTROLLER_RADIUS = 30.0f;
	const float ENEMY_CONTROLLER_HEIGHT = 100.0f;
private:
		Player* m_player;                                 //Playerのインスタンス。
	EnemyGenerator* m_enemyGen;                       //EnemyGeneratorのインスタンス。
	Item* m_item;                                     //Itemのインスタンス。

	CVector3 m_moveSpeed = CVector3::Zero();          //ムーブスピード。
	CVector3 m_position = CVector3::Zero();           //座標。
	CVector3 m_initPos = CVector3::Zero();            //初期座標。
	CVector3 m_toPlayerVec = CVector3::Zero();        //EnemyからPlayerへ向かうベクトル。
	CQuaternion m_rotation = CQuaternion::Identity(); //回転。
	int m_state = 0;                                  //Enemyの状態。
	bool m_attackFlug = false;                        //攻撃フラグ。
	float m_pushAwaySpeed = 100.0f;                   //突き放されるスピード。
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

	
	
	AnimationClip m_animationClip[enAnimationCrip_Num]; //アニメーションクリップ。
	Animation m_animation;                    //アニメーション。
	Effekseer::Effect* m_sampleEffect = nullptr;
	Effekseer::Handle m_playEffectHandle = -1;
	CVector3 m_effectPos = CVector3::Zero();

	CSoundSource m_bgm;
	CSoundSource m_walk;
	CSoundSource m_damageS;

};


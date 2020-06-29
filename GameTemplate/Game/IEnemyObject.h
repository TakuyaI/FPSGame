#pragma once
class EnemyGenerator;
class Player;
class Game;
#include "IGameObject.h"
#include "IEnemyObject.h"
#include "graphics\animation\AnimationClip.h"
class IEnemyObject : public IGameObject
{
public:
	IEnemyObject();
	~IEnemyObject();
	/// <summary>
	/// 滞在。
	/// </summary>
	/// <param name="position">座標。</param>
	/// <param name="initPos">初期座標。</param>
	void Saty(CVector3* position, CVector3* initPos);
	/// <summary>
	///追跡。
	/// </summary>
	void Tracking();
	/// <summary>
	/// 攻撃。
	/// </summary>
	void Attack();
	/// <summary>
	/// 突き飛ばされる。
	/// </summary>
	void PushAway();
	/// <summary>
	/// 死亡。
	/// </summary>
	/// <param name="pos">座標。</param>
	/// <param name="time">死亡時間。</param>
	void Death(CVector3* pos, int* time);
	/// <summary>
	/// ダメージを受ける。
	/// </summary>
	/// <param name="position">座標。</param>
	void ReceiveDamage(CVector3* position);
	void EnemyUpdate(CVector3* position, CVector3* initPos, CQuaternion* rotation, CharacterController& charaCon, int* deathTime);
	void Update();

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
	float GetEnemyAttackPow()
	{
		return m_enemyAttackPow;
	}
	float GetDamage()
	{
		return m_damage;
	}
	void SetReceiveDamageFlug(bool receiveDamageFlug)
	{
		m_receiveDamageFlug = receiveDamageFlug;
	}
	void SetDeathFlug(bool deathflug)
	{
		m_death = deathflug;
	}
	void SetEffectVec(CVector3 vec)
	{
		m_effectVec = vec;
	}
	void SetBulletPos(CVector3 pos)
	{
		m_bulletPos = pos;
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
	//const float ENEMY_CONTROLLER_RADIUS = 30.0f;
	const float ENEMY_CONTROLLER_RADIUS = 100.0f;
	const float ENEMY_CONTROLLER_HEIGHT = 200.0f;
private:
		Player* m_player;                                 //Playerのインスタンス。
	EnemyGenerator* m_enemyGen;                       //EnemyGeneratorのインスタンス。
	Game* m_game;

	CVector3 m_moveSpeed = CVector3::Zero();          //ムーブスピード。
	CVector3 m_initPos = CVector3::Zero();            //初期座標。
	CVector3 m_toPlayerVec = CVector3::Zero();        //EnemyからPlayerへ向かうベクトル。
	int m_state = 0;                                  //Enemyの状態。
	bool m_attackFlug = false;                        //攻撃フラグ。
	float m_pushAwaySpeed = 100.0f;                   //突き放されるスピード。
	bool m_endPushAwayflug = false;                   //突き放し終えたかどうか。
	int m_enemyHp = 50;                               //EnemyのHP。
	float m_playerHp = 100.0f;
	int m_AttackTimer = 0;
	float m_enemyAttackPow = 10.0f;
	float m_damage = 0.0f;
	//bool m_damageFlug = false; //ダメージを与えたかどうか。
	bool m_receiveDamageFlug = false; //ダメージを受けたかどうか。
	int m_scaredTimer = 0; //怯む時間。
	bool m_death = false; //死亡フラグ。
	int m_deathAnimtime = 0; //死亡アニメーションタイム。
	CVector3 m_toTargetVec = CVector3::Zero();
	CVector3 m_targetPos = CVector3::Zero();
	CVector3 m_bulletPos = CVector3::Zero();
	CVector3 m_effectVec = CVector3::Zero();
	Effekseer::Effect* m_sampleEffect = nullptr;
	Effekseer::Handle m_playEffectHandle = -1;

	CSoundSource m_bgm;
	CSoundSource m_walk;
	CSoundSource m_damageS;
	CVector3 m_lockTargetPos = CVector3::Zero();
	bool m_lockTargetPosFlug = false; //ターゲットの座標を固定するフラグ。

};


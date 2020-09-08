#pragma once
class Player;
class Game;
class ItemObject;
#include "IGameObject.h"
#include "IEnemyObject.h"
#include "graphics\animation\AnimationClip.h"
class IEnemyObject : public IGameObject
{
public:
	/// <summary>
	/// コンストラクタ。
	/// </summary>
	IEnemyObject();
	/// <summary>
	/// デストラクタ。
	/// </summary>
	~IEnemyObject();
	/// <summary>
	///追跡。
	/// </summary>
	void Tracking();
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
	/// <summary>
	/// 敵の更新。
	/// </summary>
	/// <param name="position">座標。</param>
	/// <param name="initPos">初期座標</param>
	/// <param name="rotation">回転。</param>
	/// <param name="charaCon">キャラコン。</param>
	/// <param name="deathTime">死亡アニメーションの時間。</param>
	/// <param name="AttackPow">攻撃力。</param>
	/// <param name="speed">速度。</param>
	void EnemyUpdate(CVector3* position, CVector3* initPos, CQuaternion* rotation, CharacterController& charaCon, int* deathTime, float* AttackPow, float* speed);
	/// <summary>
	/// 敵のHPを設定する。
	/// </summary>
	/// <param name="enemyhp"></param>
	void SetEnemyHp(int enemyhp)
	{
		m_enemyHp = enemyhp;
	}
	/// <summary>
	/// 敵のHPを返す。
	/// </summary>
	/// <returns></returns>
	int GetEnemyHp()
	{
		return m_enemyHp;
	}
	/// <summary>
	/// ダメージを受けたかどうかのフラグを設定する
	/// </summary>
	/// <param name="receiveDamageFlug"></param>
	void SetReceiveDamageFlug(bool receiveDamageFlug)
	{
		m_receiveDamageFlug = receiveDamageFlug;
	}
	/// <summary>
	/// 死亡フラグを設定する。
	/// </summary>
	/// <param name="deathflug"></param>
	void SetDeathFlug(bool deathflug)
	{
		m_death = deathflug;
	}
	/// <summary>
	/// エフェクトのベクトルを設定。
	/// </summary>
	/// <param name="vec">エフェクトのベクトル。</param>
	void SetEffectVec(CVector3 vec)
	{
		m_effectVec = vec;
	}
	/// <summary>
	/// 弾の座標を設定。
	/// </summary>
	/// <param name="pos">座標。</param>
	void SetBulletPos(CVector3 pos)
	{
		m_bulletPos = pos;
	}
private:
	/// <summary>
	/// 待機中。
	/// </summary>
	/// <param name="position">座標。</param>
	/// <param name="initPos">初期座標。</param>
	virtual void Saty(CVector3* position, CVector3* initPos){}
	/// <summary>
	/// 攻撃。
	/// </summary>
	/// /// <param name="AttackPow">攻撃力。</param>
	virtual void Attack(float AttackPow){}
protected:
	Player * m_player;                              //Playerのインスタンス。
	CVector3 m_moveSpeed = CVector3::Zero();       //ムーブスピード。
	CVector3 m_targetPos = CVector3::Zero();       //ターゲットの座標。
	CVector3 m_toPlayerVec = CVector3::Zero();     //EnemyからPlayerへ向かうベクトル。
	CSoundSource m_giveDamageS;                    //敵がダメージを与えたときの音。
	const enum anim {
		enAnimationCrip_stay,   //待機。
		enAnimationCrip_run,    //走る。
		enAnimationCrip_attack, //攻撃。
		enAnimationCrip_hirumu, //怯む。
		enAnimationCrip_death,  //死亡。
		enAnimationCrip_Num     //アニメーションクリップの数。
	};
	int m_animationFlug = 0;                       //アニメーションを決めるフラグ。
	int m_AttackTimer = 0;                         //攻撃タイマー。
	float m_damage = 0.0f;                         //ダメージ。
	float ENEMY_CONTROLLER_RADIUS = 0.0f;   //キャラコンの半径。
	float ENEMY_CONTROLLER_HEIGHT = 0.0f;  //キャラコンの高さ。
private:
	Game* m_game;                                  //Gameのインスタンス。
	ItemObject* m_itemObj;                         //ItemObjectのインスタンス。
	CVector3 m_toTargetVec = CVector3::Zero();     //敵からターゲットに向かうベクトル。
	CVector3 m_bulletPos = CVector3::Zero();       //弾の座標。
	CVector3 m_effectVec = CVector3::Zero();       //エフェクトのベクトル。
	CVector3 m_lockTargetPos = CVector3::Zero();   //ターゲットの座標。
	CSoundSource m_receiveDamageS;                 //敵がダメージを受けたときの音。
	CSoundSource m_walkS;                          //敵が歩いているときの音。
    //Effekseerマネージャ管理。
	Effekseer::Effect* m_sampleEffect = nullptr;
	Effekseer::Handle m_playEffectHandle = -1;
	int m_state = 0;                               //Enemyの状態。
	int m_enemyHp = 50;                            //EnemyのHP。
	int m_scaredTimer = 0;                         //怯む時間。
	int m_deathAnimtimer = 0;                      //死亡アニメーションタイム。
	float m_pushAwaySpeed = 100.0f;                //突き放されるスピード。
	bool m_endPushAwayflug = false;                //突き放し終えたかどうか。
	bool m_death = false;                          //死亡フラグ。
	bool m_receiveDamageFlug = false;              //ダメージを受けたかどうか。
	bool m_lockTargetPosFlug = false;              //ターゲットの座標を固定するフラグ。
};


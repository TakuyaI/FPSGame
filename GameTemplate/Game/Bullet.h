#pragma once
class Enemy;
class Game;
#include "IGameObject.h"
#include "PhysicsGhostObject.h"
#include "Rifle.h"
#include "Shotgun.h"
#include "Sniper.h"
#include "BackGround.h"
class Bullet : public IGameObject
{
public:
	/// <summary>
	/// コンストラクタ。
	/// </summary>
	Bullet();
	/// <summary>
	/// デストラクタ。
	/// </summary>
	~Bullet();
	/// <summary>
	/// ゴースト初期化。
	/// </summary>
	void InitGhost();
	/// <summary>
	/// スタート関数。
	/// </summary>
	/// <returns></returns>
	bool Start();
	/// <summary>
	/// 更新関数。
	/// </summary>
	void Update();
	//3D描画。
	void Render();
	/// <summary>
	/// 座標を設定する。
	/// </summary>
	/// <param name="pos"></param>
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
	/// 移動速度を設定する。
	/// </summary>
	/// <param name="moveSpeed"></param>
	void SetMoveSpeed(CVector3 moveSpeed)
	{
		m_moveSpeed = moveSpeed;
	}
	/// <summary>
	/// キャラコンを返す。
	/// </summary>
	/// <returns></returns>
	CharacterController* GetCharaCon()
	{
		return &m_charaCon;
	}
private:
	/// <summary>
	/// 弾丸と敵の衝突判定
	/// </summary>
	void CollisionBulletToEnemy();
	void CollisionBulletToDogEnemy();
private:
	GunGenerator* m_gunGen;                            //GunGeneratorのインスタンス。
	Game* m_game;                                      //Gameのインスタンス。
	Rifle* m_rifle;                                    //Rifleのインスタンス。
	Shotgun* m_shotgun;                                //Shotgunのインスタンス。
	Sniper* m_sniper;                                  //Sniperのインスタンス。
	SkinModel m_model;                                 //スキンモデル。
	CVector3 m_position = CVector3::Zero();            //座標。
	CVector3 m_moveSpeed = CVector3::Zero();           //移動速度。
	int m_lifeTimer = 0;                               //弾の生存時間のタイマー。
	const int m_lifeTime = 10;                         //弾の生存時間。 
	int m_bulletPower = 0;                             //弾の攻撃力。
	CQuaternion m_rotation = CQuaternion::Identity();  //回転。
	PhysicsGhostObject m_GhostObject;                  //ゴースト。
	CharacterController m_charaCon;                    //キャラコン。
	CVector3 m_hitJudgmentRange = CVector3::Zero();    //弾の当たり判定の範囲。
	const float m_controllerRadius = 5.0f;             //キャラコンの半径。
	const float m_controllerHeight = 5.0f;            //キャラコンの高さ。
};


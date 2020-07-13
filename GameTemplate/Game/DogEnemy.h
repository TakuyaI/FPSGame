#pragma once
#include "IEnemyObject.h"
//#include "Game.h"
class DogEnemy : public IEnemyObject
{
public:
	DogEnemy();
	~DogEnemy();

	bool Start();
	void Update();
	void SetRegistShadowCaster();
	void Render();

	void Saty(CVector3* position, CVector3* initPos);
	void Attack(float AttackPow);

	void SetPosition(CVector3 pos)
	{
		m_position = pos;
	}
	CVector3 GetPosition()
	{
		return m_position;
	}
	void SetRotation(CQuaternion rotation)
	{
		m_rotation = rotation;
	}
	CharacterController* CharaCon()
	{
		return &m_charaCon;
	}
private:
	SkinModel m_model;                                //スキンモデル。
	CVector3 m_position = CVector3::Zero();
	CQuaternion m_rotation = CQuaternion::Identity();
	float m_attackPow = 7.0f; //攻撃力。
	CharacterController m_charaCon;                   //キャラクターコントローラー。
	AnimationClip m_animationClip[enAnimationCrip_Num]; //アニメーションクリップ。
	Animation m_animation;                    //アニメーション。
	int m_deathAnimTime = 10; //死亡時のアニメーションの時間。
};


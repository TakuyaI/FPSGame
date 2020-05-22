#pragma once
#include "IEnemyObject.h"
class DogEnemy : public IEnemyObject
{
public:
	DogEnemy();
	~DogEnemy();

	bool Start();
	void Update();
	void Render();

private:
	SkinModel m_model;                                //スキンモデル。
	CVector3 m_position = CVector3::Zero();
	CQuaternion m_rotation = CQuaternion::Identity();
	CharacterController m_charaCon;                   //キャラクターコントローラー。
	AnimationClip m_animationClip[enAnimationCrip_Num]; //アニメーションクリップ。
	Animation m_animation;                    //アニメーション。
};


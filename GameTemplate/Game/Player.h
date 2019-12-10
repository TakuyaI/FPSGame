#pragma once
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
	void Draw();

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
	bool GetJumpFlug()
	{
		return m_jumpFlag;
	}
	void SetGameCamera(GameCamera* gc)
	{
		m_gameCamera = gc;
	}
private:
	GameCamera* m_gameCamera;

	CVector3 m_position = CVector3::Zero(); //座標。
	SkinModel m_model;						//スキンモデル。
	float ySpeed = 0.0f;                    //重力。
	CVector3 m_moveSpeed = CVector3::Zero();//
	CharacterController m_charaCon;         //キャラクターコントローラー。
	bool m_jumpFlag = false;                     //ジャンプフラグ。
	float m_playerSpeed = 20.0f;            //Playerのスピード。
};
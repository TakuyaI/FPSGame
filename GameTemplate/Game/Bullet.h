#pragma once
#include "IGameObject.h"
#include "Gun.h"
class Bullet : public IGameObject
{
public:
	Bullet();
	~Bullet();

	void Update();

	void SetPosition(CVector3 pos)
	{
		m_position = pos;
	}
	CVector3 GetPosition()
	{
		return m_position;
	}
	void Setgun(Gun* gun)
	{
		m_gun = gun;
	}
	void SetMoveSpeed(CVector3 moveSpeed)
	{
		m_moveSpeed = moveSpeed;
	}
private:
	Gun * m_gun;
	SkinModel m_model;
	CVector3 m_position = CVector3::Zero();
	CVector3 m_moveSpeed = CVector3::Zero();
	int m_timer = 0;
};


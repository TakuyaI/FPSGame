#pragma once
#include "IGameObject.h"
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


private:
	SkinModel m_model;
	CVector3 m_position = CVector3::Zero();
};


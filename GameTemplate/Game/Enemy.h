#pragma once
#include "IGameObject.h"
class Enemy : public IGameObject
{
public:
	Enemy();
	~Enemy();

	void Update();

	void SetPosition(CVector3 pos)
	{
		m_position = pos;
	}

	CVector3 GetPosition()
	{
		return m_position;
	}

	void SetNumber(int num)
	{
		m_number = num;
	}
	int GetNumber()
	{
		return m_number;
	}

private:
	SkinModel m_model;
	CVector3 m_position = CVector3::Zero();
	CQuaternion m_rotation = CQuaternion::Identity();
	int m_number = 0;
};


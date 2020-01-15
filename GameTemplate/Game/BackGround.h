#pragma once
#include "IGameObject.h"
#include "physics\PhysicsStaticObject.h"
class BackGround : public IGameObject
{
public:
	BackGround();
	~BackGround();

	void Update();

private:
	SkinModel m_model;
	CVector3 m_position = CVector3::Zero();
	CQuaternion m_rotaiton = CQuaternion::Identity();
	int a = 0;
	PhysicsStaticObject m_a;
};


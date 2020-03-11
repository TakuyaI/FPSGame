#pragma once
#include "IGameObject.h"
//#include "physics\PhysicsStaticObject.h"
class BackGround : public IGameObject
{
public:
	BackGround();
	~BackGround();

	void Update();
	void Render();

private:
	SkinModel m_model;
	CVector3 m_position = CVector3::Zero();
	CQuaternion m_rotation = CQuaternion::Identity();

	//PhysicsStaticObject m_physicsStaticObject;
	int a = 0;
};


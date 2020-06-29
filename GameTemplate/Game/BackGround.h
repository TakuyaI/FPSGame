#pragma once
#include "IGameObject.h"
#include "physics\PhysicsStaticObject.h"
class BackGround : public IGameObject
{
public:
	BackGround();
	~BackGround();

	bool Start();
	void Update();
	void SetRegistShadowCaster();
	void Render();

	void SetPosition(CVector3 position)
	{
		m_position = position;
	}

	CVector3 GetPosition()
	{
		return m_position;
	}
	void SetRotation(CQuaternion rotation)
	{
		m_rotation = rotation;
	}
	CQuaternion GetRotation() 
	{
		return m_rotation;
	}
private:
	SkinModel m_model;
	CVector3 m_position = CVector3::Zero();
	CQuaternion m_rotation = CQuaternion::Identity();

	PhysicsStaticObject m_physicsStaticObject;
	int a = 0;
};


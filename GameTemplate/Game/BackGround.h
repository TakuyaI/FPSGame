#pragma once
#include "IGameObject.h"

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
	CQuaternion m_rotaiton = CQuaternion::Identity();
	int a = 0;
};


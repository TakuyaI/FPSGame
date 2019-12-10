#include "stdafx.h"
#include "Bullet.h"


Bullet::Bullet()
{
	m_model.Init(L"Assets/modelData/bullet_test.cmo");
}


Bullet::~Bullet()
{
}

void Bullet::Update()
{
	m_model.UpdateWorldMatrix(m_position, CQuaternion::Identity(), CVector3::One());
	m_model.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}
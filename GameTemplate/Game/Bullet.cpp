#include "stdafx.h"
#include "Bullet.h"
#include "GameManager.h"

Bullet::Bullet()
{
	m_model.Init(L"Assets/modelData/bullet_test.cmo");
}


Bullet::~Bullet()
{
}

void Bullet::Update()
{
	m_timer++;
	m_position += m_moveSpeed;
	if (m_timer >= 10) {
		g_goMgr.DeleteGameObject(this);
		m_timer = 0;
	}

	m_model.UpdateWorldMatrix(m_position, CQuaternion::Identity(), CVector3::One());
	m_model.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}
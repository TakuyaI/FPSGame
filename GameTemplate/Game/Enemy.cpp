#include "stdafx.h"
#include "Enemy.h"
#include "GameManager.h"

Enemy::Enemy()
{
	m_model.Init(L"Assets/modelData/zombie01.cmo");
	m_position = { 0.0f, 0.0f, 300.0f };
}


Enemy::~Enemy()
{
}

void Enemy::Update()
{
	//m_rotation.SetRotationDeg(CVector3::AxisY(), 90.0f);
	//m_position.x += 3.0f;
	m_model.UpdateWorldMatrix(m_position, m_rotation, CVector3::One());
	m_model.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}
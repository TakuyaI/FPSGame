#include "stdafx.h"
#include "BackGround.h"


BackGround::BackGround()
{
	m_model.Init(L"Assets/modelData/background.cmo");
}


BackGround::~BackGround()
{
}

void BackGround::Update()
{
	m_model.UpdateWorldMatrix(m_position, m_rotaiton, CVector3::One() * 10.0f);
	m_model.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}
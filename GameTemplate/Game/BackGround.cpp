#include "stdafx.h"
#include "BackGround.h"
#include "GameManager.h"
BackGround::BackGround()
{
	m_model.Init(L"Assets/modelData/bk.cmo");
	
	//m_physicsStaticObject.CreateMeshObject(m_model, m_position, m_rotation);
}


BackGround::~BackGround()
{

}

void BackGround::Update()
{
	
	m_model.UpdateWorldMatrix(m_position, m_rotation, CVector3::One() * 10.0f);

	
}

void BackGround::Render()
{
	m_model.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}
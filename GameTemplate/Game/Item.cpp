#include "stdafx.h"
#include "Item.h"
#include "GameManager.h"
#include "Enemy.h"



Item::Item()
{
	m_model.Init(L"Assets/modelData/item01.cmo");
}


Item::~Item()
{
}

void Item::Update()
{

	m_position.y = 50.0f;
	m_model.UpdateWorldMatrix(m_position, m_rotation, CVector3::One());
}

void Item::Render()
{
	m_model.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}
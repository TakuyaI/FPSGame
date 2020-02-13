#include "stdafx.h"
#include "Item.h"
#include "GameManager.h"
#include "Enemy.h"
#include "Gun.h"
#include "GunGenerator.h"
#include "Player.h"



Item::Item()
{
	m_model.Init(L"Assets/modelData/item01.cmo");
	m_player = g_goMgr.FindGameObject<Player>(player);
}


Item::~Item()
{
}

void Item::Update()
{
	CVector3 v = m_position - m_player->GetPosition();
	if (v.Length() <= 100.0) {
		g_goMgr.DeleteGameObject(this);
	}
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
void Item::PostRender()
{

}
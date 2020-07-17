#include "stdafx.h"
#include "ItemObject.h"


ItemObject::ItemObject()
{
	m_itemGen = g_goMgr.FindGameObject<ItemGenerator>(itemgenerator);
	m_player = g_goMgr.FindGameObject<Player>(player);
	m_game = g_goMgr.FindGameObject<Game>(game);
	item = g_goMgr.Rand(1);
	if (item == danyaku) {
		m_model.Init(L"Assets/modelData/item01.cmo");
	}
	else if (item == kaihuku) {
		m_model.Init(L"Assets/modelData/item01.cmo");
	}
}


ItemObject::~ItemObject()
{
}
bool ItemObject::Start()
{
	
	return true;
}
void ItemObject::Update()
{
	if (m_game->GetEndFlug() != false) {
		g_goMgr.DeleteGameObject(this);
	}
	//アイテムからプレイヤーに向かって伸びるベクトルを求める。
	CVector3 toPlayerV = m_player->GetPosition() - m_position;
	float len = toPlayerV.Length();
	if (len <= 200.0f) {
		ItemGenerator* itemGen = g_goMgr.FindGameObject<ItemGenerator>(itemgenerator);
		if (item == danyaku) {
			itemGen->SetDanyakuFkug(true);
		}
		else if (item == kaihuku) {
			itemGen->SetKaihukuyakuFkug(true);
		}
		g_goMgr.DeleteGameObject(this);
	}
	m_model.UpdateWorldMatrix(m_position, CQuaternion::Identity(), CVector3::One());
}

void ItemObject::Render()
{
	m_model.Draw(
		enRenderMode_Normal,
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}

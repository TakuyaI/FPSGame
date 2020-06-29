#include "stdafx.h"
#include "ItemObject.h"


ItemObject::ItemObject()
{
	m_itemGen = g_goMgr.FindGameObject<ItemGenerator>(itemgenerator);
	m_player = g_goMgr.FindGameObject<Player>(player);
}


ItemObject::~ItemObject()
{
}
bool ItemObject::Start()
{
	
	return true;
}
void ItemObject::ItemUpdate(CVector3* position, int* number)
{
	//アイテムからプレイヤーに向かって伸びるベクトルを求める。
	CVector3 toPlayerV = m_player->GetPosition() - *position;
	if (toPlayerV.Length() <= 100.0f) {
		m_itemGen->IncreaseItem(*number);
		g_goMgr.DeleteGameObject(this);
	}
}
void ItemObject::Update()
{
}


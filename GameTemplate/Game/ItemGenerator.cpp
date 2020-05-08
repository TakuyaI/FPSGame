#include "stdafx.h"
#include "ItemGenerator.h"


ItemGenerator::ItemGenerator()
{
	m_itemS.Init(L"Resource/sprite/item.dds", 320.0f, 180.0f);
	m_danyaku.Init(L"Resource/sprite/item_danyaku.dds", 320.0f, 180.0f);
	m_position = { 0.0f, -250.0f, 0.0f };
}


ItemGenerator::~ItemGenerator()
{
}
void ItemGenerator::Update()
{
	
}
void ItemGenerator::PostRender()
{
	m_itemS.Update(
		m_position,
		CQuaternion::Identity(),
		CVector3::One(),
		{ 0.5f, 0.5f }
	);
	m_itemS.Draw();


	m_danyaku.Update(
		m_position,
		CQuaternion::Identity(),
		CVector3::One(),
		{ 0.5f, 0.5f }
	);

	
	if (g_pad->IsPress(enButtonLB2)) {
		m_itemHave = danyaku;
		m_danyaku.Draw();
	}

	if (m_itemHave == danyaku) {
		m_danyaku.Draw();
	}
}
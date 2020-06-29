#include "stdafx.h"
#include "ItemGenerator.h"


ItemGenerator::ItemGenerator()
{
	m_itemTex.Init(L"Resource/sprite/item.dds", 320.0f, 180.0f);
	m_danyakuTex.Init(L"Resource/sprite/item_danyaku.dds", 320.0f, 180.0f);
	m_kaihukuyakuTex.Init(L"Resource/sprite/item_kaihuku.dds", 320.0f, 180.0f);
	m_position = { 0.0f, -250.0f, 0.0f };
	m_kaihukuyaku.number = kaihukuyaku;
	m_danyaku.number = danyaku;
}


ItemGenerator::~ItemGenerator()
{
}
void ItemGenerator::IncreaseItem(int number)
{
	if (number == kaihukuyaku) {
		m_kaihukuyaku.num++;
	}
	else if (number == danyaku)
	{
		m_danyaku.num++;
	}
}
void ItemGenerator::Update()
{
	
}
void ItemGenerator::PostRender()
{
	if (m_kaihukuyaku.num > 0) {
		m_kaihukuyaku.getFlug = true;
	}
	else {
		m_kaihukuyaku.getFlug = false;
	}
	if (m_danyaku.num > 0) {
		m_danyaku.getFlug = true;
	}
	else {
		m_danyaku.getFlug = false;
	}

	if (g_pad->IsPress(enButtonLB2)) {
		m_stateNumber--;
		if (m_stateNumber <= firstnum) {
			m_stateNumber = endnum - 1;
		}
	}
	if (g_pad->IsPress(enButtonRB2)) {
		m_stateNumber++;
		if (m_stateNumber >= endnum) {
			m_stateNumber = firstnum - 1;
		}
	}



	{//アイテムの一番下のテクスチャ。
		m_itemTex.Update(
			m_position,
			CQuaternion::Identity(),
			CVector3::One(),
			{ 0.5f, 0.5f }
		);
		m_itemTex.Draw();
	}

	if (m_stateNumber == danyaku) {
		m_danyakuTex.Update(
			m_position,
			CQuaternion::Identity(),
			CVector3::One(),
			{ 0.5f, 0.5f }
		);
		m_danyakuTex.Draw();
	}
	else if (m_stateNumber == kaihukuyaku) {
		m_kaihukuyakuTex.Update(
			m_position,
			CQuaternion::Identity(),
			CVector3::One(),
			{ 0.5f, 0.5f }
		);
		m_kaihukuyakuTex.Draw();
	}
}
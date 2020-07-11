#include "stdafx.h"
#include "ItemGenerator.h"


ItemGenerator::ItemGenerator()
{
	m_itemTex.Init(L"Resource/sprite/item2.dds", 320.0f, 180.0f);
	m_danyakuTex.Init(L"Resource/sprite/item_danyaku.dds", 320.0f, 180.0f);
	m_kaihukuyakuTex.Init(L"Resource/sprite/item_kaihuku.dds", 320.0f, 180.0f);
	m_position = { 0.0f, -250.0f, 0.0f };
	InitItem();
}


ItemGenerator::~ItemGenerator()
{
}
void ItemGenerator::InitItem()
{

	m_kaihukuyaku.getFlug = false;
	m_kaihukuyaku.num = 0;
	m_kaihukuyaku.number = 0;

	m_danyaku.getFlug = false;
	m_danyaku.num = 0;
	m_danyaku.number = 0;
}
void ItemGenerator::GetItem(bool* flug, ItemName* item)
{
	if (*flug != false) {
		//アイテムを拾った。
		//所持数を1個増やす。
		++item->num;
		if (item->getFlug != true) {
			//アイテムを持っていなかった。
			//m_itemNumberを1足す。
			m_itemNumber++;
			//アイテムのnumberをm_itemNumberにする。
			item->number = m_itemNumber;
			m_stateNumber = item->number;
			//m_endNumはm_itemNumberより1多くする。
			m_endNum = m_itemNumber;
			m_endNum++;
			//アイテムを所持しているので、フラグをtrueにする。
			item->getFlug = true;
		}
		*flug = false;
	}
	else if (item->num <= 0) {
		//アイテムを持っていない。
		//アイテムのnumberを0にする。
		item->number = m_firstNum;
		//アイテムを所持していないので、フラグをfalseにする。
		item->getFlug = false;
	}
}
void ItemGenerator::Update()
{
	//弾薬を取得したかどうか。
	GetItem(&m_getDanyakuFlug, &m_danyaku);
	//回復薬を取得したかどうか。
	GetItem(&m_getKaihukuyakuFlug, &m_kaihukuyaku);

	if (g_pad->IsPress(enButtonLB2)) {
		//LB2ボタンを押した。
		if (m_pushLB2Flug != true) {
			//1回押したら、1度離して押さないと反応しないようにする。
			m_stateNumber--;
			if (m_stateNumber <= m_firstNum) {
				//m_stateNumberが0になったら、numberの値が1番大きいアイテムが表示される。
				int num = m_itemNumber;
				m_stateNumber = num;
			}
			//LB2ボタンを押しているので、フラグをtrueにする。
			m_pushLB2Flug = true;
		}
	}
	else {
		//LB2ボタンを離しているので、フラグをfalseにする。
		m_pushLB2Flug = false;
	}

	if (g_pad->IsPress(enButtonRB2)) {
		//RB2ボタンを押した。
		if (m_pushRB2Flug != true) {
			//1回押したら、1度離して押さないと反応しないようにする。
			m_stateNumber++;
			if (m_stateNumber >= m_endNum) {
				//m_stateNumberがm_firstNumになったら、numberの値が1のアイテムが表示される。
				int num2 = m_firstNum;
				m_stateNumber = ++num2;
			}
			//RB2ボタンを押しているので、フラグをtrueにする。
			m_pushRB2Flug = true;
		}
	}
	else {
		//RB2ボタンを離しているので、フラグをfalseにする。
		m_pushRB2Flug = false;
	}
}
void ItemGenerator::PostRender()
{
		{//アイテムの一番下のテクスチャ。
			m_itemTex.Update(
				m_position,
				CQuaternion::Identity(),
				CVector3::One(),
				{ 0.5f, 0.5f }
			);
			m_itemTex.Draw();
		}
		if (m_stateNumber == m_firstNum) {
			//m_stateNumberが0だった場合、何も表示しない。
		}
		else {
			if (m_stateNumber == m_danyaku.number) {
				//弾薬を表示。
				m_danyakuTex.Update(
					m_position,
					CQuaternion::Identity(),
					CVector3::One(),
					{ 0.5f, 0.5f }
				);
				m_stateNum = m_danyaku.num;
				m_danyakuTex.Draw();
			}
			else if (m_stateNumber == m_kaihukuyaku.number) {
				//回復薬を表示。
				m_kaihukuyakuTex.Update(
					m_position,
					CQuaternion::Identity(),
					CVector3::One(),
					{ 0.5f, 0.5f }
				);
				m_stateNum = m_kaihukuyaku.num;
				m_kaihukuyakuTex.Draw();
			}
			//表示されているアイテムの個数を表示する。
			wchar_t text[256];
			swprintf_s(text, L"%d", m_stateNum);
			m_font.Draw(text, { 628.0f, 653.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }, 0.7f);
		}
		
}
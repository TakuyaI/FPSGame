#include "stdafx.h"
#include "ItemGenerator.h"


ItemGenerator::ItemGenerator()
{
	m_itemTex.Init(L"Resource/sprite/item2.dds", 320.0f, 180.0f);
	m_danyakuTex.Init(L"Resource/sprite/item_danyaku.dds", 320.0f, 180.0f);
	m_kaihukuyakuTex.Init(L"Resource/sprite/item_kaihuku.dds", 320.0f, 180.0f);
	m_position = { 0.0f, -250.0f, 0.0f };
	m_kaihuku = new Kaihuku;
	m_danyaku = new Danyaku;
}


ItemGenerator::~ItemGenerator()
{
	delete m_kaihuku;
	delete m_danyaku;
}

void ItemGenerator::GetItem(bool* flug, IItemObject* item)
{
	if (*flug != false) {
		//アイテムを拾った。
		if(item->GetHaveFlug() != true) {
			//拾ったアイテムと同じものをまだ持っていない。
			for (int i = 0; i < m_maxHaveNum; i++) {
				//配列の0番から探して、空いているところに入れる。
				if (m_getItemList[i] == nullptr) {
					//空いていた。
					m_getItemList[i] = item;
					//アイテムを所持している状態になったので、
					//フラグをtrueにする。
					item->SetHaveFlug(true);
					//アイテムの番号に配列の番号を入れる。
					m_getItemList[i]->SetItemNumber(i);
					m_stateNumber = i;
					//入れ終わったので、for文を終了する。
					break;
				}
			}
		}
		//アイテムの所持数を加算する。
		int itemNum = item->GetHaveNum();
		item->SetHaveNum(++itemNum);
	}
	*flug = false;
}
void ItemGenerator::SelectItem()
{
	//LB2ボタン。
	if (g_pad->IsPress(enButtonLB2)) {
		//LB2ボタンを押した。
		if (m_pushLB2Flug != true) {
			//1回押したら、1度離して押さないと反応しないようにする。
			m_stateNumber--;
			if (m_stateNumber < 0) {
				//m_stateNumberがマイナスになったら、
				//m_maxHaveNumを代入する。
				int num = m_maxHaveNum;
				//配列の関係上、１引く。
				m_stateNumber = --num;
			}
			for (int i = 0; i < m_maxHaveNum; i++) {
				if (m_getItemList[m_stateNumber] != nullptr) {
					//m_getItemListの中にアイテムが入っていたので、
					//表示する。
					m_stateNumber = m_getItemList[m_stateNumber]->GetmItemNumber();
					break;
				}
				else {
					m_stateNumber--;
					if (m_stateNumber < 0) {
						int num = m_maxHaveNum;
						m_stateNumber = --num;
					}
				}
			}
			//LB2ボタンを押しているので、フラグをtrueにする。
			m_pushLB2Flug = true;
		}
	}
	else {
		//LB2ボタンを離しているので、フラグをfalseにする。
		m_pushLB2Flug = false;
	}

	//RB2ボタン。
	if (g_pad->IsPress(enButtonRB2)) {
		//RB2ボタンを押した。
		if (m_pushRB2Flug != true) {
			//1回押したら、1度離して押さないと反応しないようにする。
			m_stateNumber++;
			if (m_stateNumber >= m_maxHaveNum) {
				//m_stateNumberがm_maxHaveNum以上になったら、
				//0を代入する。
				m_stateNumber = 0;
			}
			for (int i = 0; i < m_maxHaveNum; i++) {
				if (m_getItemList[m_stateNumber] != nullptr) {
					//m_getItemListの中にアイテムが入っていたので、
					//表示する。
					m_stateNumber = m_getItemList[m_stateNumber]->GetmItemNumber();
					break;
				}
				else {
					m_stateNumber++;
					if (m_stateNumber >= m_maxHaveNum) {
						m_stateNumber = 0;
					}
				}
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
void ItemGenerator::UseItem()
{
	if (g_pad->IsPress(enButtonA)) {
		//Aボタンを押した。
		if (m_pushAFlug != true) {
			m_pushAFlug = true;
			if (m_getItemList[m_stateNumber] != nullptr) {
				//m_getItemList[m_stateNumber]にアイテムが入っている。
				//アイテム効果。
				m_getItemList[m_stateNumber]->ItemEffects();
				//使ったので、個数を減らす。
				int num = m_getItemList[m_stateNumber]->GetHaveNum();
				m_getItemList[m_stateNumber]->SetHaveNum(--num);
				if (m_getItemList[m_stateNumber]->GetHaveNum() <= 0) {
					//アイテムの個数が0個になった。
					//アイテムの所持フラグをfalseにする。
					m_getItemList[m_stateNumber]->SetHaveFlug(false);
					//番号をリセット。
					m_getItemList[m_stateNumber]->SetItemNumber(1000);
					//m_getItemList[m_stateNumber]にnullptrを入れる。
					m_getItemList[m_stateNumber] = nullptr;
				}
			}
		}
	}
	else {
		m_pushAFlug = false;
	}
}
void ItemGenerator::Update()
{
	//弾薬を取得したかどうか。
	GetItem(&m_getDanyakuFlug, m_danyaku);
	//回復薬を取得したかどうか。
	GetItem(&m_getKaihukuyakuFlug, m_kaihuku);
	//アイテムを選ぶ。
	SelectItem();
	//アイテムを使用使用するかどうか。
	UseItem();
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

		if (m_stateNumber == m_danyaku->GetmItemNumber()) {
			//弾薬を表示。
			m_danyakuTex.Update(
				m_position,
				CQuaternion::Identity(),
				CVector3::One(),
				{ 0.5f, 0.5f }
			);
			m_stateNum = m_danyaku->GetHaveNum();
			m_danyakuTex.Draw();
			//表示されているアイテムの個数を表示する。
			wchar_t text[256];
			swprintf_s(text, L"%d", m_stateNum);
			m_font.Draw(text, { 628.0f, 653.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }, 0.7f);
		}
		else if (m_stateNumber == m_kaihuku->GetmItemNumber()) {
			//回復薬を表示。
			m_kaihukuyakuTex.Update(
				m_position,
				CQuaternion::Identity(),
				CVector3::One(),
				{ 0.5f, 0.5f }
			);
			m_stateNum = m_kaihuku->GetHaveNum();
			m_kaihukuyakuTex.Draw();
			//表示されているアイテムの個数を表示する。
			wchar_t text[256];
			swprintf_s(text, L"%d", m_stateNum);
			m_font.Draw(text, { 628.0f, 653.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }, 0.7f);
		}
}
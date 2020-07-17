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
		//�A�C�e�����E�����B
		if(item->GetHaveFlug() != true) {
			//�E�����A�C�e���Ɠ������̂��܂������Ă��Ȃ��B
			for (int i = 0; i < m_maxHaveNum; i++) {
				//�z���0�Ԃ���T���āA�󂢂Ă���Ƃ���ɓ����B
				if (m_getItemList[i] == nullptr) {
					//�󂢂Ă����B
					m_getItemList[i] = item;
					//�A�C�e�����������Ă����ԂɂȂ����̂ŁA
					//�t���O��true�ɂ���B
					item->SetHaveFlug(true);
					//�A�C�e���̔ԍ��ɔz��̔ԍ�������B
					m_getItemList[i]->SetItemNumber(i);
					m_stateNumber = i;
					//����I������̂ŁAfor�����I������B
					break;
				}
			}
		}
		//�A�C�e���̏����������Z����B
		int itemNum = item->GetHaveNum();
		item->SetHaveNum(++itemNum);
	}
	*flug = false;
}
void ItemGenerator::SelectItem()
{
	//LB2�{�^���B
	if (g_pad->IsPress(enButtonLB2)) {
		//LB2�{�^�����������B
		if (m_pushLB2Flug != true) {
			//1�񉟂�����A1�x�����ĉ����Ȃ��Ɣ������Ȃ��悤�ɂ���B
			m_stateNumber--;
			if (m_stateNumber < 0) {
				//m_stateNumber���}�C�i�X�ɂȂ�����A
				//m_maxHaveNum��������B
				int num = m_maxHaveNum;
				//�z��̊֌W��A�P�����B
				m_stateNumber = --num;
			}
			for (int i = 0; i < m_maxHaveNum; i++) {
				if (m_getItemList[m_stateNumber] != nullptr) {
					//m_getItemList�̒��ɃA�C�e���������Ă����̂ŁA
					//�\������B
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
			//LB2�{�^���������Ă���̂ŁA�t���O��true�ɂ���B
			m_pushLB2Flug = true;
		}
	}
	else {
		//LB2�{�^���𗣂��Ă���̂ŁA�t���O��false�ɂ���B
		m_pushLB2Flug = false;
	}

	//RB2�{�^���B
	if (g_pad->IsPress(enButtonRB2)) {
		//RB2�{�^�����������B
		if (m_pushRB2Flug != true) {
			//1�񉟂�����A1�x�����ĉ����Ȃ��Ɣ������Ȃ��悤�ɂ���B
			m_stateNumber++;
			if (m_stateNumber >= m_maxHaveNum) {
				//m_stateNumber��m_maxHaveNum�ȏ�ɂȂ�����A
				//0��������B
				m_stateNumber = 0;
			}
			for (int i = 0; i < m_maxHaveNum; i++) {
				if (m_getItemList[m_stateNumber] != nullptr) {
					//m_getItemList�̒��ɃA�C�e���������Ă����̂ŁA
					//�\������B
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
			//RB2�{�^���������Ă���̂ŁA�t���O��true�ɂ���B
			m_pushRB2Flug = true;
		}
	}
	else {
		//RB2�{�^���𗣂��Ă���̂ŁA�t���O��false�ɂ���B
		m_pushRB2Flug = false;
	}


}
void ItemGenerator::UseItem()
{
	if (g_pad->IsPress(enButtonA)) {
		//A�{�^�����������B
		if (m_pushAFlug != true) {
			m_pushAFlug = true;
			if (m_getItemList[m_stateNumber] != nullptr) {
				//m_getItemList[m_stateNumber]�ɃA�C�e���������Ă���B
				//�A�C�e�����ʁB
				m_getItemList[m_stateNumber]->ItemEffects();
				//�g�����̂ŁA�������炷�B
				int num = m_getItemList[m_stateNumber]->GetHaveNum();
				m_getItemList[m_stateNumber]->SetHaveNum(--num);
				if (m_getItemList[m_stateNumber]->GetHaveNum() <= 0) {
					//�A�C�e���̌���0�ɂȂ����B
					//�A�C�e���̏����t���O��false�ɂ���B
					m_getItemList[m_stateNumber]->SetHaveFlug(false);
					//�ԍ������Z�b�g�B
					m_getItemList[m_stateNumber]->SetItemNumber(1000);
					//m_getItemList[m_stateNumber]��nullptr������B
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
	//�e����擾�������ǂ����B
	GetItem(&m_getDanyakuFlug, m_danyaku);
	//�񕜖���擾�������ǂ����B
	GetItem(&m_getKaihukuyakuFlug, m_kaihuku);
	//�A�C�e����I�ԁB
	SelectItem();
	//�A�C�e�����g�p�g�p���邩�ǂ����B
	UseItem();
}
void ItemGenerator::PostRender()
{
		{//�A�C�e���̈�ԉ��̃e�N�X�`���B
			m_itemTex.Update(
				m_position,
				CQuaternion::Identity(),
				CVector3::One(),
				{ 0.5f, 0.5f }
			);
			m_itemTex.Draw();
		}

		if (m_stateNumber == m_danyaku->GetmItemNumber()) {
			//�e���\���B
			m_danyakuTex.Update(
				m_position,
				CQuaternion::Identity(),
				CVector3::One(),
				{ 0.5f, 0.5f }
			);
			m_stateNum = m_danyaku->GetHaveNum();
			m_danyakuTex.Draw();
			//�\������Ă���A�C�e���̌���\������B
			wchar_t text[256];
			swprintf_s(text, L"%d", m_stateNum);
			m_font.Draw(text, { 628.0f, 653.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }, 0.7f);
		}
		else if (m_stateNumber == m_kaihuku->GetmItemNumber()) {
			//�񕜖��\���B
			m_kaihukuyakuTex.Update(
				m_position,
				CQuaternion::Identity(),
				CVector3::One(),
				{ 0.5f, 0.5f }
			);
			m_stateNum = m_kaihuku->GetHaveNum();
			m_kaihukuyakuTex.Draw();
			//�\������Ă���A�C�e���̌���\������B
			wchar_t text[256];
			swprintf_s(text, L"%d", m_stateNum);
			m_font.Draw(text, { 628.0f, 653.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }, 0.7f);
		}
}
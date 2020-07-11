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
		//�A�C�e�����E�����B
		//��������1���₷�B
		++item->num;
		if (item->getFlug != true) {
			//�A�C�e���������Ă��Ȃ������B
			//m_itemNumber��1�����B
			m_itemNumber++;
			//�A�C�e����number��m_itemNumber�ɂ���B
			item->number = m_itemNumber;
			m_stateNumber = item->number;
			//m_endNum��m_itemNumber���1��������B
			m_endNum = m_itemNumber;
			m_endNum++;
			//�A�C�e�����������Ă���̂ŁA�t���O��true�ɂ���B
			item->getFlug = true;
		}
		*flug = false;
	}
	else if (item->num <= 0) {
		//�A�C�e���������Ă��Ȃ��B
		//�A�C�e����number��0�ɂ���B
		item->number = m_firstNum;
		//�A�C�e�����������Ă��Ȃ��̂ŁA�t���O��false�ɂ���B
		item->getFlug = false;
	}
}
void ItemGenerator::Update()
{
	//�e����擾�������ǂ����B
	GetItem(&m_getDanyakuFlug, &m_danyaku);
	//�񕜖���擾�������ǂ����B
	GetItem(&m_getKaihukuyakuFlug, &m_kaihukuyaku);

	if (g_pad->IsPress(enButtonLB2)) {
		//LB2�{�^�����������B
		if (m_pushLB2Flug != true) {
			//1�񉟂�����A1�x�����ĉ����Ȃ��Ɣ������Ȃ��悤�ɂ���B
			m_stateNumber--;
			if (m_stateNumber <= m_firstNum) {
				//m_stateNumber��0�ɂȂ�����Anumber�̒l��1�ԑ傫���A�C�e�����\�������B
				int num = m_itemNumber;
				m_stateNumber = num;
			}
			//LB2�{�^���������Ă���̂ŁA�t���O��true�ɂ���B
			m_pushLB2Flug = true;
		}
	}
	else {
		//LB2�{�^���𗣂��Ă���̂ŁA�t���O��false�ɂ���B
		m_pushLB2Flug = false;
	}

	if (g_pad->IsPress(enButtonRB2)) {
		//RB2�{�^�����������B
		if (m_pushRB2Flug != true) {
			//1�񉟂�����A1�x�����ĉ����Ȃ��Ɣ������Ȃ��悤�ɂ���B
			m_stateNumber++;
			if (m_stateNumber >= m_endNum) {
				//m_stateNumber��m_firstNum�ɂȂ�����Anumber�̒l��1�̃A�C�e�����\�������B
				int num2 = m_firstNum;
				m_stateNumber = ++num2;
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
		if (m_stateNumber == m_firstNum) {
			//m_stateNumber��0�������ꍇ�A�����\�����Ȃ��B
		}
		else {
			if (m_stateNumber == m_danyaku.number) {
				//�e���\���B
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
				//�񕜖��\���B
				m_kaihukuyakuTex.Update(
					m_position,
					CQuaternion::Identity(),
					CVector3::One(),
					{ 0.5f, 0.5f }
				);
				m_stateNum = m_kaihukuyaku.num;
				m_kaihukuyakuTex.Draw();
			}
			//�\������Ă���A�C�e���̌���\������B
			wchar_t text[256];
			swprintf_s(text, L"%d", m_stateNum);
			m_font.Draw(text, { 628.0f, 653.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }, 0.7f);
		}
		
}
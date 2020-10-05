#include "stdafx.h"
#include "ItemGenerator.h"

const CVector2 ITEM_SPRITE_SIZE = { 320.0f, 180.0f }; //�A�C�e���̃X�v���C�g�̃T�C�Y�B
const int MOVE_RIGHT_TIME = 10;                       //�^�C����10�ɂȂ�܂ŁA�A�C�e���Q�b�g�̃t�H���g���E�ɓ����B
const int MOVE_LEFT_TIME = 30;                        //�^�C����30�𒴂�����A�A�C�e���Q�b�g�̃t�H���g�����ɓ����B
const float EXP_CAL_NUM = 1.7f;                       //�w���v�Z�Ŏg���l�B
const int MOVE_UP_TIME = 2;                           //�^�C����2�ɂȂ�܂ŁA�A�C�e���Q�b�g�̃t�H���g����ɓ����B
const float UP_MOVE_SPEED = 20.0f;                    //�A�C�e���Q�b�g�̃t�H���g����ɓ����X�s�[�h�B
ItemGenerator::ItemGenerator()
{
	//�e�N�X�`�������[�h�B
	m_itemTex.Init(L"Resource/sprite/item2.dds", ITEM_SPRITE_SIZE.x, ITEM_SPRITE_SIZE.y);
	m_danyakuTex.Init(L"Resource/sprite/item_danyaku.dds", ITEM_SPRITE_SIZE.x, ITEM_SPRITE_SIZE.y);
	m_kaihukuyakuTex.Init(L"Resource/sprite/item_kaihuku.dds", ITEM_SPRITE_SIZE.x, ITEM_SPRITE_SIZE.y);
	//�A�C�e���̃C���X�^���X���쐬�B
	m_kaihuku = g_goMgr.NewGameObject<Kaihuku>(kaihuku);
	m_danyaku = g_goMgr.NewGameObject<Danyaku>(danyaku);

	for (int i = 0; i < m_maxFontItemNum; i++) {
		m_fontPos[i].x = m_initFontPos.x;
		m_fontPos[i].y = m_initFontPos.y;
		m_timerX[i] = 0;
		m_timerY[i] = 0;
		m_itemName[i] = nullptr;
	}
}
ItemGenerator::~ItemGenerator()
{
	//�A�C�e���̃C���X�^���X���폜����B
	g_goMgr.DeleteGameObject(m_kaihuku);
	g_goMgr.DeleteGameObject(m_danyaku);
}
void ItemGenerator::GetItem(bool* flug, IItemObject* item, wchar_t* name)
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

		//�A�C�e���Q�b�g�̃t�H���g��1�ǉ��B
		m_DisplayingNum++;
		for (int i = 0; i < m_DisplayingNum; i++) {
			//�z���nullptr�������Ă�����A
			//�Q�b�g�����A�C�e���̖��O������B
			if (m_itemName[i] == nullptr) {
				m_itemName[i] = name;
				break;
			}
		}
		int arrayNum = m_DisplayingNum - 2;
		//arrayNum�͔z��̔ԍ��Ȃ̂ŁA
		//m_DisplayingNum�̔ԍ��ƈ�ԐV�����A�C�e���Q�b�g�̃t�H���g�̔ԍ��͊O���̂ŁA
		//2�����B
		//��ԐV�����A�C�e���Q�b�g�̃t�H���g�ȊO�̃t�H���g����Ɉړ������邽�߁A
		//�^�C�}�[�����Z�b�g����B
		for (int i = 0; i < arrayNum; i++) {
			m_timerY[i] = 0;
		}
	}
	*flug = false;
}
void ItemGenerator::SelectItem()
{
	//LB2�{�^���B
	if (g_pad->IsTrigger(enButtonLB2)) {
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
	if (g_pad->IsTrigger(enButtonRB2)) {
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
	if (g_pad->IsTrigger(enButtonA)) {
		//A�{�^�����������B
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
void ItemGenerator::FontItem(Sprite& sprite, IItemObject* item)
{
	sprite.Update(
		m_position,
		CQuaternion::Identity(),
		CVector3::One()
	);
	m_stateNum = item->GetHaveNum();
	sprite.Draw();
	//�\������Ă���A�C�e���̌���\������B
	wchar_t text[256];
	swprintf_s(text, L"%d", m_stateNum);
	m_itemNumFont.Draw(text, m_itemNumFontPos, m_fontColor, m_fontSize);
}
void ItemGenerator::Update()
{
	//�e����擾�������ǂ����B
	GetItem(&m_getDanyakuFlug, m_danyaku ,L"�e��");
	//�񕜖���擾�������ǂ����B
	GetItem(&m_getKaihukuyakuFlug, m_kaihuku, L"�񕜖�");
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
				CVector3::One()
			);
			m_itemTex.Draw();
		}
		if (m_stateNumber == m_danyaku->GetmItemNumber()) {
			//�e���\���B
			FontItem(m_danyakuTex, m_danyaku);
		}
		else if (m_stateNumber == m_kaihuku->GetmItemNumber()) {
			//�񕜖��\���B
			FontItem(m_kaihukuyakuTex, m_kaihuku);
		}
		if (m_DisplayingNum > 0) {
			//�A�C�e���Q�b�g�̃t�H���g��\�����B

			//displayingNum�͔z��̔ԍ��Ȃ̂ŁA
			//m_DisplayingNum�̔ԍ��͊O���̂ŁA1�����B
			int displayingNum = m_DisplayingNum;
			--displayingNum;
			for (int i = 0; i < m_DisplayingNum; i++) {
				m_timerX[i]++;
				//�w���B
				float sisu = MOVE_RIGHT_TIME;
				if (m_timerX[i] <= MOVE_RIGHT_TIME) {
					//�^�C�}�[��10�ȉ�
					//�E�Ɉړ�
					//�w������^�C�}�[�������B�t���[�����Ɏw���������Ă����B
					sisu -= m_timerX[i];
					m_fontPos[i].x += powf(EXP_CAL_NUM, sisu);
				}
				else if (m_timerX[i] >= MOVE_LEFT_TIME) {
					//�^�C�}�[��30�ȏ�ɂȂ���
					//���Ɉړ�
					//�w������^�C�}�[����MOVE_LEFT_TIME���������������B�t���[�����Ɏw���������Ă����B
					sisu -= m_timerX[i] - MOVE_LEFT_TIME;
					m_fontPos[i].x -= powf(EXP_CAL_NUM, sisu);

					if (m_fontPos[i].x <= m_initFontPos.x) {
						//�t�H���g��X���W�������l�ȉ��ɂȂ����B
						//�����l�ɌŒ�B
						m_fontPos[i].x = m_initFontPos.x;
						m_fontPos[i].y = m_initFontPos.y;
						if (i == displayingNum) {
							//�Ō�̃t�H���g��X���W�������l�ȉ��ɂȂ����B
							for (int j = 0; j < m_DisplayingNum; j++) {
								//�^�C�}�[�ƃA�C�e���̖��O���������B
								m_timerX[j] = 0;
								m_timerY[j] = 0;
								m_itemName[j] = nullptr;
							}
							//m_DisplayingNum��0�ɂ��āA�\�����Ȃ��悤�ɂ���B
							m_DisplayingNum = 0;
						}
					}
				}
				if (i < displayingNum) {
					//��ԐV�����A�C�e���Q�b�g�̃t�H���g�̔ԍ������̔z��B
					if (m_timerY[i] <= MOVE_UP_TIME) {
						//��Ɉړ��B
						m_fontPos[i].y -= UP_MOVE_SPEED;
						m_timerY[i]++;
					}
				}
				wchar_t text[256];
				swprintf_s(text, L"%s���l������", m_itemName[i]);
				m_getFontItem[i].Draw(text, m_fontPos[i], m_getItemaFontColor, m_getItemaFontScale);
			}
		}
}
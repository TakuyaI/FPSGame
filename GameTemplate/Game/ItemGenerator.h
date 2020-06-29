#pragma once
#include "IGameObject.h"
#include "Sprite.h"
// �A�C�e���̔ԍ��B
const enum {
	firstnum,
	kaihukuyaku,
	danyaku,
	endnum
};
class ItemGenerator : public IGameObject
{
public:
	ItemGenerator();
	~ItemGenerator();

	void Update();
	void PostRender();
	//�擾�����A�C�e���̌��𑝂₷�B
	void IncreaseItem(int number);
	
private:
	struct ItemName {
		bool getFlug = false; //�擾���Ă��邩�ǂ����B
		int num = 0;          //�擾���Ă�����B
		int number = 0;       //�ԍ��B
	};
	ItemName m_kaihukuyaku;
	ItemName m_danyaku;
	int m_stateNumber = 0; //�\�������A�C�e���̔ԍ��B
	
	Sprite m_itemTex; //�A�C�e���̈�ԉ��̃e�N�X�`���B
	Sprite m_danyakuTex;//�e��̃e�N�X�`���B
	Sprite m_kaihukuyakuTex;//�񕜖�̃e�N�X�`���B
	CVector3 m_position = CVector3::Zero();
	
};


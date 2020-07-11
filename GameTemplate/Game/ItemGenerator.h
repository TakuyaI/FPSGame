#pragma once
#include "IGameObject.h"
#include "Sprite.h"
#include "FontRender.h"
struct ItemName {
	bool getFlug; //�擾���Ă��邩�ǂ����B
	int num;          //�擾���Ă�����B
	int number;       //�ԍ��B
};
class ItemGenerator : public IGameObject
{
public:
	ItemGenerator();
	~ItemGenerator();

	void Update();
	void PostRender();
	void InitItem();
	void GetItem(bool* flug, ItemName* item);

	void SetKaihukuyakuFkug(bool flug)
	{
		m_getKaihukuyakuFlug = flug;
	}

	void SetDanyakuFkug(bool flug)
	{
		m_getDanyakuFlug = flug;
	}
	
private:
	
	int m_stateNumber = 0; //�\�������A�C�e���̔ԍ��B
	int m_stateNum = 0; //�\�������A�C�e���̌��B
	int m_itemNumber = 0;
	const int m_firstNum = 0;
	int m_endNum = 0;

	ItemName m_kaihukuyaku;
	ItemName m_danyaku;

	bool m_getKaihukuyakuFlug = false;
	bool m_getDanyakuFlug = false;

	Sprite m_itemTex; //�A�C�e���̈�ԉ��̃e�N�X�`���B
	Sprite m_danyakuTex;//�e��̃e�N�X�`���B
	Sprite m_kaihukuyakuTex;//�񕜖�̃e�N�X�`���B
	CVector3 m_position = CVector3::Zero();//�e�N�X�`���̍��W�B
	
	bool m_pushLB2Flug = false;//LB2�{�^���������Ă��邩�ǂ����B
	bool m_pushRB2Flug = false;//RB2�{�^���������Ă��邩�ǂ����B
	
	FontRender m_font;
};


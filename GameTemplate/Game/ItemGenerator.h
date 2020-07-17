#pragma once
class Danyaku;
class Kaihuku;
#include "IGameObject.h"
#include "Sprite.h"
#include "IItemObject.h"
#include "Danyaku.h"
#include "Kaihuku.h"
#include "FontRender.h"

class ItemGenerator : public IGameObject
{
public:
	ItemGenerator();
	~ItemGenerator();

	void Update();
	void PostRender();
	void GetItem(bool* flug, IItemObject* item);
	void SelectItem();
	void UseItem();

	void SetKaihukuyakuFkug(bool flug)
	{
		m_getKaihukuyakuFlug = flug;
	}

	void SetDanyakuFkug(bool flug)
	{
		m_getDanyakuFlug = flug;
	}
	
private:
	
	Danyaku* m_danyaku;
	Kaihuku* m_kaihuku;
	static const int m_maxHaveNum = 30;
	IItemObject* m_getItemList[m_maxHaveNum] = { nullptr };

	int m_stateNumber = 0; //�\�������A�C�e���̔ԍ��B
	int m_stateNum = 0; //�\�������A�C�e���̌��B

	bool m_getKaihukuyakuFlug = false;
	bool m_getDanyakuFlug = false;

	Sprite m_itemTex; //�A�C�e���̈�ԉ��̃e�N�X�`���B
	Sprite m_danyakuTex;//�e��̃e�N�X�`���B
	Sprite m_kaihukuyakuTex;//�񕜖�̃e�N�X�`���B
	CVector3 m_position = CVector3::Zero();//�e�N�X�`���̍��W�B
	
	bool m_pushLB2Flug = false;//LB2�{�^���������Ă��邩�ǂ����B
	bool m_pushRB2Flug = false;//RB2�{�^���������Ă��邩�ǂ����B
	bool m_pushAFlug = false;//A�{�^���������Ă��邩�ǂ����B
	FontRender m_font;
};


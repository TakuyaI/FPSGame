#pragma once
#include "IGameObject.h"
#include "Sprite.h"
#include "FontRender.h"
struct ItemName {
	bool getFlug; //取得しているかどうか。
	int num;          //取得している個数。
	int number;       //番号。
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
	
	int m_stateNumber = 0; //表示されるアイテムの番号。
	int m_stateNum = 0; //表示されるアイテムの個数。
	int m_itemNumber = 0;
	const int m_firstNum = 0;
	int m_endNum = 0;

	ItemName m_kaihukuyaku;
	ItemName m_danyaku;

	bool m_getKaihukuyakuFlug = false;
	bool m_getDanyakuFlug = false;

	Sprite m_itemTex; //アイテムの一番下のテクスチャ。
	Sprite m_danyakuTex;//弾薬のテクスチャ。
	Sprite m_kaihukuyakuTex;//回復薬のテクスチャ。
	CVector3 m_position = CVector3::Zero();//テクスチャの座標。
	
	bool m_pushLB2Flug = false;//LB2ボタンを押しているかどうか。
	bool m_pushRB2Flug = false;//RB2ボタンを押しているかどうか。
	
	FontRender m_font;
};


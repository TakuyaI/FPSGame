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

	int m_stateNumber = 0; //表示されるアイテムの番号。
	int m_stateNum = 0; //表示されるアイテムの個数。

	bool m_getKaihukuyakuFlug = false;
	bool m_getDanyakuFlug = false;

	Sprite m_itemTex; //アイテムの一番下のテクスチャ。
	Sprite m_danyakuTex;//弾薬のテクスチャ。
	Sprite m_kaihukuyakuTex;//回復薬のテクスチャ。
	CVector3 m_position = CVector3::Zero();//テクスチャの座標。
	
	bool m_pushLB2Flug = false;//LB2ボタンを押しているかどうか。
	bool m_pushRB2Flug = false;//RB2ボタンを押しているかどうか。
	bool m_pushAFlug = false;//Aボタンを押しているかどうか。
	FontRender m_font;
};


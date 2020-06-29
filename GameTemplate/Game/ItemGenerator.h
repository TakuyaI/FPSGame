#pragma once
#include "IGameObject.h"
#include "Sprite.h"
// アイテムの番号。
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
	//取得したアイテムの個数を増やす。
	void IncreaseItem(int number);
	
private:
	struct ItemName {
		bool getFlug = false; //取得しているかどうか。
		int num = 0;          //取得している個数。
		int number = 0;       //番号。
	};
	ItemName m_kaihukuyaku;
	ItemName m_danyaku;
	int m_stateNumber = 0; //表示されるアイテムの番号。
	
	Sprite m_itemTex; //アイテムの一番下のテクスチャ。
	Sprite m_danyakuTex;//弾薬のテクスチャ。
	Sprite m_kaihukuyakuTex;//回復薬のテクスチャ。
	CVector3 m_position = CVector3::Zero();
	
};


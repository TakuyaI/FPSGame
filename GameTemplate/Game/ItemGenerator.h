#pragma once
#include "IGameObject.h"
#include "Sprite.h"
class ItemGenerator : public IGameObject
{
public:
	ItemGenerator();
	~ItemGenerator();

	void Update();
	void PostRender();

private:
	Sprite m_itemS; //アイテムの一番下のテクスチャ。
	Sprite m_danyaku;//弾薬のテクスチャ。
	int m_itemHave = 0;
	CVector3 m_position = CVector3::Zero();
	/*float m_danyaku = false;
	float m_kaihuku = false;*/
	enum {
		firstnum,
		danyaku,
		kaihuku,
		endnum
	};
};


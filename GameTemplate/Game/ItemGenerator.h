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
	Sprite m_itemS; //�A�C�e���̈�ԉ��̃e�N�X�`���B
	Sprite m_danyaku;//�e��̃e�N�X�`���B
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


#pragma once
//class ItemGenerator;
#include "Player.h"
#include "ItemGenerator.h"
class ItemObject : public IGameObject
{
public:
	ItemObject();
	~ItemObject();

	bool Start();
	void Update();
	void Render();

	void SetPosition(CVector3 pos)
	{
		m_position = pos;
	}
	CVector3 GetPosition()
	{
		return m_position;
	}
private:
	Player* m_player;
	ItemGenerator* m_itemGen;

	SkinModel m_model;
	CVector3 m_position = CVector3::Zero();
	int item = 0;
	int m_itemNumber = 2;
};


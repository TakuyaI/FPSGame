#pragma once
#include "Player.h"
#include "ItemGenerator.h"
class ItemObject : public IGameObject
{
public:
	ItemObject();
	~ItemObject();

	bool Start();
	void ItemUpdate(CVector3* position, int* number);
	void Update();
private:
	Player* m_player;
	ItemGenerator* m_itemGen;
};


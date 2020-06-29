#pragma once
#include "ItemObject.h"
class Kaihuku : public ItemObject
{
public:
	Kaihuku();
	~Kaihuku();

	bool Start();
	void Update();
private:
	CVector3 m_position = CVector3::Zero();//座標。
	int m_number = kaihukuyaku;//アイテムの番号。
};


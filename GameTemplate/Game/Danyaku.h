#pragma once
#include "ItemObject.h"
class Danyaku : public ItemObject
{
public:
	Danyaku();
	~Danyaku();

	bool Start();
	void Update();
private:
	CVector3 m_position = CVector3::Zero();//���W�B
	int m_number = danyaku;//�A�C�e���̔ԍ��B
};


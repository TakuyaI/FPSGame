#pragma once
#include "IItemObject.h"
#include "ItemObject.h"
class Kaihuku : public IItemObject
{
public:
	/// <summary>
	/// �R���X�g���N�^�B
	/// </summary>
	Kaihuku();
	/// <summary>
	/// �f�X�g���N�^�B
	/// </summary>
	~Kaihuku();
	/// <summary>
	/// �A�C�e�����ʁB
	/// </summary>
	void ItemEffects();
private:
};


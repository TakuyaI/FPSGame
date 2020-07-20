#pragma once
#include "IItemObject.h"
#include "ItemObject.h"
class Kaihuku : public IItemObject
{
public:
	/// <summary>
	/// コンストラクタ。
	/// </summary>
	Kaihuku();
	/// <summary>
	/// デストラクタ。
	/// </summary>
	~Kaihuku();
	/// <summary>
	/// アイテム効果。
	/// </summary>
	void ItemEffects();
private:
};


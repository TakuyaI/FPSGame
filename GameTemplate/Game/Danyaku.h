#pragma once
#include "IItemObject.h"
#include "ItemObject.h"
class Danyaku : public IItemObject
{
public:
	/// <summary>
	/// コンストラクタ。
	/// </summary>
	Danyaku();
	/// <summary>
	/// デストラクタ。
	/// </summary>
	~Danyaku();
	/// <summary>
	/// アイテム効果。
	/// </summary>
	void ItemEffects();
private:

};


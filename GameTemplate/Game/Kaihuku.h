#pragma once
#include "IItemObject.h"
#include "ItemObject.h"
#include "Player.h"
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
	Player* m_player;                 //プレイヤーのインスタンス。
	const float m_kaihukuryou = 0.2f; //回復量。プレイヤーのHPが1を100%としたときの数値。
};


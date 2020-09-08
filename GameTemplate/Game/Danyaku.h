#pragma once
#include "ItemObject.h"
#include "GunGenerator.h"


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
	GunGenerator * m_gunGen;                            //GunGeneratorのインスタンス。
	Rifle* m_rifle;                                    //Rifleのインスタンス。
	Shotgun* m_shotGun;                                //Shotgunのインスタンス。
	Sniper* m_sniper;                                  //Sniperのインスタンス。
	const int m_addBullet = 20;                        //加算する弾数。
};


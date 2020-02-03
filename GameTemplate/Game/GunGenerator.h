#pragma once
class Gun;
class GameCamera;
#include "IGameObject.h"
/// <summary>
/// 銃の番号
/// </summary>
struct GunNumber
{
	const enum {
		RIFLE_NUMBER,
		SHOTGUN_NUMBER,
		SNIPER_NUMBER,
		END_NUMBER
	};
};

class GunGenerator : public IGameObject
{
public:
	GunGenerator();
	~GunGenerator();
	/// <summary>
	/// 銃の弾数。
	/// </summary>
	/// <returns></returns>
	int GetGunAmmo();
	/// <summary>
	/// 銃の連射弾数。
	/// </summary>
	/// <returns></returns>
	int GetGunBlaze();
	void SetNextNum(int num)
	{
		m_nextnum = num;
	}
	int GetNextNum()
	{
		return m_nextnum;
	}
	void Update();

	Gun* m_gun;
	GameCamera* m_gameCam;
	int m_nextnum = 0;
	bool a = false;
	int  m_rifleAmmo = 200;             //ライフルの弾数。
	int  m_shotgunAmmo = 60;           //ショットガンの弾数。
	int  m_sniperAmmo = 20;             //スナイパーの弾数。
	int m_rifulBlaze = 50;              //ライフルの連射弾数。
	int m_shotgunBlaze = 10;            //ショットガンの連射弾数。  
	int m_sniperBlaze = 4;              //スナイパーの連射弾数。
};


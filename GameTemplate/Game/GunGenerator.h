#pragma once
class Gun;
class GameCamera;
class Sprite;
class Rifle;
class Shotgun;
class Sniper;
#include "Sprite.h"
#include "IGameObject.h"
#include "Game.h"
/// <summary>
/// e‚Ì”Ô†
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
	/// e‚Ì’e”B
	/// </summary>
	/// <returns></returns>
	int GetGunAmmo();
	/// <summary>
	/// e‚Ì’e”‚ğİ’èB
	/// </summary>
	/// <summary>
	void SetGunAmmo(int ammo);
	/// e‚Ì‘•“U’e”B
	/// </summary>
	/// <returns></returns>
	int GetGunLoading();
	/// <summary>
	///e‚Ì‘•“U’e”‚ğİ’èB 
	/// </summary>
	void SetGunLoading(int loading);
	void SetNextNum(int num)
	{
		m_nextnum = num;
	}
	int GetNextNum()
	{
		return m_nextnum;
	}
	void SetReloadFlug(bool flug)
	{
		m_reloadFlug = flug;
	}
	void SetShootingBulletFlug(bool flug)
	{
		m_shootingBulletFlug = flug;
	}
	void SetmAimFlug(bool flug)
	{
		m_aimFlug = flug;
	}
	bool Start();
	void Update();
	void PostRender();


	Rifle* m_rifle;
	Shotgun* m_shotgun;
	Sniper* m_sniper;
	Game * m_game;
	int m_nextnum = 0;
	int m_num = 0;
	bool a = false;
	int  m_rifleAmmo = 200;             //ƒ‰ƒCƒtƒ‹‚Ì’e”B
	int  m_shotgunAmmo = 60;           //ƒVƒ‡ƒbƒgƒKƒ“‚Ì’e”B
	int  m_sniperAmmo = 20;             //ƒXƒiƒCƒp[‚Ì’e”B
	int m_rifulLoading = 50;              //ƒ‰ƒCƒtƒ‹‚Ì‘•“U’e”B
	int m_shotgunLoading = 10;            //ƒVƒ‡ƒbƒgƒKƒ“‚Ì‘•“U’e”B  
	int m_sniperLoading = 4;              //ƒXƒiƒCƒp[‚Ì‘•“U’e”B

	float m_initGunFlug = false;
	float m_gunChangeFlug = true;
	bool m_reloadFlug = false;
	bool m_shootingBulletFlug = false;
	bool m_aimFlug = false;
	Sprite m_sprite;
};


#pragma once
class Sprite;
class Rifle;
class Shotgun;
class Sniper;
class IGunObject;
class Game;
#include "Sprite.h"
#include "IGameObject.h"
#include "Game.h"
#include "IGunObject.h"
/// <summary>
/// 銃の番号
/// </summary>
struct GunNumber
{
	const enum {
		RIFLE_NUMBER,    //ライフルの番号。
		SHOTGUN_NUMBER,  //ショットガンの番号。
		SNIPER_NUMBER,   //スナイパーの番号。
		END_NUMBER       //最後の番号。
	};
};
class GunGenerator : public IGameObject
{
public:
	/// <summary>
	/// コンストラクタ。
	/// </summary>
	GunGenerator();
	/// <summary>
	/// デストラクタ。
	/// </summary>
	~GunGenerator();
	/// <summary>
	/// スタート関数。
	/// </summary>
	/// <returns></returns>
	bool Start();
	/// <summary>
	/// 更新関数。
	/// </summary>
	void Update();
	/// <summary>
	/// 2D描画。
	/// </summary>
	void PostRender();
	/// <summary>
	/// 銃の弾数を返す。
	/// </summary>
	/// <returns></returns>
	int GetGunAmmo();
	/// <summary>
	/// 銃の弾数を設定。
	/// </summary>
	/// <param name="ammo">弾数。</param>
	void SetGunAmmo(int ammo);
	/// <summary>
	/// 銃の装填弾数を返す。
	/// </summary>
	/// <returns></returns>
	int GetGunLoading();
	/// <summary>
	/// 銃の装填弾数を設定。 
	/// </summary>
	/// <param name="loading">装填弾数。</param>
	void SetGunLoading(int loading);
	/// <summary>
	/// 銃の番号を返す。
	/// </summary>
	/// <returns></returns>
	int GetGunNum()
	{
		return m_gunNum;
	}
	/// <summary>
	/// リロードしたかどうかのフラグを設定する。
	/// </summary>
	/// <param name="flug">フラグ。</param>
	void SetReloadFlug(bool flug)
	{
		m_reloadFlug = flug;
	}
	
	/// <summary>
	/// エイム中かどうかのフラグを設定する。
	/// </summary>
	/// <param name="flug">フラグ。</param>
	void SetmAimFlug(bool flug)
	{
		m_aimFlug = flug;
	}
	/// <summary>
	/// エイム中かどうかのフラグを返す。
	/// </summary>
	/// <returns></returns>
	bool GetAimFlug()
	{
		return m_aimFlug;
	}
	/// <summary>
	/// 銃を切り替えるかどうかのフラグを設定する。
	/// </summary>
	/// <param name="flug">フラグ。</param>
	void SetSwitchFlug(bool flug)
	{
		m_switchFlug = flug;
	}
	/// <summary>
	/// 銃を切り替えるかどうかのフラグを返す。
	/// </summary>
	/// <returns></returns>
	bool GetSwitchFlug()
	{
		return m_switchFlug;
	}
	/// <summary>
	/// 銃をしまっている最中かどうかのフラグを設定する。
	/// </summary>
	/// <param name="flug">フラグ。</param>
	void SetPutAwayFlug(bool flug)
	{
		m_PutAwayFlug = flug;
	}
	/// <summary>
	///銃をしまっている最中かどうかのフラグを返す。
	/// </summary>
	/// <returns></returns>
	bool GetPutAwayFlug()
	{
		return m_PutAwayFlug;
	}
	/// <summary>
	/// 銃を出している最中かどうかを設定する。
	/// </summary>
	/// <param name="flug">フラグ。</param>
	void SetPutOutFlug(bool flug)
	{
		m_PutOutFlug = flug;
	}
	/// <summary>
	/// 銃を出している最中かどうかを返す。
	/// </summary>
	/// <returns></returns>
	bool GetPutOutFlug()
	{
		return m_PutOutFlug;
	}
private:
	IGunObject* m_gun;                    //IGunObjectのインスタンス。
	Game * m_game;                        //Gameのインスタンス。
	int m_gunNum = 0;                     //銃の番号。
	int m_beforeGunNum = 0;               //前の銃の番号。
	int  m_rifleAmmo = 200;               //ライフルの弾数。
	int  m_shotgunAmmo = 30;              //ショットガンの弾数。
	int  m_sniperAmmo = 20;               //スナイパーの弾数。
	int m_rifulLoading = 50;              //ライフルの装填弾数。
	int m_shotgunLoading = 2;             //ショットガンの装填弾数。  
	int m_sniperLoading = 4;              //スナイパーの装填弾数。
	bool m_reloadFlug = false;            //リロードしたかどうか。
	bool m_aimFlug = false;               //エイム中かどうか。
	Sprite m_sprite;                      //銃の照準の画像。
	bool m_switchFlug = false;            //銃を切り替えるかどうか。
	bool m_PutAwayFlug = false;           //銃をしまっている最中かどうか。
	bool m_PutOutFlug = false;            //銃を出している最中かどうか。
};


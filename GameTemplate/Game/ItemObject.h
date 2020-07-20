#pragma once
class ItemGenerator;
#include "Player.h"
#include "Game.h"
#include "ItemGenerator.h"
class ItemObject : public IGameObject
{
public:
	/// <summary>
	/// コンストラクタ。
	/// </summary>
	ItemObject();
	/// <summary>
	/// デストラクタ。
	/// </summary>
	~ItemObject();
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
	/// 3D描画。
	/// </summary>
	void Render();
	/// <summary>
	/// 座標を設定する。
	/// </summary>
	/// <param name="pos">座標。</param>
	void SetPosition(CVector3 pos)
	{
		m_position = pos;
	}
	/// <summary>
	/// 座標を返す。
	/// </summary>
	/// <returns></returns>
	CVector3 GetPosition()
	{
		return m_position;
	}
private:
	Player* m_player;                         //プレイヤーのインスタンス。
	Game* m_game;                             //Gameのインスタンス。
	ItemGenerator* m_itemGen;                 //ItemGeneratorのインスタンス。
	SkinModel m_model;                        //スキンモデル。
	//アイテムの番号。
	const enum {
		danyaku, //弾薬。
		kaihuku, //回復薬。
		itemnum  //アイテムの種類。
	};
	CVector3 m_position = CVector3::Zero();   //座標。
	int m_itemNumber = 0;                     //アイテムの番号。
	float m_getItemRange = 200.0f;            //アイテムをゲットできる範囲。
	
};


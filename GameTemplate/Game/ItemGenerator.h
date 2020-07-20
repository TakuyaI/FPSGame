#pragma once
class Danyaku;
class Kaihuku;
#include "IGameObject.h"
#include "Sprite.h"
#include "IItemObject.h"
#include "Danyaku.h"
#include "Kaihuku.h"
#include "FontRender.h"

class ItemGenerator : public IGameObject
{
public:
	/// <summary>
	/// コンストラクタ。
	/// </summary>
	ItemGenerator();
	/// <summary>
	/// デストラクタ。
	/// </summary>
	~ItemGenerator();
	/// <summary>
	/// 更新関数。
	/// </summary>
	void Update();
	/// <summary>
	/// 2D描画。
	/// </summary>
	void PostRender();
	/// <summary>
	/// アイテムを獲得したかどうか。
	/// </summary>
	/// <param name="flug">フラグ</param>
	/// <param name="item">アイテム</param>
	void GetItem(bool* flug, IItemObject* item);
	/// <summary>
	/// 表示するアイテムを選ぶ関数。
	/// </summary>
	void SelectItem();
	/// <summary>
	/// アイテムを使うかどうか。
	/// </summary>
	void UseItem();
	/// <summary>
	/// 回復薬を取得したかどうかのフラグを設定する。
	/// </summary>
	/// <param name="flug">フラグ</param>
	void SetKaihukuyakuFkug(bool flug)
	{
		m_getKaihukuyakuFlug = flug;
	}
	/// <summary>
	/// 弾薬を取得したかどうかのフラグを設定する。
	/// </summary>
	/// <param name="flug">フラグ</param>
	void SetDanyakuFkug(bool flug)
	{
		m_getDanyakuFlug = flug;
	}
	
private:
	Danyaku* m_danyaku;                                           //弾薬のインスタンス。
	Kaihuku* m_kaihuku;                                           //回復薬のインスタンス。
	static const int m_maxHaveNum = 30;                           //所持できるアイテムの最大数。
	IItemObject* m_getItemList[m_maxHaveNum] = { nullptr };       //IItemObjectの配列。
	int m_stateNumber = 0;                                        //表示されるアイテムの番号。
	int m_stateNum = 0;                                           //表示されるアイテムの個数。
	Sprite m_itemTex;                                             //アイテムの一番下のテクスチャ。
	Sprite m_danyakuTex;                                          //弾薬のテクスチャ。
	Sprite m_kaihukuyakuTex;                                      //回復薬のテクスチャ。
	CVector3 m_position = { 0.0f, -250.0f, 0.0f };                //テクスチャの座標。
	bool m_getKaihukuyakuFlug = false;                            //回復薬を取得したかどうか。
	bool m_getDanyakuFlug = false;                                //弾薬を取得したかどうか。
	bool m_pushLB2Flug = false;                                   //LB2ボタンを押しているかどうか。
	bool m_pushRB2Flug = false;                                   //RB2ボタンを押しているかどうか。
	FontRender m_itemNumFont;                                     //アイテムの個数を表示する文字。
	DirectX::XMFLOAT2 m_fontPos = { 628.0f, 653.0f };             //文字の座標。
	DirectX::FXMVECTOR m_fontColor = { 1.0f, 1.0f, 1.0f, 1.0f };  //文字の色。
	float m_fontSize = 0.7f;                                      //文字のサイズ。
};


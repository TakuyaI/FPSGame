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
	void GetItem(bool* flug, IItemObject* item, wchar_t* name);
	/// <summary>
	/// 表示するアイテムを選ぶ関数。
	/// </summary>
	void SelectItem();
	/// <summary>
	/// アイテムを使うかどうか。
	/// </summary>
	void UseItem();
	/// <summary>
	/// アイテムを表示する関数。
	/// </summary>
	/// <param name="sprite">表示するアイテムのスプライト。</param>
	/// <param name="item">表示するアイテムのインスタンス。</param>
	void FontItem(Sprite& sprite, IItemObject* item);
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
	Danyaku * m_danyaku;                                           //弾薬のインスタンス。
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
	CVector2 m_itemNumFontPos = { 628.0f, 653.0f };               //文字の座標。
	CVector4 m_fontColor = { 1.0f, 1.0f, 1.0f, 1.0f };            //文字の色。
	float m_fontSize = 0.7f;                                      //文字のサイズ。
	static const int m_maxFontItemNum = 10;                       //アイテムゲットのフォントを表示できる最大値。
	FontRender m_getFontItem[m_maxFontItemNum];                   //アイテムゲットのフォント。
	CVector2 m_initFontPos = { -200.0f, 500.0f };                 //アイテムゲットのフォントの初期値。
	CVector2 m_fontPos[m_maxFontItemNum];                         //アイテムゲットのフォントの座標。
	int m_DisplayingNum = 0;                                      //アイテムゲットのフォントを表示している数。
	int m_timerY[m_maxFontItemNum] = { 0 };                       //アイテムゲットのフォントのY方向へ移動するときに使うタイマー。
	int m_timerX[m_maxFontItemNum] = { 0 };                       //アイテムゲットのフォントのX方向へ移動するときに使うタイマー。
	wchar_t* m_itemName[m_maxFontItemNum];                        //ゲットしたアイテムの名前。
	CVector4 m_getItemaFontColor = { 1.0f, 1.0f, 1.0f , 1.0f };   //アイテムゲットのフォントの色。
	float m_getItemaFontScale = 0.5f;                             //アイテムゲットのフォントのサイズ。
};


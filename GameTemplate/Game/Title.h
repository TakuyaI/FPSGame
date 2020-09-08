#pragma once
#include "IGameObject.h"
#include "Sprite.h"
class Title : public IGameObject
{
public:
	/// <summary>
	/// コンストラクタ。
	/// </summary>
	Title();
	/// <summary>
	/// デストラクタ。
	/// </summary>
	~Title();
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

private:
	Sprite m_start;                  //スタートボタンのスプライト。
	Sprite m_haikei;                 //タイトルの背景のスプライト。
	Sprite m_titleName;              //タイトル名のスプライト。
	Sprite m_brack;                  //スタートした時に出る黒色のスプライト。
	CSoundSource m_bgm;              //タイトルのbgm。
	bool m_gameStartFlug = false;    //ゲームスタートしたかどうか。
	float m_startAlpha = 1.0f;       //スタートのα値。
	float m_startAlphaSpeed = 0.0f;  //スタートのα値の変動スピード。
	float m_Alpha = 0.0f;            //黒板のα値。
};


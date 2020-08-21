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
	Sprite m_start;
	Sprite m_haikei;
	Sprite m_titleName; //タイトル名のスプライト。
	CSoundSource m_bgm;
	bool m_gameStartFlug = false;//ゲームスタートしたかどうか。
	float m_startAlpha = 1.0f; //スタートのα値。
	float m_startAlphaSpeed = 0.0f;//スタートのα値の変動スピード。
	float m_Alpha = 0.0f; //黒板のα値。
};


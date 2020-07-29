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
	void PostRender();

	Sprite m_start;
	Sprite m_haikei;
	CSoundSource m_bgm;
	CSoundSource m_cio;
};


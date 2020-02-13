#pragma once
#include "IGameObject.h"
#include "Sprite.h"
#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"
class Title : public IGameObject
{
public:
	Title();
	~Title();

	void Update();
	void PostRender();

	Sprite m_start;
	Sprite m_haikei;
	CSoundEngine m_soundEngine;
	CSoundSource m_bgm;
};


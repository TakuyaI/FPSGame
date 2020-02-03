#pragma once
#include "IGameObject.h"
#include "Sprite.h"
class Title : public IGameObject
{
public:
	Title();
	~Title();

	void Update();
	void PostRender();

	Sprite m_start;
	Sprite m_haikei;
};


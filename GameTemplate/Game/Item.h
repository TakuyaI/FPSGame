#pragma once
class Game;
class Player;
#include "IGameObject.h"
class Item : public IGameObject
{
public:
	Item();
	~Item();

	void Update();
	void Render();
	void PostRender();

	void SetPosition(CVector3 pos)
	{
		m_position = pos;
	}
	CVector3 GetPosition()
	{
		return m_position;
	}

	Player* m_player;
	Game* m_game;
	SkinModel m_model;

	CVector3 m_position = CVector3::Zero();
	CQuaternion m_rotation = CQuaternion::Identity();
};


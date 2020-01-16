#pragma once
class Gun;
class GameCamera;
#include "IGameObject.h"
/// <summary>
/// èeÇÃî‘çÜ
/// </summary>
struct GunNumber
{
	const enum {
		RIFLE_NUMBER,
		SHOTGUN_NUMBER,
		SNIPER_NUMBER,
		END_NUMBER
	};
	/*const int RIFLE_NUMBER = 0;
	const int SHOTGUN_NUMBER = 1;
	const int SNIPER_NUMBER = 2;
	const int END_NUMBER = 3;*/
};

class GunGenerator : public IGameObject
{
public:
	GunGenerator();
	~GunGenerator();

	void SetNextNum(int num)
	{
		m_nextnum = num;
	}
	int GetNextNum()
	{
		return m_nextnum;
	}
	void Update();

	Gun* m_gun;
	GameCamera* m_gameCam;
	int m_nextnum = 0;
	bool a = false;
};


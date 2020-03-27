#pragma once
class Gun;
class GameCamera;
class EnemyGenerator;
class Sprite;
class GunGenerator;
#include "IGameObject.h"
#include "Player.h"
#include "BackGround.h"
#include "GameCamera.h"
#include "Enemy.h"
#include "EnemyGenerator.h"
#include "Gun.h"
#include "Sprite.h"
#include "FontRender.h"
class Game : public IGameObject
{
public:
	Game();
	~Game();


	void Update();
	void PostRender();
	 
	void SetEndFlug(bool flug)
	{
		m_endFlug = flug;
	}
	bool GetEndFlug()
	{
		return m_endFlug;
	}
	void SetKnockDownEnemyNum(int knockdownenemynum)
	{
		m_knockDownEnemyNum = knockdownenemynum;
	}
	int GetKnockDownEnemyNum()
	{
		return m_knockDownEnemyNum;
	}
private:
	FontRender m_font;
	Player* m_player;
	BackGround* m_backGro;
	GameCamera* m_gameCam;
	Enemy* m_enemy;
	EnemyGenerator* m_enemyGen;
	Gun* m_gun;
	GunGenerator* m_gunGen;
	
	int m_gameOverTime = 0; //ゲームオーバーになってから、タイトル画面にもどるまでの時間。
	int m_gameClearTime = 0;
	bool m_endFlug = false; //ゲームが終わったかどうか。
	Sprite m_gameOverSprite; // ゲームオーバースプライト。
	Sprite m_gameClearSprite; //ゲームクリアスプライト。
	int m_knockDownEnemyNum = 10; //倒す敵の数。

	Sprite m_itemS;
};


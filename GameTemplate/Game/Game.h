#pragma once
class GameCamera;
class EnemyGenerator;
class Sprite;
class GunGenerator;
class ItemGenerator;
#include "IGameObject.h"
#include "Player.h"
#include "BackGround.h"
#include "GameCamera.h"
#include "Enemy.h"
#include "DogEnemy.h"
#include "EnemyGenerator.h"
#include "Sprite.h"
#include "FontRender.h"
#include "ItemGenerator.h"
class Game : public IGameObject
{
public:
	Game();
	~Game();

	bool Start();
	void Update();
	void Render();
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
	std::vector<DogEnemy*> GetDogEnemy()
	{
		return m_dogEnemyList;
	}
private:
	FontRender m_font;
	Player* m_player;
	BackGround* m_backGro;
	GameCamera* m_gameCam;
	Enemy* m_enemy;
	EnemyGenerator* m_enemyGen;
	GunGenerator* m_gunGen;
	ItemGenerator* m_itemGen;
	DogEnemy* m_dogEnemy;

	int m_gameOverTime = 0; //ゲームオーバーになってから、タイトル画面にもどるまでの時間。
	int m_gameClearTime = 0;
	bool m_endFlug = false; //ゲームが終わったかどうか。
	Sprite m_gameOverSprite; // ゲームオーバースプライト。
	Sprite m_gameClearSprite; //ゲームクリアスプライト。
	int m_knockDownEnemyNum = 10; //倒す敵の数。


	Level m_level;
	std::vector<Enemy*> m_enemyList;
	std::vector<DogEnemy*> m_dogEnemyList;
	//Sprite m_itemS;
};


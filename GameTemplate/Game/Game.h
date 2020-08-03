#pragma once
class GameCamera;
class Sprite;
class GunGenerator;
#include "IGameObject.h"
#include "Player.h"
#include "BackGround.h"
#include "GameCamera.h"
#include "Enemy.h"
#include "DogEnemy.h"
#include "PointLightObject.h"
#include "Sprite.h"
#include "FontRender.h"
#include "ItemGenerator.h"
class Game : public IGameObject
{
public:
	/// <summary>
	/// コンストラクタ。
	/// </summary>
	Game();
	/// <summary>
	/// デストラクタ。
	/// </summary>
	~Game();
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
	/// 3D描画。
	/// </summary>
	void Render();
	/// <summary>
	/// 2D描画。
	/// </summary>
	void PostRender();
	//
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
	GunGenerator* m_gunGen;
	ItemGenerator* m_itemGen;
	DogEnemy* m_dogEnemy;
	PointLightObject* m_pointLightObj;
	int m_gameOverTime = 0; //ゲームオーバーになってから、タイトル画面にもどるまでの時間。
	int m_gameClearTime = 0;
	bool m_endFlug = false; //ゲームが終わったかどうか。
	Sprite m_gameOverSprite; // ゲームオーバースプライト。
	Sprite m_gameClearSprite; //ゲームクリアスプライト。
	int m_knockDownEnemyNum = 0; //倒す敵の数。


	Level m_level;
	int i = 1;
};


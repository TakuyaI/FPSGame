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
	/// <summary>
	/// ゲームが終わったかどうかのフラグを返す。
	/// </summary>
	/// <returns></returns>
	bool GetEndFlug()
	{
		return m_endFlug;
	}
	/// <summary>
	/// 倒す敵の数を設定。
	/// </summary>
	/// <param name="knockdownenemynum"></param>
	void SetKnockDownEnemyNum(int knockdownenemynum)
	{
		m_knockDownEnemyNum = knockdownenemynum;
	}
	/// <summary>
	/// 倒す敵の数を返す。
	/// </summary>
	/// <returns></returns>
	int GetKnockDownEnemyNum()
	{
		return m_knockDownEnemyNum;
	}
private:
	Level m_level;                                                //レベル。
	FontRender m_font;                                            //FontRenderのインスタンス。
	Player* m_player;                                             //プレイヤーのインスタンス。
	BackGround* m_backGro;                                        //BackGroundのインスタンス。
	GameCamera* m_gameCam;                                        //GameCameraのインスタンス。
	Enemy* m_enemy;                                               //Enemyのインスタンス。
	GunGenerator* m_gunGen;                                       //GunGeneratorのインスタンス。
	ItemGenerator* m_itemGen;                                     //ItemGeneratorのインスタンス。
	DogEnemy* m_dogEnemy;                                         //DogEnemyのインスタンス。
	PointLightObject* m_pointLightObj;                            //PointLightObjectのインスタンス。
	Sprite m_gameOverSprite;                                      //ゲームオーバースプライト。
	Sprite m_gameClearSprite;                                     //ゲームクリアスプライト。
	int m_knockDownEnemyNum = 0;                                  //倒す敵の数。
	int pointLightObjNum = 1;                                     //ポイントライトオブジェクトの番号。0番目はプレイヤーを照らすポイントライト。
	int m_returnTitleTime = 120;                                  //タイトル画面にもどるまでの時間。
	int m_returnTitleTimer = 0;                                   //タイトルに戻るまでのタイマー。
	bool m_endFlug = false;                                       //ゲームが終わったかどうか。
	DirectX::XMFLOAT2 m_fontPos = { 100.0f, 100.0f };             //文字の座標。
	DirectX::FXMVECTOR m_fontColor = { 1.0f, 1.0f, 1.0f, 1.0f };  //文字の色。
	float m_fontScale = 1.0f;                                     //文字のサイズ。
};


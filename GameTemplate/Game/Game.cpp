#include "stdafx.h"
#include "Game.h"
#include "GameManager.h"
#include "Sprite.h"
#include "GunGenerator.h"
Game::Game()
{
	//m_sprite->Init(L"Assets/sprite/aka.dds", 1000.0f, 700.0f);
	m_player = g_goMgr.NewGameObject<Player>(player);
	m_backGro = g_goMgr.NewGameObject<BackGround>(background);
	m_gameCam = g_goMgr.NewGameObject<GameCamera>(gamecamera);
	m_enemyGen = g_goMgr.NewGameObject<EnemyGenerator>(enemygenerator);
	m_gunGen = g_goMgr.NewGameObject<GunGenerator>(gungenerator);
}


Game::~Game()
{

}

void Game::Update()
{
	/*int a = g_goMgr.Rand(10);
	int b = g_goMgr.Rand(10);
	int c = rand();
	int d = rand();*/
}
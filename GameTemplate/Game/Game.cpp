#include "stdafx.h"
#include "Game.h"
#include "GameManager.h"
#include "Title.h"
#include "GunGenerator.h"
Game::Game()
{
	m_sprite.Init(L"Resource/sprite/gameover.dds", 1280.0f, 720.0f);
	m_player = g_goMgr.NewGameObject<Player>(player);
	m_backGro = g_goMgr.NewGameObject<BackGround>(background);
	m_gameCam = g_goMgr.NewGameObject<GameCamera>(gamecamera);
	m_enemyGen = g_goMgr.NewGameObject<EnemyGenerator>(enemygenerator);
	m_gunGen = g_goMgr.NewGameObject<GunGenerator>(gungenerator);
}


Game::~Game()
{
	g_goMgr.DeleteGameObject(m_player);
	g_goMgr.DeleteGameObject(m_backGro);
	g_goMgr.DeleteGameObject(m_gameCam);
	g_goMgr.DeleteGameObject(m_enemyGen);
	g_goMgr.DeleteGameObject(m_gunGen);
}

void Game::Update()
{
	if (g_pad->IsTrigger(enButtonSelect)) {
		m_flug = true;
		g_goMgr.NewGameObject<Title>(title);
		g_goMgr.DeleteGameObject(this);
	}
	if (m_player->GetDeathFlug() != false) {
		m_gameOverTime++;
		if (m_gameOverTime >= 120) {
			g_goMgr.NewGameObject<Title>(title);
			g_goMgr.DeleteGameObject(this);
		}
	}
}
void Game::PostRender()
{
	if (m_player->GetDeathFlug() != false) {
		m_sprite.Draw();
	}
}
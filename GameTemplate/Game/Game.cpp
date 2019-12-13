#include "stdafx.h"
#include "Game.h"
#include "GameManager.h"

Game::Game()
{
	
	m_player = g_goMgr.NewGameObject<Player>();
	m_backGro = g_goMgr.NewGameObject<BackGround>();
	m_gameCam = g_goMgr.NewGameObject<GameCamera>();
	m_enemyGen = g_goMgr.NewGameObject<EnemyGenerator>();
	m_gun = g_goMgr.NewGameObject<Gun>();

	

	m_gameCam->SetPlayer(m_player);
	m_player->SetGameCamera(m_gameCam);
	m_enemyGen->SetPlayer(m_player);
	m_enemyGen->SetGameCamera(m_gameCam);
	m_gameCam->SetEnemyGenerator(m_enemyGen);
	m_gun->SetPlayer(m_player);
	m_gun->SetEenmy(m_enemyGen->GetEnemy());
	m_gun->SetGameCamera(m_gameCam);
}


Game::~Game()
{
	
}

void Game::Update()
{
	//m_gameCam->SetPlayer(m_player);
	//m_player->SetGameCamera(m_gameCam);
	//m_enemyGen->SetPlayer(m_player);
	//m_enemyGen->SetGameCamera(m_gameCam);
	if (m_enemyGen->GetFlug() != 0) {
		m_gameCam->SetEnemy(m_enemyGen->GetEnemy());
	}
}
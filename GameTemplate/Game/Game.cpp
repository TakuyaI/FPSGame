#include "stdafx.h"
#include "Game.h"
#include "GameManager.h"

#include "GunGenerator.h"
Game::Game()
{
	m_sprite.Init(L"Resource/sprite/zyuzi.dds", 256.0f, 144.0f);
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
}
void Game::PostRender()
{
	//m_rotation.SetRotationDeg(CVector3::AxisZ(), 30.0f);
	//m_sprite.Update(
	//	pos,
	//	CQuaternion::Identity(),/*m_rotation*/
	//	scale,
	//	CVector2::Zero()
	//);
	m_sprite.Draw();
}
#include "stdafx.h"
#include "Game.h"
#include "GameManager.h"
#include "Title.h"
#include "GunGenerator.h"
Game::Game()
{
	m_gameOverSprite.Init(L"Resource/sprite/gameover.dds", 1280.0f, 720.0f);
	m_gameClearSprite.Init(L"Resource/sprite/gameclear.dds", 1280.0f, 720.0f);
	//m_itemS.Init(L"Resource/sprite/item.dds", 320.0f, 180.0f);
	//m_player = g_goMgr.NewGameObject<Player>(player);
	//m_backGro = g_goMgr.NewGameObject<BackGround>(background);
	m_gameCam = g_goMgr.NewGameObject<GameCamera>(gamecamera);
	m_enemyGen = g_goMgr.NewGameObject<EnemyGenerator>(enemygenerator);
	m_gunGen = g_goMgr.NewGameObject<GunGenerator>(gungenerator);
	m_itemGen = g_goMgr.NewGameObject<ItemGenerator>(itemgenerator);

	m_level.Init(
		L"Assets/level/stage_00.tkl",
		[&](const LevelObjectData & object) {
			if (wcscmp(object.name, L"player") == 0) {
				m_player = g_goMgr.NewGameObject<Player>(player);
				m_player->SetPosition(object.position);
				m_player->SetRotation(object.rotation);
				return true;
			}
			else if (wcscmp(object.name, L"enemy") == 0) {
				m_enemy = g_goMgr.NewGameObject<Enemy>(enemy);
				m_enemy->SetPosition(object.position);
				m_enemy->SetRotation(object.rotation);
				return true;
			}
			else if (wcscmp(object.name, L"background") == 0) {
				m_backGro = g_goMgr.NewGameObject<BackGround>(background);
				m_backGro->SetPosition(object.position);
				m_backGro->SetRotation(object.rotation);
				return true;
			}
			return false;
		});
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
	//セレクトボタンを押したら、タイトルに戻る。
	if (g_pad->IsTrigger(enButtonSelect)) {
		m_endFlug = true;
		g_goMgr.NewGameObject<Title>(title);
		g_goMgr.DeleteGameObject(this);
	}
	//プレイヤーが」死亡してから２秒後、タイトルに戻る。
	if (m_player->GetDeathFlug() != false) {
		m_gameOverTime++;
		if (m_gameOverTime >= 120) {
			m_endFlug = true;
			g_goMgr.NewGameObject<Title>(title);
			g_goMgr.DeleteGameObject(this);
		}
	}
	if (m_knockDownEnemyNum <= 0) {
		m_gameClearTime++;
		if (m_gameClearTime >= 120) {
			m_endFlug = true;
			g_goMgr.NewGameObject<Title>(title);
			g_goMgr.DeleteGameObject(this);
		}
	}

}
void Game::Render()
{
	m_level.Draw();
}
void Game::PostRender()
{
	/*m_itemS.Update(
		{ 0.0f, -250.0f, 0.0f },
		CQuaternion::Identity(),
		CVector3::One(),
		{0.5f, 0.5f}
	);
	m_itemS.Draw();*/
	if (m_player->GetDeathFlug() != false) {
		m_gameOverSprite.Draw();
	}
	if (m_knockDownEnemyNum <= 0) {
		m_gameClearSprite.Draw();
	}
	wchar_t text[256];
	swprintf_s(text, L" 残り%d体", m_knockDownEnemyNum);
	m_font.Draw(text, { 100.0f, 100.0f }, { 1.0f, 1.0f, 1.0f, 1.0f });
}
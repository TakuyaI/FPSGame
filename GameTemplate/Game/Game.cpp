#include "stdafx.h"
#include "Game.h"
#include "Title.h"
#include "GunGenerator.h"

Game::Game()
{
	m_gameOverSprite.Init(L"Resource/sprite/gameover.dds", 1280.0f, 720.0f);
	m_gameClearSprite.Init(L"Resource/sprite/gameclear.dds", 1280.0f, 720.0f);
	m_level.Init(
		L"Assets/level/stage_02.tkl",
		[&](const LevelObjectData & object) {
			if (wcscmp(object.name, L"player") == 0) {
				m_player = g_goMgr.NewGameObject<Player>(player);
				m_player->SetPosition(object.position);
				m_player->SetRotation(object.rotation);
				return true;
			}
			else if (wcscmp(object.name, L"dogEnemy") == 0) {
				m_dogEnemy = g_goMgr.NewGameObject<DogEnemy>(dogenemy);
				m_dogEnemy->SetPosition(object.position);
				m_dogEnemy->SetRotation(object.rotation);
				m_dogEnemyList.push_back(m_dogEnemy);
				m_knockDownEnemyNum++;
				return true;
			}
			else if (wcscmp(object.name, L"enemy") == 0) {
				m_enemy = g_goMgr.NewGameObject<Enemy>(enemy);
				m_enemy->SetPosition(object.position);
				m_enemy->SetRotation(object.rotation);
				m_enemyList.push_back(m_enemy);
				m_knockDownEnemyNum++;
				return true;
			}
			else if (wcscmp(object.name, L"stage_02") == 0) {
				m_backGro = g_goMgr.NewGameObject<BackGround>(background);
				m_backGro->SetPosition(object.position);
				m_backGro->SetRotation(object.rotation);
				return true;
			}
			else if (wcscmp(object.name, L"pointLightObj") == 0) {
				m_pointLightObj = g_goMgr.NewGameObject<PointLightObject>(pointlight);
				m_pointLightObj->SetPosition(object.position);
				g_goMgr.SetPointLightPos(m_pointLightObj->GetPosition(), i);
				i++;
				return true;
			}
			return false;
		});
	m_gameCam = g_goMgr.NewGameObject<GameCamera>(gamecamera);
	m_gunGen = g_goMgr.NewGameObject<GunGenerator>(gungenerator);
	m_itemGen = g_goMgr.NewGameObject<ItemGenerator>(itemgenerator);
}


Game::~Game()
{
	g_goMgr.DeleteGameObject(m_player);
	g_goMgr.DeleteGameObject(m_backGro);
	g_goMgr.DeleteGameObject(m_gameCam);
	g_goMgr.DeleteGameObject(m_gunGen);
	g_goMgr.DeleteGameObject(m_itemGen);
	g_goMgr.QueryGameObject<Enemy>(enemy, [](Enemy * enemy)->bool
		{
			g_goMgr.DeleteGameObject(enemy);
			return true;
		});
	g_goMgr.QueryGameObject<DogEnemy>(dogenemy, [](DogEnemy * dogenemy)->bool
		{
			g_goMgr.DeleteGameObject(dogenemy);
			return true;
		});
}

bool Game::Start()
{

	return true;
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
	if (m_player->GetDeathFlug() != false) {
		m_gameOverSprite.Draw();
	}
	if (m_knockDownEnemyNum <= 0) {
		m_gameClearSprite.Draw();
	}
	wchar_t text[256];
	swprintf_s(text, L" 残り%d体", m_knockDownEnemyNum);
	m_font.Draw(text, { 100.0f, 100.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }, 1.0f);
}
#include "stdafx.h"
#include "Game.h"
#include "Title.h"
#include "GunGenerator.h"

Game::Game()
{
	////ゲームオーバーのスプライトをロード。
	//m_gameOverSprite.Init(L"Resource/sprite/gameover.dds", FRAME_BUFFER_W, FRAME_BUFFER_H);
	////ゲームクリアのスプライトをロード。
	//m_gameClearSprite.Init(L"Resource/sprite/gameclear.dds", FRAME_BUFFER_W, FRAME_BUFFER_H);
	////レベルをロード。
	//m_level.Init(
	//	L"Assets/level/stage_03.tkl",
	//	[&](const LevelObjectData & object) {
	//		if (wcscmp(object.name, L"player") == 0) {
	//			//プレイヤー。
	//			m_player = g_goMgr.NewGameObject<Player>(player);
	//			m_player->SetPosition(object.position);
	//			m_player->SetRotation(object.rotation);
	//			m_pos = m_player->GetPosition();
	//			return true;
	//		}
	//		else if (wcscmp(object.name, L"dogEnemy") == 0) {
	//			//犬の敵。
	//			m_dogEnemy = g_goMgr.NewGameObject<DogEnemy>(dogenemy);
	//			m_dogEnemy->SetPosition(object.position);
	//			m_dogEnemy->SetRotation(object.rotation);
	//			m_knockDownEnemyNum++;
	//			return true;
	//		}
	//		else if (wcscmp(object.name, L"enemy") == 0) {
	//			//人の敵。
	//			m_enemy = g_goMgr.NewGameObject<Enemy>(enemy);
	//			m_enemy->SetPosition(object.position);
	//			m_enemy->SetRotation(object.rotation);
	//			m_knockDownEnemyNum++;
	//			return true;
	//		}
	//		else if (wcscmp(object.name, L"stage3") == 0) {
	//			//ステージ。
	//			m_backGro = g_goMgr.NewGameObject<BackGround>(background);
	//			m_backGro->SetPosition(object.position);
	//			m_backGro->SetRotation(object.rotation);
	//			return true;
	//		}
	//		else if (wcscmp(object.name, L"pointLightObj") == 0) {
	//			//ポイントライトのオブジェクト。
	//			m_pointLightObj = g_goMgr.NewGameObject<PointLightObject>(pointlight);
	//			m_pointLightObj->SetPosition(object.position);
	//			g_goMgr.SetPointLightPos(m_pointLightObj->GetPosition(), pointLightObjNum);
	//			pointLightObjNum++;
	//			return true;
	//		}
	//		return false;
	//	});
	////GameCameraのインスタンスを作成。
	//m_gameCam = g_goMgr.NewGameObject<GameCamera>(gamecamera);
	////GunGeneratorのインスタンスを作成。
	//m_gunGen = g_goMgr.NewGameObject<GunGenerator>(gungenerator);
	////ItemGeneratorのインスタンスを作成。
	//m_itemGen = g_goMgr.NewGameObject<ItemGenerator>(itemgenerator);

	//


}


Game::~Game()
{
	//インスタンスを削除。
	g_goMgr.DeleteGameObject(m_player);
	g_goMgr.DeleteGameObject(m_backGro);
	g_goMgr.DeleteGameObject(m_gameCam);
	g_goMgr.DeleteGameObject(m_gunGen);
	g_goMgr.DeleteGameObject(m_itemGen);
	//EnemyとDogEnemyはインスタンスがないか探してから、削除する。
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
	//ゲームオーバーのスプライトをロード。
	m_gameOverSprite.Init(L"Resource/sprite/gameover.dds", FRAME_BUFFER_W, FRAME_BUFFER_H);
	//ゲームクリアのスプライトをロード。
	m_gameClearSprite.Init(L"Resource/sprite/gameclear.dds", FRAME_BUFFER_W, FRAME_BUFFER_H);
	//レベルをロード。
	m_level.Init(
		L"Assets/level/stage_03.tkl",
		[&](const LevelObjectData & object) {
			if (wcscmp(object.name, L"player") == 0) {
				//プレイヤー。
				m_player = g_goMgr.NewGameObject<Player>(player);
				m_player->SetPosition(object.position);
				m_player->SetRotation(object.rotation);
				m_pos = m_player->GetPosition();
				return true;
			}
			else if (wcscmp(object.name, L"dogEnemy") == 0) {
				//犬の敵。
				m_dogEnemy = g_goMgr.NewGameObject<DogEnemy>(dogenemy);
				m_dogEnemy->SetPosition(object.position);
				m_dogEnemy->SetRotation(object.rotation);
				m_knockDownEnemyNum++;
				return true;
			}
			else if (wcscmp(object.name, L"enemy") == 0) {
				//人の敵。
				m_enemy = g_goMgr.NewGameObject<Enemy>(enemy);
				m_enemy->SetPosition(object.position);
				m_enemy->SetRotation(object.rotation);
				m_knockDownEnemyNum++;
				return true;
			}
			else if (wcscmp(object.name, L"stage3") == 0) {
				//ステージ。
				m_backGro = g_goMgr.NewGameObject<BackGround>(background);
				m_backGro->SetPosition(object.position);
				m_backGro->SetRotation(object.rotation);
				return true;
			}
			else if (wcscmp(object.name, L"pointLightObj") == 0) {
				//ポイントライトのオブジェクト。
				m_pointLightObj = g_goMgr.NewGameObject<PointLightObject>(pointlight);
				m_pointLightObj->SetPosition(object.position);
				g_goMgr.SetPointLightPos(m_pointLightObj->GetPosition(), pointLightObjNum);
				pointLightObjNum++;
				return true;
			}
			return false;
		});
	//GameCameraのインスタンスを作成。
	m_gameCam = g_goMgr.NewGameObject<GameCamera>(gamecamera);
	//GunGeneratorのインスタンスを作成。
	m_gunGen = g_goMgr.NewGameObject<GunGenerator>(gungenerator);
	//ItemGeneratorのインスタンスを作成。
	m_itemGen = g_goMgr.NewGameObject<ItemGenerator>(itemgenerator);



	m_pos.y += 100.0f;
	for (int i = 0; i < 5; i++) {
		item[i] = g_goMgr.NewGameObject<ItemObject>(itemobject);
		m_pos.z -= 200.0f;
		item[i]->SetPosition(m_pos);
	}
	return true;
}

void Game::Update()
{
#if 0
	//セレクトボタンを押したら、タイトルに戻る。
	if (g_pad->IsTrigger(enButtonSelect)) {
		m_endFlug = true;
		g_goMgr.NewGameObject<Title>(title);
		g_goMgr.DeleteGameObject(this);
	}
#endif
	//プレイヤーが死亡してから２秒後、タイトルに戻る。
	if (m_player->GetDeathFlug() != false) {
		//タイマーを加算。
		m_returnTitleTimer++;
		if (m_returnTitleTimer >= m_returnTitleTime) {
			m_endFlug = true;
			g_goMgr.NewGameObject<Title>(title);
			g_goMgr.DeleteGameObject(this);
		}
	}
	//敵が0になってから２秒後、タイトルに戻る。
	if (m_knockDownEnemyNum <= 0) {
		//タイマーを加算。
		m_returnTitleTimer++;
		if (m_returnTitleTimer >= m_returnTitleTime) {
			m_endFlug = true;
			g_goMgr.NewGameObject<Title>(title);
			g_goMgr.DeleteGameObject(this);
		}
	}
}
void Game::Render()
{
	//レベルを描画。
	m_level.Draw();
}
void Game::PostRender()
{
	if (m_player->GetDeathFlug() != false) {
		//ゲームオーバーを表示。
		m_gameOverSprite.Draw();
	}
	if (m_knockDownEnemyNum <= 0) {
		//ゲームクリアを表示。
		m_gameClearSprite.Draw();
	}
	//文字描画。
	wchar_t text[256];
	swprintf_s(text, L" 残り%d体", m_knockDownEnemyNum);
	m_font.Draw(
		text,
		m_fontPos,
		m_fontColor, 
		m_fontScale
	);
}
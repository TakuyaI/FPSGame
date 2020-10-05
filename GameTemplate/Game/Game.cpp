#include "stdafx.h"
#include "Game.h"
#include "Title.h"
#include "GunGenerator.h"

Game::Game()
{
	////�Q�[���I�[�o�[�̃X�v���C�g�����[�h�B
	//m_gameOverSprite.Init(L"Resource/sprite/gameover.dds", FRAME_BUFFER_W, FRAME_BUFFER_H);
	////�Q�[���N���A�̃X�v���C�g�����[�h�B
	//m_gameClearSprite.Init(L"Resource/sprite/gameclear.dds", FRAME_BUFFER_W, FRAME_BUFFER_H);
	////���x�������[�h�B
	//m_level.Init(
	//	L"Assets/level/stage_03.tkl",
	//	[&](const LevelObjectData & object) {
	//		if (wcscmp(object.name, L"player") == 0) {
	//			//�v���C���[�B
	//			m_player = g_goMgr.NewGameObject<Player>(player);
	//			m_player->SetPosition(object.position);
	//			m_player->SetRotation(object.rotation);
	//			m_pos = m_player->GetPosition();
	//			return true;
	//		}
	//		else if (wcscmp(object.name, L"dogEnemy") == 0) {
	//			//���̓G�B
	//			m_dogEnemy = g_goMgr.NewGameObject<DogEnemy>(dogenemy);
	//			m_dogEnemy->SetPosition(object.position);
	//			m_dogEnemy->SetRotation(object.rotation);
	//			m_knockDownEnemyNum++;
	//			return true;
	//		}
	//		else if (wcscmp(object.name, L"enemy") == 0) {
	//			//�l�̓G�B
	//			m_enemy = g_goMgr.NewGameObject<Enemy>(enemy);
	//			m_enemy->SetPosition(object.position);
	//			m_enemy->SetRotation(object.rotation);
	//			m_knockDownEnemyNum++;
	//			return true;
	//		}
	//		else if (wcscmp(object.name, L"stage3") == 0) {
	//			//�X�e�[�W�B
	//			m_backGro = g_goMgr.NewGameObject<BackGround>(background);
	//			m_backGro->SetPosition(object.position);
	//			m_backGro->SetRotation(object.rotation);
	//			return true;
	//		}
	//		else if (wcscmp(object.name, L"pointLightObj") == 0) {
	//			//�|�C���g���C�g�̃I�u�W�F�N�g�B
	//			m_pointLightObj = g_goMgr.NewGameObject<PointLightObject>(pointlight);
	//			m_pointLightObj->SetPosition(object.position);
	//			g_goMgr.SetPointLightPos(m_pointLightObj->GetPosition(), pointLightObjNum);
	//			pointLightObjNum++;
	//			return true;
	//		}
	//		return false;
	//	});
	////GameCamera�̃C���X�^���X���쐬�B
	//m_gameCam = g_goMgr.NewGameObject<GameCamera>(gamecamera);
	////GunGenerator�̃C���X�^���X���쐬�B
	//m_gunGen = g_goMgr.NewGameObject<GunGenerator>(gungenerator);
	////ItemGenerator�̃C���X�^���X���쐬�B
	//m_itemGen = g_goMgr.NewGameObject<ItemGenerator>(itemgenerator);

	//


}


Game::~Game()
{
	//�C���X�^���X���폜�B
	g_goMgr.DeleteGameObject(m_player);
	g_goMgr.DeleteGameObject(m_backGro);
	g_goMgr.DeleteGameObject(m_gameCam);
	g_goMgr.DeleteGameObject(m_gunGen);
	g_goMgr.DeleteGameObject(m_itemGen);
	//Enemy��DogEnemy�̓C���X�^���X���Ȃ����T���Ă���A�폜����B
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
	//�Q�[���I�[�o�[�̃X�v���C�g�����[�h�B
	m_gameOverSprite.Init(L"Resource/sprite/gameover.dds", FRAME_BUFFER_W, FRAME_BUFFER_H);
	//�Q�[���N���A�̃X�v���C�g�����[�h�B
	m_gameClearSprite.Init(L"Resource/sprite/gameclear.dds", FRAME_BUFFER_W, FRAME_BUFFER_H);
	//���x�������[�h�B
	m_level.Init(
		L"Assets/level/stage_03.tkl",
		[&](const LevelObjectData & object) {
			if (wcscmp(object.name, L"player") == 0) {
				//�v���C���[�B
				m_player = g_goMgr.NewGameObject<Player>(player);
				m_player->SetPosition(object.position);
				m_player->SetRotation(object.rotation);
				m_pos = m_player->GetPosition();
				return true;
			}
			else if (wcscmp(object.name, L"dogEnemy") == 0) {
				//���̓G�B
				m_dogEnemy = g_goMgr.NewGameObject<DogEnemy>(dogenemy);
				m_dogEnemy->SetPosition(object.position);
				m_dogEnemy->SetRotation(object.rotation);
				m_knockDownEnemyNum++;
				return true;
			}
			else if (wcscmp(object.name, L"enemy") == 0) {
				//�l�̓G�B
				m_enemy = g_goMgr.NewGameObject<Enemy>(enemy);
				m_enemy->SetPosition(object.position);
				m_enemy->SetRotation(object.rotation);
				m_knockDownEnemyNum++;
				return true;
			}
			else if (wcscmp(object.name, L"stage3") == 0) {
				//�X�e�[�W�B
				m_backGro = g_goMgr.NewGameObject<BackGround>(background);
				m_backGro->SetPosition(object.position);
				m_backGro->SetRotation(object.rotation);
				return true;
			}
			else if (wcscmp(object.name, L"pointLightObj") == 0) {
				//�|�C���g���C�g�̃I�u�W�F�N�g�B
				m_pointLightObj = g_goMgr.NewGameObject<PointLightObject>(pointlight);
				m_pointLightObj->SetPosition(object.position);
				g_goMgr.SetPointLightPos(m_pointLightObj->GetPosition(), pointLightObjNum);
				pointLightObjNum++;
				return true;
			}
			return false;
		});
	//GameCamera�̃C���X�^���X���쐬�B
	m_gameCam = g_goMgr.NewGameObject<GameCamera>(gamecamera);
	//GunGenerator�̃C���X�^���X���쐬�B
	m_gunGen = g_goMgr.NewGameObject<GunGenerator>(gungenerator);
	//ItemGenerator�̃C���X�^���X���쐬�B
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
	//�Z���N�g�{�^������������A�^�C�g���ɖ߂�B
	if (g_pad->IsTrigger(enButtonSelect)) {
		m_endFlug = true;
		g_goMgr.NewGameObject<Title>(title);
		g_goMgr.DeleteGameObject(this);
	}
#endif
	//�v���C���[�����S���Ă���Q�b��A�^�C�g���ɖ߂�B
	if (m_player->GetDeathFlug() != false) {
		//�^�C�}�[�����Z�B
		m_returnTitleTimer++;
		if (m_returnTitleTimer >= m_returnTitleTime) {
			m_endFlug = true;
			g_goMgr.NewGameObject<Title>(title);
			g_goMgr.DeleteGameObject(this);
		}
	}
	//�G��0�ɂȂ��Ă���Q�b��A�^�C�g���ɖ߂�B
	if (m_knockDownEnemyNum <= 0) {
		//�^�C�}�[�����Z�B
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
	//���x����`��B
	m_level.Draw();
}
void Game::PostRender()
{
	if (m_player->GetDeathFlug() != false) {
		//�Q�[���I�[�o�[��\���B
		m_gameOverSprite.Draw();
	}
	if (m_knockDownEnemyNum <= 0) {
		//�Q�[���N���A��\���B
		m_gameClearSprite.Draw();
	}
	//�����`��B
	wchar_t text[256];
	swprintf_s(text, L" �c��%d��", m_knockDownEnemyNum);
	m_font.Draw(
		text,
		m_fontPos,
		m_fontColor, 
		m_fontScale
	);
}
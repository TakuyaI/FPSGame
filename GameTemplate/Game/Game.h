#pragma once
class GameCamera;
class EnemyGenerator;
class Sprite;
class GunGenerator;
class ItemGenerator;
#include "IGameObject.h"
#include "Player.h"
#include "BackGround.h"
#include "GameCamera.h"
#include "Enemy.h"
#include "EnemyGenerator.h"
#include "Sprite.h"
#include "FontRender.h"
#include "ItemGenerator.h"
class Game : public IGameObject
{
public:
	Game();
	~Game();


	void Update();
	void PostRender();
	 
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
	EnemyGenerator* m_enemyGen;
	GunGenerator* m_gunGen;
	ItemGenerator* m_itemGen;
	
	int m_gameOverTime = 0; //�Q�[���I�[�o�[�ɂȂ��Ă���A�^�C�g����ʂɂ��ǂ�܂ł̎��ԁB
	int m_gameClearTime = 0;
	bool m_endFlug = false; //�Q�[�����I��������ǂ����B
	Sprite m_gameOverSprite; // �Q�[���I�[�o�[�X�v���C�g�B
	Sprite m_gameClearSprite; //�Q�[���N���A�X�v���C�g�B
	int m_knockDownEnemyNum = 10; //�|���G�̐��B

	//Sprite m_itemS;
};


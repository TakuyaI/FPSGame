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
	/// �R���X�g���N�^�B
	/// </summary>
	Game();
	/// <summary>
	/// �f�X�g���N�^�B
	/// </summary>
	~Game();
	/// <summary>
	/// �X�^�[�g�֐��B
	/// </summary>
	/// <returns></returns>
	bool Start();
	/// <summary>
	/// �X�V�֐��B
	/// </summary>
	void Update();
	/// <summary>
	/// 3D�`��B
	/// </summary>
	void Render();
	/// <summary>
	/// 2D�`��B
	/// </summary>
	void PostRender();
	/// <summary>
	/// �Q�[�����I��������ǂ����̃t���O��Ԃ��B
	/// </summary>
	/// <returns></returns>
	bool GetEndFlug()
	{
		return m_endFlug;
	}
	/// <summary>
	/// �|���G�̐���ݒ�B
	/// </summary>
	/// <param name="knockdownenemynum"></param>
	void SetKnockDownEnemyNum(int knockdownenemynum)
	{
		m_knockDownEnemyNum = knockdownenemynum;
	}
	/// <summary>
	/// �|���G�̐���Ԃ��B
	/// </summary>
	/// <returns></returns>
	int GetKnockDownEnemyNum()
	{
		return m_knockDownEnemyNum;
	}
private:
	Level m_level;                                                //���x���B
	FontRender m_font;                                            //FontRender�̃C���X�^���X�B
	Player* m_player;                                             //�v���C���[�̃C���X�^���X�B
	BackGround* m_backGro;                                        //BackGround�̃C���X�^���X�B
	GameCamera* m_gameCam;                                        //GameCamera�̃C���X�^���X�B
	Enemy* m_enemy;                                               //Enemy�̃C���X�^���X�B
	GunGenerator* m_gunGen;                                       //GunGenerator�̃C���X�^���X�B
	ItemGenerator* m_itemGen;                                     //ItemGenerator�̃C���X�^���X�B
	DogEnemy* m_dogEnemy;                                         //DogEnemy�̃C���X�^���X�B
	PointLightObject* m_pointLightObj;                            //PointLightObject�̃C���X�^���X�B
	Sprite m_gameOverSprite;                                      //�Q�[���I�[�o�[�X�v���C�g�B
	Sprite m_gameClearSprite;                                     //�Q�[���N���A�X�v���C�g�B
	int m_knockDownEnemyNum = 0;                                  //�|���G�̐��B
	int pointLightObjNum = 1;                                     //�|�C���g���C�g�I�u�W�F�N�g�̔ԍ��B0�Ԗڂ̓v���C���[���Ƃ炷�|�C���g���C�g�B
	int m_returnTitleTime = 120;                                  //�^�C�g����ʂɂ��ǂ�܂ł̎��ԁB
	int m_returnTitleTimer = 0;                                   //�^�C�g���ɖ߂�܂ł̃^�C�}�[�B
	bool m_endFlug = false;                                       //�Q�[�����I��������ǂ����B
	DirectX::XMFLOAT2 m_fontPos = { 100.0f, 100.0f };             //�����̍��W�B
	DirectX::FXMVECTOR m_fontColor = { 1.0f, 1.0f, 1.0f, 1.0f };  //�����̐F�B
	float m_fontScale = 1.0f;                                     //�����̃T�C�Y�B
};


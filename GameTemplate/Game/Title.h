#pragma once
#include "IGameObject.h"
#include "Sprite.h"
class Title : public IGameObject
{
public:
	/// <summary>
	/// �R���X�g���N�^�B
	/// </summary>
	Title();
	/// <summary>
	/// �f�X�g���N�^�B
	/// </summary>
	~Title();
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
	/// 2D�`��B
	/// </summary>
	void PostRender();

private:
	Sprite m_start;                  //�X�^�[�g�{�^���̃X�v���C�g�B
	Sprite m_haikei;                 //�^�C�g���̔w�i�̃X�v���C�g�B
	Sprite m_titleName;              //�^�C�g�����̃X�v���C�g�B
	Sprite m_brack;                  //�X�^�[�g�������ɏo�鍕�F�̃X�v���C�g�B
	CSoundSource m_bgm;              //�^�C�g����bgm�B
	bool m_gameStartFlug = false;    //�Q�[���X�^�[�g�������ǂ����B
	float m_startAlpha = 1.0f;       //�X�^�[�g�̃��l�B
	float m_startAlphaSpeed = 0.0f;  //�X�^�[�g�̃��l�̕ϓ��X�s�[�h�B
	float m_Alpha = 0.0f;            //���̃��l�B
};


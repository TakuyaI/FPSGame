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
	Sprite m_start;
	Sprite m_haikei;
	Sprite m_titleName; //�^�C�g�����̃X�v���C�g�B
	CSoundSource m_bgm;
	bool m_gameStartFlug = false;//�Q�[���X�^�[�g�������ǂ����B
	float m_startAlpha = 1.0f; //�X�^�[�g�̃��l�B
	float m_startAlphaSpeed = 0.0f;//�X�^�[�g�̃��l�̕ϓ��X�s�[�h�B
	float m_Alpha = 0.0f; //���̃��l�B
};


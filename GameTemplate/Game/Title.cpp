#include "stdafx.h"
#include "Title.h"
#include "Game.h"

const float ALPHA_SPEED = 0.05f;
Title::Title()
{
	//�T�E���h�����[�h�B
	m_bgm.Init(L"Assets/sound/Titlebgm.wav");
	//���[�v������B
	m_bgm.Play(true);
	//�X�v���C�g�����[�h�B
	m_haikei.Init(L"Resource/sprite/titleBack.dds", FRAME_BUFFER_W, FRAME_BUFFER_H);
	m_start.Init(L"Resource/sprite/startbutton.dds", FRAME_BUFFER_W, FRAME_BUFFER_H);
	m_titleName.Init(L"Resource/sprite/titlename.dds", FRAME_BUFFER_W, FRAME_BUFFER_H);
	m_brack.Init(L"Resource/sprite/brack.dds", FRAME_BUFFER_W, FRAME_BUFFER_H);
	//�ŏ��͌����Ȃ��悤�ɂ���B
	m_brack.DeltaAlpha(-1.0f);
	//�X�^�[�g�{�^���̃X�v���C�g�̃��l�̕ϓ��X�s�[�h��ݒ肷��B�B
	m_startAlphaSpeed = ALPHA_SPEED;
}


Title::~Title()
{
}
bool Title::Start()
{
	return true;
}
void Title::Update()
{

	if (g_pad->IsTrigger(enButtonA)) {
		//A�{�^�����������B
		m_gameStartFlug = true;
	}
	else {
		if (
			m_startAlpha >= 1.0f || //m_startAlpha��1�ȏ�B
			m_startAlpha <= 0.0f    //m_startAlpha��0�ȉ��B
			) {
			m_startAlphaSpeed *= -1.0f;
		}
		//m_startAlpha��m_startAlphaSpeed�����Z���Ă����B
		m_startAlpha += m_startAlphaSpeed;
		//���l��ϓ�������B
		m_start.DeltaAlpha(m_startAlphaSpeed);
	}
	if (m_gameStartFlug != false) {
		//�Q�[���X�^�[�g�B
		//���܂ŕ\�����Ă����X�v���C�g�̃��l�����������炵�Ă����B
		m_haikei.DeltaAlpha(-ALPHA_SPEED);
		m_start.DeltaAlpha(-ALPHA_SPEED);
		//���F�̃X�v���C�g�̓��l�𑝂₵�Ă����B
		m_brack.DeltaAlpha(ALPHA_SPEED);
		//m_Alpha��ALPHA_SPEED�����Z�B
		m_Alpha += ALPHA_SPEED;
	}
	if (m_Alpha >= 1.0f) {
		//��ʂ������Ȃ����B
		//Game�̃C���X�^���X�𐶐��B
		g_goMgr.NewGameObject<Game>(game);
		//bgm���X�g�b�v�B
		m_bgm.Stop();
		//�^�C�g���̃C���X�^���X���폜�B
		g_goMgr.DeleteGameObject(this);
	}
}
void Title::PostRender()
{
	//�`��B
	m_haikei.Draw();
	m_start.Draw();
	m_titleName.Draw();
	m_brack.Draw();
}
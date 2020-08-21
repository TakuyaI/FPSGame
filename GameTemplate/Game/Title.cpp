#include "stdafx.h"
#include "Title.h"
#include "Game.h"

const float ALPHA_SPEED = 0.05f;
Title::Title()
{
	//サウンドをロード。
	m_bgm.Init(L"Assets/sound/Titlebgm.wav");
	//ループさせる。
	m_bgm.Play(true);
	//スプライトをロード。
	m_haikei.Init(L"Resource/sprite/orengi.dds", FRAME_BUFFER_W, FRAME_BUFFER_H);
	m_start.Init(L"Resource/sprite/startbutton.dds", FRAME_BUFFER_W, FRAME_BUFFER_H);
	m_titleName.Init(L"Resource/sprite/titlename.dds", FRAME_BUFFER_W, FRAME_BUFFER_H);
	//スタートボタンのスプライトのα値の変動スピードを設定する。。
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
		//Aボタンを押した。
		m_gameStartFlug = true;
	}
	else {
		if (
			m_startAlpha >= 1.0f || //m_startAlphaが1以上。
			m_startAlpha <= 0.0f    //m_startAlphaが0以下。
			) {
			m_startAlphaSpeed *= -1.0f;
		}
		//m_startAlphaにm_startAlphaSpeedを加算していく。
		m_startAlpha += m_startAlphaSpeed;
		//α値を変動させる。
		m_start.DeltaAlpha(m_startAlphaSpeed);
	}
	if (m_gameStartFlug != false) {
		//ゲームスタート。
		m_haikei.DeltaAlpha(-ALPHA_SPEED);
		m_start.DeltaAlpha(-ALPHA_SPEED);
		//m_Alpha += ALPHA_SPEED;
	}
	if (m_Alpha >= 1.0f) {
		g_goMgr.NewGameObject<Game>(game);
		m_bgm.Stop();
		g_goMgr.DeleteGameObject(this);
	}
}
void Title::PostRender()
{
	m_haikei.Draw();
	m_start.Draw();
	m_titleName.Draw();
}
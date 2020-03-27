#include "stdafx.h"
#include "Title.h"
#include "GameManager.h"
#include "Game.h"

Title::Title()
{
	//m_soundEngine.Init();
	m_bgm.Init(L"Assets/sound/op.wav");
	m_cio.Init(L"Assets/sound/gamestart.wav");
	m_bgm.Play(true);


	m_haikei.Init(L"Resource/sprite/orengi.dds", 1280.0f, 720.0f);
	m_start.Init(L"Resource/sprite/st.dds", 1280.0f, 720.0f);
}


Title::~Title()
{
}
void Title::Update()
{
	//m_soundEngine.Update();
	if (GetAsyncKeyState('A')) {
		g_goMgr.NewGameObject<Game>(game);
		m_bgm.Stop();
		g_goMgr.DeleteGameObject(this);
	}
	if (g_pad->IsPress(enButtonB)) {
		m_cio.Play(false);
	}
}
void Title::PostRender()
{
	m_start.Update(
		{-1280.0f / 2.0f, -720.f / 2.0f, 0.0f},
		CQuaternion::Identity(),
		CVector3::One(),
		CVector2::Zero()
	);
	m_haikei.Draw();
	m_start.Draw();
}
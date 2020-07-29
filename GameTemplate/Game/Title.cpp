#include "stdafx.h"
#include "Title.h"
#include "Game.h"

Title::Title()
{
	m_bgm.Init(L"Assets/sound/op.wav");
	m_cio.Init(L"Assets/sound/gamestart.wav");
	m_bgm.Play(true);
	
	m_haikei.Init(L"Resource/sprite/orengi.dds", FRAME_BUFFER_W, FRAME_BUFFER_H);
	m_start.Init(L"Resource/sprite/st.dds", FRAME_BUFFER_W, FRAME_BUFFER_H);
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
	if (g_pad->IsPress(enButtonB)) {
		g_goMgr.NewGameObject<Game>(game);
		m_bgm.Stop();
		g_goMgr.DeleteGameObject(this);
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
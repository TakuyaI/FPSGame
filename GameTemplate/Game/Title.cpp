#include "stdafx.h"
#include "Title.h"
#include "GameManager.h"
#include "Game.h"

Title::Title()
{
	m_haikei.Init(L"Resource/sprite/title_test.dds", 1280.0f, 720.0f);
	m_start.Init(L"Resource/sprite/st.dds", 128.0f, 72.0f);
}


Title::~Title()
{
}
void Title::Update()
{
	if (g_pad->IsPress(enButtonA)) {
		g_goMgr.NewGameObject<Game>(game);
		g_goMgr.DeleteGameObject(this);
	}
}
void Title::PostRender()
{
	m_haikei.Draw();
	m_start.Draw();
}
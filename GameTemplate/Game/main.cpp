#include "stdafx.h"
#include "system/system.h"
//#include "Game.h"
#include "IGameObject.h"
#include "Title.h"
#include "level/Level.h"

///////////////////////////////////////////////////////////////////
// ウィンドウプログラムのメイン関数。
///////////////////////////////////////////////////////////////////
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	//ゲームの初期化。
	InitGame(hInstance, hPrevInstance, lpCmdLine, nCmdShow, "Game");

	//カメラを初期化。
	g_camera3D.SetPosition({ 0.0f, 100.0f, 300.0f });
	g_camera3D.SetTarget({ 0.0f, 100.0f, 0.0f });
	g_camera3D.SetFar(10000.0f);
	
	//
	g_camera2D.SetPosition({ 0.0f, 0.0f, -1.0f });
	g_camera2D.SetTarget({ 0.0f, 0.0f, 0.0f });
	g_camera2D.SetNear(0.1f);
	g_camera2D.SetFar(1000.0f);
	g_camera2D.SetUpdateProjMatrixFunc(Camera::enUpdateProjMatrixFunc_Ortho);
	CSoundEngine soundEngine;
	soundEngine.Init();
	g_goMgr.NewGameObject<Title>(100);
	bool debugFlug = false;
	//ゲームループ。
	while (DispatchWindowMessage() == true)
	{
		//描画開始。
		g_graphicsEngine->BegineRender();
		//ゲームパッドの更新。	
		for (auto& pad : g_pad) {
			pad.Update();
		}
		g_goMgr.Init();
		g_goMgr.Update();
		soundEngine.Update();
		//物理エンジンの更新。
		g_physics.Update();
		g_goMgr.Render();

		//カメラの更新。
		g_camera3D.Update();
		g_camera2D.Update();
#if 0
		if (g_pad->IsPress(enButtonB)) {
			//コリジョン表示。
			g_physics.DebugDraw();
		}
#endif
		//描画終了。
		g_graphicsEngine->EndRender();
	}
}
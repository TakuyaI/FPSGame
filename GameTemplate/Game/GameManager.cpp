#include "stdafx.h"
#include "GameManager.h"

//GameManagerクラスのインスタンス。
GameManager g_goMgr;

GameManager::GameManager()
{
}
GameManager::~GameManager()
{
}

void GameManager::Init()
{
	if (m_flug != true) {
		//メインとなるレンダリングターゲットを作成する。
		m_mainRenderTarget.Create(
			FRAME_BUFFER_W,
			FRAME_BUFFER_H,
			DXGI_FORMAT_R8G8B8A8_UNORM
		);

		//メインレンダリングターゲットに描かれた絵を
		//フレームバッファにコピーするためのスプライトを初期化する。
		m_copyMainRtToFrameBufferSprite.Init(
			m_mainRenderTarget.GetRenderTargetSRV(),
			FRAME_BUFFER_W,
			FRAME_BUFFER_H
		);
		m_flug = true;
	}
}
void GameManager::ChangeRenderTarget(ID3D11DeviceContext* d3dDeviceContext, RenderTarget* renderTarget, D3D11_VIEWPORT* viewport)
{
	ChangeRenderTarget(
		d3dDeviceContext,
		renderTarget->GetRenderTargetView(),
		renderTarget->GetDepthStensilView(),
		viewport
	);
}
void GameManager::ChangeRenderTarget(ID3D11DeviceContext* d3dDeviceContext, ID3D11RenderTargetView* renderTarget, ID3D11DepthStencilView* depthStensil, D3D11_VIEWPORT* viewport)
{
	ID3D11RenderTargetView* rtTbl[] = {
		renderTarget
	};
	//レンダリングターゲットの切り替え。
	d3dDeviceContext->OMSetRenderTargets(1, rtTbl, depthStensil);
	if (viewport != nullptr) {
		//ビューポートが指定されていたら、ビューポートも変更する。
		d3dDeviceContext->RSSetViewports(1, viewport);
	}
}
void GameManager::Update()
{
	
	
		////描画開始。
		//g_graphicsEngine->BegineRender();
		//フレームバッファののレンダリングターゲットをバックアップしておく。
		auto d3dDeviceContext = g_graphicsEngine->GetD3DDeviceContext();
		d3dDeviceContext->OMGetRenderTargets(
			1,
			&m_frameBufferRenderTargetView,
			&m_frameBufferDepthStencilView
		);
		//ビューポートもバックアップを取っておく。
		unsigned int numViewport = 1;
		d3dDeviceContext->RSGetViewports(&numViewport, &m_frameBufferViewports);

	{
		//レンダリングターゲットをメインに変更する。
		auto d3dDeviceContext = g_graphicsEngine->GetD3DDeviceContext();
		ChangeRenderTarget(d3dDeviceContext, &m_mainRenderTarget, &m_frameBufferViewports);
		//メインレンダリングターゲットをクリアする。
		float clearColor[] = { 0.0f, 0.0f, 0.0f, 1.0f };
		m_mainRenderTarget.ClearRenderTarget(clearColor);


		

		//登録されているゲームオブジェクトの更新処理を呼ぶ。
		for (auto go : m_goList) {
			go->Update();
		}
	}
	
		
	{
		//レンダリングターゲットをフレームバッファに戻す。
		auto d3dDeviceContext = g_graphicsEngine->GetD3DDeviceContext();
		ChangeRenderTarget(
			d3dDeviceContext,
			m_frameBufferRenderTargetView,
			m_frameBufferDepthStencilView,
			&m_frameBufferViewports
		);
		m_copyMainRtToFrameBufferSprite.Update(CVector3::Zero(), CQuaternion::Identity(), CVector3::One());
		//ドロドロ
		m_copyMainRtToFrameBufferSprite.Draw();

		m_frameBufferRenderTargetView->Release();
		m_frameBufferDepthStencilView->Release();
	}

	

	//g_graphicsEngine->EndRender();

	for (auto it = m_goList.begin(); it != m_goList.end();) {
		if ((*it)->IsReqDelete()) {
			//削除リクエストを受けているので、削除する。
			delete *it;
			it = m_goList.erase(it);
		}
		else {
			//リクエストを受けていない。
			it++;
		}
	}
}

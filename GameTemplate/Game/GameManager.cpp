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
	//InitTranslucentBlendState();
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

void GameManager::InitTranslucentBlendState()
{
	//例のごとく、作成するブレンドステートの情報を設定する。
	CD3D11_DEFAULT defaultSettings;
	//デフォルトセッティングで初期化する。
	CD3D11_BLEND_DESC blendDesc(defaultSettings);

	//αブレンディングを有効にする。
	blendDesc.RenderTarget[0].BlendEnable = true;

	//ソースカラーのブレンディング方法を指定している。
	//ソースカラーとはピクセルシェーダ―からの出力を指している。
	//この指定では、ソースカラーをSRC(rgba)とすると、
	//最終的なソースカラーは下記のように計算される。
	//最終的なソースカラー = SRC.rgb × SRC.a・・・・・・　①
	blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;

	//ディスティネーションカラーのブレンディング方法を指定している。
	//ディスティネーションカラーとは、
	//すでに描き込まれているレンダリングターゲットのカラーを指している。
	//この指定では、ディスティネーションカラーをDEST(rgba)、
	//ソースカラーをSRC(RGBA)とすると、最終的なディスティネーションカラーは
	//下記のように計算される。
	//最終的なディスティネーションカラー = DEST.rgb × (1.0f - SRC.a)・・・・・②
	blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;

	//最終的にレンダリングターゲットに描き込まれるカラーの計算方法を指定している。
	//この指定だと、①＋②のカラーが書き込まれる。
	//つまり、最終的にレンダリングターゲットに描き込まれるカラーは
	//SRC.rgb × SRC.a + DEST.rgb × (1.0f - SRC.a)
	//となる。
	blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;

	//この設定で、ブレンドステートを作成すると
	//半透明合成を行えるブレンドステートが作成できる。
	auto d3dDevice = g_graphicsEngine->GetD3DDevice();
	d3dDevice->CreateBlendState(&blendDesc, &m_translucentBlendState);
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
		//登録されているゲームオブジェクトの更新処理を呼ぶ。
		for (auto go : m_goList) {
			go->Update();
		}

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

void GameManager::Render()
{
	//描画開始。
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
			go->Render();
		}
		
		ChangeRenderTarget(
			d3dDeviceContext,
			m_mainRenderTarget.GetRenderTargetView(),
			nullptr,
			&m_frameBufferViewports
		);
		
		//2D
		for (auto go : m_goList) {
			go->PostRender();
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

}

#include "stdafx.h"
#include "GameManager.h"
//GameManagerクラスのインスタンス。
GameManager g_goMgr;
const float LIGHT_CAMERA_POS_Y = 500.0f; //ライトカメラのY座標。
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
		//InitTranslucentBlendState();
		InitEffekseer();
		m_shadowMap.SetShadowMapRT(2048, 2048);

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
	blendDesc.RenderTarget[0].SrcBlend = /*D3D11_BLEND_SRC_ALPHA*/D3D11_BLEND_ONE;

	//ディスティネーションカラーのブレンディング方法を指定している。
	//ディスティネーションカラーとは、
	//すでに描き込まれているレンダリングターゲットのカラーを指している。
	//この指定では、ディスティネーションカラーをDEST(rgba)、
	//ソースカラーをSRC(RGBA)とすると、最終的なディスティネーションカラーは
	//下記のように計算される。
	//最終的なディスティネーションカラー = DEST.rgb × (1.0f - SRC.a)・・・・・②
	blendDesc.RenderTarget[0].DestBlend = /*D3D11_BLEND_INV_SRC_ALPHA*/D3D11_BLEND_ONE;

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
void GameManager::InitEffekseer()
{
	//レンダラーを初期化。
	m_effekseerRenderer = EffekseerRendererDX11::Renderer::Create(
		g_graphicsEngine->GetD3DDevice(),			//D3Dデバイス。
		g_graphicsEngine->GetD3DDeviceContext(),	//D3Dデバイスコンテキスト。
		20000										//板ポリの最大数。
	);
	//エフェクトマネージャを初期化。
	m_effekseerManager = Effekseer::Manager::Create(10000);

	// 描画用インスタンスから描画機能を設定
	m_effekseerManager->SetSpriteRenderer(m_effekseerRenderer->CreateSpriteRenderer());
	m_effekseerManager->SetRibbonRenderer(m_effekseerRenderer->CreateRibbonRenderer());
	m_effekseerManager->SetRingRenderer(m_effekseerRenderer->CreateRingRenderer());
	m_effekseerManager->SetTrackRenderer(m_effekseerRenderer->CreateTrackRenderer());
	m_effekseerManager->SetModelRenderer(m_effekseerRenderer->CreateModelRenderer());

	// 描画用インスタンスからテクスチャの読込機能を設定
	// 独自拡張可能、現在はファイルから読み込んでいる。
	m_effekseerManager->SetTextureLoader(m_effekseerRenderer->CreateTextureLoader());
	m_effekseerManager->SetModelLoader(m_effekseerRenderer->CreateModelLoader());

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
	////登録されているゲームオブジェクトのSatrt関数1回を呼ぶ。
	//for (auto go : m_goList) {
	//	if (go->GetmStartEndFlug() != true) {
	//		go->Start();
	//		go->SetStartEndFlug(true);
	//	}
	//}
	//	//登録されているゲームオブジェクトの更新処理を呼ぶ。
	//	for (auto go : m_goList) {
	//		if (go->GetmStartEndFlug() != false
	//			&& go->IsReqDelete() == false
	//		) {
	//			go->Update();
	//		}
	//	}
	//登録されているゲームオブジェクトのSatrt関数1回を呼ぶ。
	for (auto go : m_goList) {
		if (go->GetmStartEndFlug() != true) {
			go->Start();
			go->SetStartEndFlug(true);
		}
	    if (go->IsReqDelete() == false) {
			go->Update();
		}
	}
		//Effekseerカメラ行列を設定。
		//まずはEffeseerの行列型の変数に、カメラ行列とプロジェクション行列をコピー。
		Effekseer::Matrix44 efCameraMat;
		g_camera3D.GetViewMatrix().CopyTo(efCameraMat);
		Effekseer::Matrix44 efProjMat;
		g_camera3D.GetProjectionMatrix().CopyTo(efProjMat);
		//カメラ行列とプロジェクション行列を設定。
		m_effekseerRenderer->SetCameraMatrix(efCameraMat);
		m_effekseerRenderer->SetProjectionMatrix(efProjMat);
		//Effekseerを更新。
		m_effekseerManager->Update();


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
	for (auto go : m_goList) {
		go->SetRegistShadowCaster();
	}
	CVector3 m_lightCameraPos = m_playerPos; //ライトの座標。
	m_lightCameraPos.y = LIGHT_CAMERA_POS_Y;
	m_shadowMap.Update(
		m_lightCameraPos,
		m_playerPos
	);
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
	
	//シャドウマップにレンダリング
	m_shadowMap.RenderToShadowMap();
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
		//エフェクトは不透明オブジェクトを描画した後で描画する。
		m_effekseerRenderer->BeginRendering();
		m_effekseerManager->Draw();
		m_effekseerRenderer->EndRendering();

		ChangeRenderTarget(
			d3dDeviceContext,
			m_mainRenderTarget.GetRenderTargetView(),
			nullptr,
			&m_frameBufferViewports
		);
		
		float blendFactor[] = { 0.0f, 0.0f, 0.0f, 0.0f };
		//半透明合成のブレンドステートを設定する。
		d3dDeviceContext->OMSetBlendState(
			m_translucentBlendState,	//設定するブレンディングステート
			blendFactor,				//ブレンディングファクター。気にしなくてよい
			0xffffffff					//サンプリングマスク。気にしなくてよい。
		);
		//2D
		for (auto go : m_goList) {
			if (go->GetPostRenderPriority() != false) {
				go->PostRender();
			}
		}
		for (auto go : m_goList) {
			if (go->GetPostRenderPriority() != true) {
				go->PostRender();
			}
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

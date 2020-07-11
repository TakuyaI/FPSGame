#include "stdafx.h"
#include "GameManager.h"
//GameManager�N���X�̃C���X�^���X�B
GameManager g_goMgr;
const float LIGHT_CAMERA_POS_Y = 500.0f; //���C�g�J������Y���W�B
GameManager::GameManager()
{
}
GameManager::~GameManager()
{
}

void GameManager::Init()
{
	if (m_flug != true) {
		//���C���ƂȂ郌���_�����O�^�[�Q�b�g���쐬����B
		m_mainRenderTarget.Create(
			FRAME_BUFFER_W,
			FRAME_BUFFER_H,
			DXGI_FORMAT_R8G8B8A8_UNORM
		);

		//���C�������_�����O�^�[�Q�b�g�ɕ`���ꂽ�G��
		//�t���[���o�b�t�@�ɃR�s�[���邽�߂̃X�v���C�g������������B
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
	//��̂��Ƃ��A�쐬����u�����h�X�e�[�g�̏���ݒ肷��B
	CD3D11_DEFAULT defaultSettings;
	//�f�t�H���g�Z�b�e�B���O�ŏ���������B
	CD3D11_BLEND_DESC blendDesc(defaultSettings);

	//���u�����f�B���O��L���ɂ���B
	blendDesc.RenderTarget[0].BlendEnable = true;

	//�\�[�X�J���[�̃u�����f�B���O���@���w�肵�Ă���B
	//�\�[�X�J���[�Ƃ̓s�N�Z���V�F�[�_�\����̏o�͂��w���Ă���B
	//���̎w��ł́A�\�[�X�J���[��SRC(rgba)�Ƃ���ƁA
	//�ŏI�I�ȃ\�[�X�J���[�͉��L�̂悤�Ɍv�Z�����B
	//�ŏI�I�ȃ\�[�X�J���[ = SRC.rgb �~ SRC.a�E�E�E�E�E�E�@�@
	blendDesc.RenderTarget[0].SrcBlend = /*D3D11_BLEND_SRC_ALPHA*/D3D11_BLEND_ONE;

	//�f�B�X�e�B�l�[�V�����J���[�̃u�����f�B���O���@���w�肵�Ă���B
	//�f�B�X�e�B�l�[�V�����J���[�Ƃ́A
	//���łɕ`�����܂�Ă��郌���_�����O�^�[�Q�b�g�̃J���[���w���Ă���B
	//���̎w��ł́A�f�B�X�e�B�l�[�V�����J���[��DEST(rgba)�A
	//�\�[�X�J���[��SRC(RGBA)�Ƃ���ƁA�ŏI�I�ȃf�B�X�e�B�l�[�V�����J���[��
	//���L�̂悤�Ɍv�Z�����B
	//�ŏI�I�ȃf�B�X�e�B�l�[�V�����J���[ = DEST.rgb �~ (1.0f - SRC.a)�E�E�E�E�E�A
	blendDesc.RenderTarget[0].DestBlend = /*D3D11_BLEND_INV_SRC_ALPHA*/D3D11_BLEND_ONE;

	//�ŏI�I�Ƀ����_�����O�^�[�Q�b�g�ɕ`�����܂��J���[�̌v�Z���@���w�肵�Ă���B
	//���̎w�肾�ƁA�@�{�A�̃J���[���������܂��B
	//�܂�A�ŏI�I�Ƀ����_�����O�^�[�Q�b�g�ɕ`�����܂��J���[��
	//SRC.rgb �~ SRC.a + DEST.rgb �~ (1.0f - SRC.a)
	//�ƂȂ�B
	blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;

	//���̐ݒ�ŁA�u�����h�X�e�[�g���쐬�����
	//�������������s����u�����h�X�e�[�g���쐬�ł���B
	auto d3dDevice = g_graphicsEngine->GetD3DDevice();
	d3dDevice->CreateBlendState(&blendDesc, &m_translucentBlendState);
}
void GameManager::InitEffekseer()
{
	//�����_���[���������B
	m_effekseerRenderer = EffekseerRendererDX11::Renderer::Create(
		g_graphicsEngine->GetD3DDevice(),			//D3D�f�o�C�X�B
		g_graphicsEngine->GetD3DDeviceContext(),	//D3D�f�o�C�X�R���e�L�X�g�B
		20000										//�|���̍ő吔�B
	);
	//�G�t�F�N�g�}�l�[�W�����������B
	m_effekseerManager = Effekseer::Manager::Create(10000);

	// �`��p�C���X�^���X����`��@�\��ݒ�
	m_effekseerManager->SetSpriteRenderer(m_effekseerRenderer->CreateSpriteRenderer());
	m_effekseerManager->SetRibbonRenderer(m_effekseerRenderer->CreateRibbonRenderer());
	m_effekseerManager->SetRingRenderer(m_effekseerRenderer->CreateRingRenderer());
	m_effekseerManager->SetTrackRenderer(m_effekseerRenderer->CreateTrackRenderer());
	m_effekseerManager->SetModelRenderer(m_effekseerRenderer->CreateModelRenderer());

	// �`��p�C���X�^���X����e�N�X�`���̓Ǎ��@�\��ݒ�
	// �Ǝ��g���\�A���݂̓t�@�C������ǂݍ���ł���B
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
	//�����_�����O�^�[�Q�b�g�̐؂�ւ��B
	d3dDeviceContext->OMSetRenderTargets(1, rtTbl, depthStensil);
	if (viewport != nullptr) {
		//�r���[�|�[�g���w�肳��Ă�����A�r���[�|�[�g���ύX����B
		d3dDeviceContext->RSSetViewports(1, viewport);
	}
}
void GameManager::Update()
{
	////�o�^����Ă���Q�[���I�u�W�F�N�g��Satrt�֐�1����ĂԁB
	//for (auto go : m_goList) {
	//	if (go->GetmStartEndFlug() != true) {
	//		go->Start();
	//		go->SetStartEndFlug(true);
	//	}
	//}
	//	//�o�^����Ă���Q�[���I�u�W�F�N�g�̍X�V�������ĂԁB
	//	for (auto go : m_goList) {
	//		if (go->GetmStartEndFlug() != false
	//			&& go->IsReqDelete() == false
	//		) {
	//			go->Update();
	//		}
	//	}
	//�o�^����Ă���Q�[���I�u�W�F�N�g��Satrt�֐�1����ĂԁB
	for (auto go : m_goList) {
		if (go->GetmStartEndFlug() != true) {
			go->Start();
			go->SetStartEndFlug(true);
		}
	    if (go->IsReqDelete() == false) {
			go->Update();
		}
	}
		//Effekseer�J�����s���ݒ�B
		//�܂���Effeseer�̍s��^�̕ϐ��ɁA�J�����s��ƃv���W�F�N�V�����s����R�s�[�B
		Effekseer::Matrix44 efCameraMat;
		g_camera3D.GetViewMatrix().CopyTo(efCameraMat);
		Effekseer::Matrix44 efProjMat;
		g_camera3D.GetProjectionMatrix().CopyTo(efProjMat);
		//�J�����s��ƃv���W�F�N�V�����s���ݒ�B
		m_effekseerRenderer->SetCameraMatrix(efCameraMat);
		m_effekseerRenderer->SetProjectionMatrix(efProjMat);
		//Effekseer���X�V�B
		m_effekseerManager->Update();


	for (auto it = m_goList.begin(); it != m_goList.end();) {
		if ((*it)->IsReqDelete()) {
			//�폜���N�G�X�g���󂯂Ă���̂ŁA�폜����B
			delete *it;
			it = m_goList.erase(it);
		}
		else {
			//���N�G�X�g���󂯂Ă��Ȃ��B
			it++;
		}
	}
	for (auto go : m_goList) {
		go->SetRegistShadowCaster();
	}
	CVector3 m_lightCameraPos = m_playerPos; //���C�g�̍��W�B
	m_lightCameraPos.y = LIGHT_CAMERA_POS_Y;
	m_shadowMap.Update(
		m_lightCameraPos,
		m_playerPos
	);
}

void GameManager::Render()
{
	//�`��J�n�B
	//g_graphicsEngine->BegineRender();
	//�t���[���o�b�t�@�̂̃����_�����O�^�[�Q�b�g���o�b�N�A�b�v���Ă����B
	auto d3dDeviceContext = g_graphicsEngine->GetD3DDeviceContext();
	d3dDeviceContext->OMGetRenderTargets(
		1,
		&m_frameBufferRenderTargetView,
		&m_frameBufferDepthStencilView
	);
	//�r���[�|�[�g���o�b�N�A�b�v������Ă����B
	unsigned int numViewport = 1;
	d3dDeviceContext->RSGetViewports(&numViewport, &m_frameBufferViewports);
	
	//�V���h�E�}�b�v�Ƀ����_�����O
	m_shadowMap.RenderToShadowMap();
	{
		//�����_�����O�^�[�Q�b�g�����C���ɕύX����B
		auto d3dDeviceContext = g_graphicsEngine->GetD3DDeviceContext();
		ChangeRenderTarget(d3dDeviceContext, &m_mainRenderTarget, &m_frameBufferViewports);
		//���C�������_�����O�^�[�Q�b�g���N���A����B
		float clearColor[] = { 0.0f, 0.0f, 0.0f, 1.0f };
		m_mainRenderTarget.ClearRenderTarget(clearColor);
		
		//�o�^����Ă���Q�[���I�u�W�F�N�g�̍X�V�������ĂԁB
		for (auto go : m_goList) {
			go->Render();
		}
		//�G�t�F�N�g�͕s�����I�u�W�F�N�g��`�悵����ŕ`�悷��B
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
		//�����������̃u�����h�X�e�[�g��ݒ肷��B
		d3dDeviceContext->OMSetBlendState(
			m_translucentBlendState,	//�ݒ肷��u�����f�B���O�X�e�[�g
			blendFactor,				//�u�����f�B���O�t�@�N�^�[�B�C�ɂ��Ȃ��Ă悢
			0xffffffff					//�T���v�����O�}�X�N�B�C�ɂ��Ȃ��Ă悢�B
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
		//�����_�����O�^�[�Q�b�g���t���[���o�b�t�@�ɖ߂��B
		auto d3dDeviceContext = g_graphicsEngine->GetD3DDeviceContext();
		ChangeRenderTarget(
			d3dDeviceContext,
			m_frameBufferRenderTargetView,
			m_frameBufferDepthStencilView,
			&m_frameBufferViewports
		);
		
		m_copyMainRtToFrameBufferSprite.Update(CVector3::Zero(), CQuaternion::Identity(), CVector3::One());
		
		//�h���h��
		m_copyMainRtToFrameBufferSprite.Draw();

		m_frameBufferRenderTargetView->Release();
		m_frameBufferDepthStencilView->Release();
	}

}

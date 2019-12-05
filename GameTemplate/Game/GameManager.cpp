#include "stdafx.h"
#include "GameManager.h"

//GameManager�N���X�̃C���X�^���X�B
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
	//�����_�����O�^�[�Q�b�g�̐؂�ւ��B
	d3dDeviceContext->OMSetRenderTargets(1, rtTbl, depthStensil);
	if (viewport != nullptr) {
		//�r���[�|�[�g���w�肳��Ă�����A�r���[�|�[�g���ύX����B
		d3dDeviceContext->RSSetViewports(1, viewport);
	}
}
void GameManager::Update()
{
	
	
		////�`��J�n�B
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

	{
		//�����_�����O�^�[�Q�b�g�����C���ɕύX����B
		auto d3dDeviceContext = g_graphicsEngine->GetD3DDeviceContext();
		ChangeRenderTarget(d3dDeviceContext, &m_mainRenderTarget, &m_frameBufferViewports);
		//���C�������_�����O�^�[�Q�b�g���N���A����B
		float clearColor[] = { 0.0f, 0.0f, 0.0f, 1.0f };
		m_mainRenderTarget.ClearRenderTarget(clearColor);


		

		//�o�^����Ă���Q�[���I�u�W�F�N�g�̍X�V�������ĂԁB
		for (auto go : m_goList) {
			go->Update();
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

	

	//g_graphicsEngine->EndRender();

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
}

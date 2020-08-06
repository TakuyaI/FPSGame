#pragma once
#include <time.h>
#include "IGameObject.h"
#include "RenderTarget.h"
#include "Sprite.h"
#include "ShadowMap.h"
class GameManager
{
public:
	/// <summary>
	/// �R���X�g���N�^�B
	/// </summary>
	GameManager();
	/// <summary>
	/// �f�X�g���N�^�B
	/// </summary>
	~GameManager();
	void Init();
	void InitTranslucentBlendState();
	void ChangeRenderTarget(ID3D11DeviceContext* d3dDeviceContext, RenderTarget* renderTarget, D3D11_VIEWPORT* viewport);
	void ChangeRenderTarget(ID3D11DeviceContext* d3dDeviceContext, ID3D11RenderTargetView* renderTarget, ID3D11DepthStencilView* depthStensil, D3D11_VIEWPORT* viewport);
	/// <summary>
	/// �X�V�B
	/// </summary>
	void Update();
	/// <summary>
	void Render();
	void InitEffekseer();
	Effekseer::Manager* GetEffekseerManager()
	{
		return m_effekseerManager;
	}
	ShadowMap* GetShadowMap()
	{
		return &m_shadowMap;
	}

	/// <summary>
	/// �Q�[���I�u�W�F�N�g��ǉ��B
	/// </summary>
	template<class T>
	T* NewGameObject(const int num)
	{
		T* newObj = new T();
		m_goList.push_back(newObj);
		newObj->SetObjectNum(num);
		return newObj;
	}

	template<class T>
	T* FindGameObject(const int num)
	{
		for (auto go : m_goList) {
			if (go->GetObjectNum() == num) {
				T* p = dynamic_cast<T*>(go);
				return p;
			}
		}
	}

	void DeleteGameObject(IGameObject* go)
	{
		//���X�g����T���āA����������폜����B
		for (auto it = m_goList.begin();
			it != m_goList.end();
			it++
			) {
			if ((*it) == go) {
				//�폜�̃��N�G�X�g�𑗂�B
				go->RequestDelete();
				return;
			}
		}
	}
	template<class T>
	void QueryGameObject(const int num, std::function<bool(T* go)> func)
	{
		for (auto go : m_goList) {
			if (go->GetObjectNum() == num) {
				T* p = dynamic_cast<T*>(go);
				if (func(p) == false) {
					//�N�G�����f�B
					return;
				}
			}
		}
	}
	/// <summary>
	/// �����_���Ő��l��Ԃ��B
	/// </summary>
	///<param name="num"> 0����num�Ԗڂ܂ł̐��l���o���B</param>
	/// <returns></returns>
	int Rand(int num) 
	{
		//srand((unsigned int)time(nullptr));
		rand(); rand(); rand(); rand();
		int ran = rand();
		int rand1 = ran % (num + 1);
		return rand1;
	}
	/// <summary>
	/// ���͈͓��̐��l�������_���ŕԂ��B
	/// </summary>
	/// <param name="lowest">�͈͂̍ŏ��l</param>
	/// <param name="highest">�͈͂̍ő�l</param>
	/// <returns></returns>
	float Lerp(float lowest, float highest)
	{
		return lowest + (float)Rand(highest - lowest);
	}
	void SetPlayerPos(CVector3 pos)
	{
		m_playerPos = pos;
	}
	CVector3 GetPlayerPos()
	{
		return m_playerPos;
	}
	void SetPointLightPos(CVector3 pos , int i)
	{
		m_pointLightPos[i] = pos;
	}
	CVector3 GetPointLightPos(int i)
	{
		return m_pointLightPos[i];
	}
	void SetShotFlug(bool flug)
	{
		m_shotFlug = flug;
	}
	bool GetShotFlug()
	{
		return m_shotFlug;
	}
	
private:
	std::list <IGameObject*> m_goList; //�ϒ��z��B

	D3D11_VIEWPORT m_frameBufferViewports;			//�t���[���o�b�t�@�̃r���[�|�[�g�B
	RenderTarget m_mainRenderTarget;   //���C�������_�����O�^�[�Q�b�g�B
	ID3D11RenderTargetView* m_frameBufferRenderTargetView = nullptr;	//�t���[���o�b�t�@�̃����_�����O�^�[�Q�b�g�r���[�B
	ID3D11DepthStencilView* m_frameBufferDepthStencilView = nullptr;	//�t���[���o�b�t�@�̃f�v�X�X�e���V���r���[�B
	Sprite m_copyMainRtToFrameBufferSprite;			//���C�������_�����O�^�[�Q�b�g�ɕ`���ꂽ�G���t���[���o�b�t�@�ɃR�s�[���邽�߂̃X�v���C�g�B
	ID3D11BlendState* m_translucentBlendState = nullptr;	//�����������p�̃u�����h�X�e�[�g�B
	bool m_flug = false;
	ShadowMap m_shadowMap; //�V���h�E�}�b�v�B
	CVector3 m_playerPos = CVector3::Zero(); //�v���C���[�̍��W�B
	Effekseer::Manager*	m_effekseerManager = nullptr;
	EffekseerRenderer::Renderer* m_effekseerRenderer = nullptr;
	CVector3 m_pointLightPos[13]; //�|�C���g���C�g�̍��W�B
	bool m_shotFlug = false; //�e�����������ǂ����B
};
//�O������A�N�Z�X����̂ŁAextern�錾���K�v�B
extern GameManager g_goMgr;


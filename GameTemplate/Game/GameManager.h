#pragma once
#include <time.h>
#include "IGameObject.h"
#include "RenderTarget.h"
#include "Sprite.h"
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

	void ChangeRenderTarget(ID3D11DeviceContext* d3dDeviceContext, RenderTarget* renderTarget, D3D11_VIEWPORT* viewport);
	void ChangeRenderTarget(ID3D11DeviceContext* d3dDeviceContext, ID3D11RenderTargetView* renderTarget, ID3D11DepthStencilView* depthStensil, D3D11_VIEWPORT* viewport);
	/// <summary>
	/// �X�V�B
	/// </summary>
	void Update();
	/// <summary>
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
	/// <summary>
	/// �����_���Ő��l��Ԃ��B
	/// </summary>
	///<param name="num"> 0����num�Ԗڂ܂ł̐��l���o���B</param>
	/// <returns></returns>
	int Rand(int num) 
	{
		//srand((unsigned int)time(nullptr));
		rand(); rand(); rand(); rand();
		int ran = 0;
		if (aa % 4 == 0) {
			ran = rand();
			aa++;
		}
		else if (aa % 4 == 1) {
			ran = rand();
			aa++;
		}
		else if (aa % 4 == 2) {
			ran = rand();
			aa++;
		}
		else if (aa % 4 == 3) {
			ran = rand();
			aa++;
		}
		else {
			ran = rand();
			aa++;
		}

		int rand1 = ran % num;
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
		return lowest + Rand(highest - lowest);
	}
private:
	std::list <IGameObject*> m_goList; //�ϒ��z��B
	D3D11_VIEWPORT m_frameBufferViewports;			//�t���[���o�b�t�@�̃r���[�|�[�g�B
	RenderTarget m_mainRenderTarget;   //���C�������_�����O�^�[�Q�b�g�B
	ID3D11RenderTargetView* m_frameBufferRenderTargetView = nullptr;	//�t���[���o�b�t�@�̃����_�����O�^�[�Q�b�g�r���[�B
	ID3D11DepthStencilView* m_frameBufferDepthStencilView = nullptr;	//�t���[���o�b�t�@�̃f�v�X�X�e���V���r���[�B
	Sprite m_copyMainRtToFrameBufferSprite;			//���C�������_�����O�^�[�Q�b�g�ɕ`���ꂽ�G���t���[���o�b�t�@�ɃR�s�[���邽�߂̃X�v���C�g�B
	bool m_flug = false;
	int aa = 0;
};
//�O������A�N�Z�X����̂ŁAextern�錾���K�v�B
extern GameManager g_goMgr;


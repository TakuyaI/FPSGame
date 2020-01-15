#pragma once
#include <time.h>
#include "IGameObject.h"
#include "RenderTarget.h"
#include "Sprite.h"
class GameManager
{
public:
	/// <summary>
	/// コンストラクタ。
	/// </summary>
	GameManager();
	/// <summary>
	/// デストラクタ。
	/// </summary>
	~GameManager();
	void Init();

	void ChangeRenderTarget(ID3D11DeviceContext* d3dDeviceContext, RenderTarget* renderTarget, D3D11_VIEWPORT* viewport);
	void ChangeRenderTarget(ID3D11DeviceContext* d3dDeviceContext, ID3D11RenderTargetView* renderTarget, ID3D11DepthStencilView* depthStensil, D3D11_VIEWPORT* viewport);
	/// <summary>
	/// 更新。
	/// </summary>
	void Update();
	/// <summary>
	/// <summary>
	/// ゲームオブジェクトを追加。
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
		//リストから探して、見つかったら削除する。
		for (auto it = m_goList.begin();
			it != m_goList.end();
			it++
			) {
			if ((*it) == go) {
				//削除のリクエストを送る。
				go->RequestDelete();
				return;
			}
		}
	}
	/// <summary>
	/// ランダムで数値を出す。
	/// </summary>
	/// 0からnum番目までの数値を出す。<param name="num"></param>
	/// <returns></returns>
	int Rand(int num) 
	{
		srand((unsigned int)time(0));
		rand(); rand(); rand(); rand();

		int rand1 = rand() % num;
		return rand1;
	}
	float Lerp(float lowest, float highest)
	{
		return lowest + Rand(highest - lowest);
	}
private:
	std::list <IGameObject*> m_goList; //可変長配列。
	D3D11_VIEWPORT m_frameBufferViewports;			//フレームバッファのビューポート。
	RenderTarget m_mainRenderTarget;   //メインレンダリングターゲット。
	ID3D11RenderTargetView* m_frameBufferRenderTargetView = nullptr;	//フレームバッファのレンダリングターゲットビュー。
	ID3D11DepthStencilView* m_frameBufferDepthStencilView = nullptr;	//フレームバッファのデプスステンシルビュー。
	Sprite m_copyMainRtToFrameBufferSprite;			//メインレンダリングターゲットに描かれた絵をフレームバッファにコピーするためのスプライト。
	bool m_flug = false;
};
//外部からアクセスするので、extern宣言も必要。
extern GameManager g_goMgr;


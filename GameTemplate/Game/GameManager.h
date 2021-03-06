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
	/// コンストラクタ。
	/// </summary>
	GameManager();
	/// <summary>
	/// デストラクタ。
	/// </summary>
	~GameManager();
	void Init();
	void InitTranslucentBlendState();
	void ChangeRenderTarget(ID3D11DeviceContext* d3dDeviceContext, RenderTarget* renderTarget, D3D11_VIEWPORT* viewport);
	void ChangeRenderTarget(ID3D11DeviceContext* d3dDeviceContext, ID3D11RenderTargetView* renderTarget, ID3D11DepthStencilView* depthStensil, D3D11_VIEWPORT* viewport);
	/// <summary>
	/// 更新。
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
	/// <summary>
	/// ゲームオブジェクトの検索。
	/// </summary>
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
	/// <summary>
	/// ゲームオブジェクトの検索。
	/// </summary>
	template<class T>
	void QueryGameObject(const int num, std::function<bool(T* go)> func)
	{
		for (auto go : m_goList) {
			if (go->GetObjectNum() == num) {
				T* p = dynamic_cast<T*>(go);
				if (func(p) == false) {
					//クエリ中断。
					return;
				}
			}
		}
	}
	/// <summary>
	/// ゲームオブジェクトを削除。
	/// </summary>
	/// <param name="go">ゲームオブジェクト。</param>
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
	/// ランダムで数値を返す。
	/// </summary>
	///<param name="num"> 0からnum番目までの数値を出す。</param>
	/// <returns></returns>
	int Rand(int num) 
	{
		rand(); rand(); rand(); rand();
		int ran = rand();
		int rand1 = ran % (num + 1);
		return rand1;
	}
	/// <summary>
	/// 一定範囲内の数値をランダムで返す。
	/// </summary>
	/// <param name="lowest">範囲の最小値</param>
	/// <param name="highest">範囲の最大値</param>
	/// <returns></returns>
	float Lerp(float lowest, float highest)
	{
		return lowest + (float)Rand(highest - lowest);
	}
	/// <summary>
	/// プレイヤーの座標を設定する。
	/// </summary>
	/// <param name="pos"></param>
	void SetPlayerPos(CVector3 pos)
	{
		m_playerPos = pos;
	}
	/// <summary>
	/// プレイヤーの座標を返す。
	/// </summary>
	/// <returns></returns>
	CVector3 GetPlayerPos()
	{
		return m_playerPos;
	}
	/// <summary>
	/// ポイントライトの座標を設定する。
	/// </summary>
	/// <param name="pos">座標。</param>
	/// <param name="i">配列の番号。</param>
	void SetPointLightPos(CVector3 pos , int i)
	{
		m_pointLightPos[i] = pos;
	}
	/// <summary>
	/// ポイントライトの座標を返す。
	/// </summary>
	/// <param name="i"></param>
	/// <returns></returns>
	CVector3 GetPointLightPos(int i)
	{
		return m_pointLightPos[i];
	}
	/// <summary>
	/// 弾を撃ったかどうかのフラグを設定する。
	/// </summary>
	/// <param name="flug">フラグ。</param>
	void SetShotFlug(bool flug)
	{
		m_shotFlug = flug;
	}
	/// <summary>
	/// 弾を撃ったかどうかのフラグを返す。
	/// </summary>
	/// <returns></returns>
	bool GetShotFlug()
	{
		return m_shotFlug;
	}
	
private:
	std::list <IGameObject*> m_goList;                                  //可変長配列。
	D3D11_VIEWPORT m_frameBufferViewports;	                    		//フレームバッファのビューポート。
	RenderTarget m_mainRenderTarget;                                    //メインレンダリングターゲット。
	ID3D11RenderTargetView* m_frameBufferRenderTargetView = nullptr;	//フレームバッファのレンダリングターゲットビュー。
	ID3D11DepthStencilView* m_frameBufferDepthStencilView = nullptr;	//フレームバッファのデプスステンシルビュー。
	Sprite m_copyMainRtToFrameBufferSprite;			                    //メインレンダリングターゲットに描かれた絵をフレームバッファにコピーするためのスプライト。
	ID3D11BlendState* m_translucentBlendState = nullptr;	            //半透明合成用のブレンドステート。
	bool m_initFlug = false;                                            //Init関数を1回しか通さないためのフラグ。
	ShadowMap m_shadowMap;                                              //シャドウマップ。
	CVector3 m_playerPos = CVector3::Zero();                            //プレイヤーの座標。
	Effekseer::Manager*	m_effekseerManager = nullptr;
	EffekseerRenderer::Renderer* m_effekseerRenderer = nullptr;
	CVector3 m_pointLightPos[13];                                       //ポイントライトの座標。
	bool m_shotFlug = false;                                            //弾を撃ったかどうか。
};
//外部からアクセスするので、extern宣言も必要。
extern GameManager g_goMgr;


#pragma once
class IGameObject
{
public:
	virtual ~IGameObject()
	{
		//これが仮想デストラクタ。
		//これを追加すると派生クラスのデストラクタが呼ばれるよ。
	}
	virtual bool Start() { return true; }
	/// <summary>
	/// 更新関数。
	/// </summary>
	virtual void Update() = 0;
	virtual void SetRegistShadowCaster() {}
	/// <summary>
	/// 描画。
	/// </summary>
	virtual void Render() {}
	virtual void PostRender() {}
	/// <summary>
	/// 削除リクエストを行う。
	/// </summary>
	void RequestDelete()
	{
		isReqDelete = true;
	}

	//削除リクエストを受けているか調べる。
	//trueが返ってきたら、リクエストを受けている。
	bool IsReqDelete()
	{
		return isReqDelete; 
	}

	void SetObjectNum(int objectNum)
	{
		m_objectNum = objectNum;
	}
	int GetObjectNum()
	{
		return m_objectNum;
	}
	void SetStartEndFlug(bool flug)
	{
		m_startEndFlug = flug;
	}
	bool GetmStartEndFlug()
	{
		return m_startEndFlug;
	}
	/// <summary>
	/// 2D描画の優先度。
	/// trueを優先して、falseを後回し。
	/// </summary>
	/// <param name="priority"></param>
	void SetPostRenderPriority(bool priority)
	{
		m_postRenderPriority = priority;
	}
	bool GetPostRenderPriority()
	{
		return m_postRenderPriority;
	}
private:
	bool isReqDelete = false;//削除フラグ。
	int m_objectNum = 0;
	bool m_startEndFlug = false;
	bool m_postRenderPriority = false;// 2D描画の優先度。
protected:

	const enum objectNum {
		background,
		pointlight,
		bullet,
		font,
		enemy,
		dogenemy,
		enemygenerator,
		game,
		gamecamera,
		player,
		gungenerator,
		itemgenerator,
		itemobject,
		title,
		rifle,
		shotgun,
		sniper,
	};
};


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
	virtual void Update() {};
	/// <summary>
	/// シャドウキャスターをセット。
	/// </summary>
	virtual void SetRegistShadowCaster() {}
	/// <summary>
	/// 3描画。
	/// </summary>
	virtual void Render() {}
	/// <summary>
	/// 2D描画。
	/// </summary>
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
	/// <summary>
	/// ゲームオブジェクトの番号を設定する。
	/// </summary>
	/// <param name="objectNum">番号。</param>
	void SetObjectNum(int objectNum)
	{
		m_objectNum = objectNum;
	}
	/// <summary>
	/// ゲームオブジェクトの番号を返す。
	/// </summary>
	/// <returns></returns>
	int GetObjectNum()
	{
		return m_objectNum;
	}
	/// <summary>
	/// Start関数を1回しか通らないようにするためのフラグを設定する。
	/// </summary>
	/// <param name="flug"></param>
	void SetStartEndFlug(bool flug)
	{
		m_startEndFlug = flug;
	}
	/// <summary>
	/// Start関数を1回しか通らないようにするためのフラグを返す。
	/// </summary>
	/// <returns></returns>
	bool GetmStartEndFlug()
	{
		return m_startEndFlug;
	}
	/// <summary>
	/// 2D描画の優先度設定する。
	/// trueを優先して、falseを後回し。
	/// </summary>
	/// <param name="priority">優先度。</param>
	void SetPostRenderPriority(bool priority)
	{
		m_postRenderPriority = priority;
	}
	/// <summary>
	/// 2D描画の優先度返す。
	/// </summary>
	/// <returns></returns>
	bool GetPostRenderPriority()
	{
		return m_postRenderPriority;
	}
private:
	bool isReqDelete = false;           //削除フラグ。
	int m_objectNum = 0;                //ゲームオブジェクトの番号。
	bool m_startEndFlug = false;        //Start関数を1回しか通らないようにするためのフラグ。
	bool m_postRenderPriority = false;  //2D描画の優先度。
protected:
	//ゲームオブジェクトの番号を設定。
	const enum objectNum {
		background,
		pointlight,
		bullet,
		font,
		enemy,
		dogenemy,
		game,
		gamecamera,
		player,
		gungenerator,
		itemgenerator,
		itemobject,
		kaihuku,
		danyaku,
		title,
		rifle,
		shotgun,
		sniper,
	};
};


#pragma once
class IGameObject
{
public:
	virtual ~IGameObject()
	{
		//これが仮想デストラクタ。
		//これを追加すると派生クラスのデストラクタが呼ばれるよ。
	}
	/// <summary>
	/// 更新関数。
	/// </summary>
	virtual void Update() = 0;
	/// <summary>
	/// 描画。
	/// </summary>
	virtual void Render() {}
	virtual void PostRender() {}

	//virtual bool Start() { return true; };
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

private:
	bool isReqDelete = false;//削除フラグ。
	int m_objectNum = 0;
protected:

	const enum objectNum {
		background,
		bullet,
		font,
		enemy,
		enemygenerator,
		game,
		gamecamera,
		gun,
		player,
		gungenerator,
		item,
		title
	};
};


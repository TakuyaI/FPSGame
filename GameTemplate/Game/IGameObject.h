#pragma once
class IGameObject
{
public:
	/// <summary>
	/// 更新関数。
	/// </summary>
	virtual void Update() = 0;
	/// <summary>
	/// 描画。
	/// </summary>
	//virtual void Render() = 0;
	virtual bool Start() { return true; };
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

	void SetA(int aa)
	{
		a = aa;
	}
	int GetA()
	{
		return a;
	}

private:
	bool isReqDelete = false;//削除フラグ。
protected:
	int a = 0;
};


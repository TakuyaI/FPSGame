#pragma once
class IItemObject
{
public:
	/// <summary>
	/// コンストラクタ。
	/// </summary>
	IItemObject();
	/// <summary>
	/// デストラクタ。
	/// </summary>
	~IItemObject();
	/// <summary>
	/// アイテム効果。
	/// </summary>
	virtual void ItemEffects() = 0;
	/// <summary>
	/// アイテムを所持しているかどうかのフラグを設定する。
	/// </summary>
	/// <param name="flug">フラグ</param>
	void SetHaveFlug(bool flug)
	{
		m_haveFlug = flug;
	}
	/// <summary>
	/// アイテムを所持しているかどうかのフラグを返す。
	/// </summary>
	/// <returns></returns>
	bool GetHaveFlug()
	{
		return m_haveFlug;
	}
	/// <summary>
	/// アイテムの所持数を設定する。
	/// </summary>
	/// <param name="haveNum">所持数</param>
	void SetHaveNum(int haveNum)
	{
		m_haveNum = haveNum;
	}
	/// <summary>
	/// アイテムの所持数を返す。
	/// </summary>
	/// <returns></returns>
	int GetHaveNum()
	{
		return m_haveNum;
	}
	/// <summary>
	/// アイテムの番号を設定する。
	/// </summary>
	/// <param name="num">アイテムの番号。何も設定されていないときは、0～29以外の数値を入れておく。</param>
	void SetItemNumber(int num)
	{
		m_itemNumber = num;
	}
	/// <summary>
	/// アイテムの番号を返す。
	/// </summary>
	/// <returns></returns>
	int GetmItemNumber()
	{
		return m_itemNumber;
	}
private:
	bool m_haveFlug = false;   //アイテムを所持しているかどうか。
	int m_haveNum = 0;         //アイテムの所持数。
	int m_itemNumber = 1000;   //アイテムの番号。初期化で0～29以外の数値を入れておく。
};


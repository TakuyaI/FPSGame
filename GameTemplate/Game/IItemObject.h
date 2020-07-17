#pragma once
class IItemObject
{
public:
	IItemObject();
	~IItemObject();
	/// <summary>
	/// アイテム効果。
	/// </summary>
	virtual void ItemEffects() = 0;

	void SetHaveFlug(bool flug)
	{
		m_haveFlug = flug;
	}
	bool GetHaveFlug()
	{
		return m_haveFlug;
	}
	void SetHaveNum(int haveNum)
	{
		m_haveNum = haveNum;
	}
	int GetHaveNum()
	{
		return m_haveNum;
	}
	void SetItemNumber(int num)
	{
		m_itemNumber = num;
	}
	int GetmItemNumber()
	{
		return m_itemNumber;
	}
private:
	bool m_haveFlug = false;
	int m_haveNum = 0; //アイテムの所持数。
	int m_itemNumber = 1000; //アイテムの番号。初期化で0～30以外の数値を入れておく。
};


#pragma once
class IItemObject
{
public:
	IItemObject();
	~IItemObject();
	/// <summary>
	/// �A�C�e�����ʁB
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
	int m_haveNum = 0; //�A�C�e���̏������B
	int m_itemNumber = 1000; //�A�C�e���̔ԍ��B��������0�`30�ȊO�̐��l�����Ă����B
};


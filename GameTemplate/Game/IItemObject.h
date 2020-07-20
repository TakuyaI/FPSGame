#pragma once
class IItemObject
{
public:
	/// <summary>
	/// �R���X�g���N�^�B
	/// </summary>
	IItemObject();
	/// <summary>
	/// �f�X�g���N�^�B
	/// </summary>
	~IItemObject();
	/// <summary>
	/// �A�C�e�����ʁB
	/// </summary>
	virtual void ItemEffects() = 0;
	/// <summary>
	/// �A�C�e�����������Ă��邩�ǂ����̃t���O��ݒ肷��B
	/// </summary>
	/// <param name="flug">�t���O</param>
	void SetHaveFlug(bool flug)
	{
		m_haveFlug = flug;
	}
	/// <summary>
	/// �A�C�e�����������Ă��邩�ǂ����̃t���O��Ԃ��B
	/// </summary>
	/// <returns></returns>
	bool GetHaveFlug()
	{
		return m_haveFlug;
	}
	/// <summary>
	/// �A�C�e���̏�������ݒ肷��B
	/// </summary>
	/// <param name="haveNum">������</param>
	void SetHaveNum(int haveNum)
	{
		m_haveNum = haveNum;
	}
	/// <summary>
	/// �A�C�e���̏�������Ԃ��B
	/// </summary>
	/// <returns></returns>
	int GetHaveNum()
	{
		return m_haveNum;
	}
	/// <summary>
	/// �A�C�e���̔ԍ���ݒ肷��B
	/// </summary>
	/// <param name="num">�A�C�e���̔ԍ��B�����ݒ肳��Ă��Ȃ��Ƃ��́A0�`29�ȊO�̐��l�����Ă����B</param>
	void SetItemNumber(int num)
	{
		m_itemNumber = num;
	}
	/// <summary>
	/// �A�C�e���̔ԍ���Ԃ��B
	/// </summary>
	/// <returns></returns>
	int GetmItemNumber()
	{
		return m_itemNumber;
	}
private:
	bool m_haveFlug = false;   //�A�C�e�����������Ă��邩�ǂ����B
	int m_haveNum = 0;         //�A�C�e���̏������B
	int m_itemNumber = 1000;   //�A�C�e���̔ԍ��B��������0�`29�ȊO�̐��l�����Ă����B
};


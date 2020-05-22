#pragma once
class IGameObject
{
public:
	virtual ~IGameObject()
	{
		//���ꂪ���z�f�X�g���N�^�B
		//�����ǉ�����Ɣh���N���X�̃f�X�g���N�^���Ă΂���B
	}
	virtual bool Start() { return true; }
	/// <summary>
	/// �X�V�֐��B
	/// </summary>
	virtual void Update() = 0;
	/// <summary>
	/// �`��B
	/// </summary>
	virtual void Render() {}
	virtual void PostRender() {}

	//virtual bool Start() { return true; };
	/// <summary>
	/// �폜���N�G�X�g���s���B
	/// </summary>
	void RequestDelete()
	{
		isReqDelete = true;
	}

	//�폜���N�G�X�g���󂯂Ă��邩���ׂ�B
	//true���Ԃ��Ă�����A���N�G�X�g���󂯂Ă���B
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
private:
	bool isReqDelete = false;//�폜�t���O�B
	int m_objectNum = 0;
	bool m_startEndFlug = false;
protected:

	const enum objectNum {
		background,
		bullet,
		font,
		enemy,
		dogenemy,
		enemygenerator,
		game,
		gamecamera,
		player,
		gungenerator,
		item,
		itemgenerator,
		title,
		rifle,
		shotgun,
		sniper,
	};
};


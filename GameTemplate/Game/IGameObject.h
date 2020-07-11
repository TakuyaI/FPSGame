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
	virtual void SetRegistShadowCaster() {}
	/// <summary>
	/// �`��B
	/// </summary>
	virtual void Render() {}
	virtual void PostRender() {}
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
	/// <summary>
	/// 2D�`��̗D��x�B
	/// true��D�悵�āAfalse����񂵁B
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
	bool isReqDelete = false;//�폜�t���O�B
	int m_objectNum = 0;
	bool m_startEndFlug = false;
	bool m_postRenderPriority = false;// 2D�`��̗D��x�B
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


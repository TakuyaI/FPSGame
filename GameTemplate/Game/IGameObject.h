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
	virtual void Update() {};
	/// <summary>
	/// �V���h�E�L���X�^�[���Z�b�g�B
	/// </summary>
	virtual void SetRegistShadowCaster() {}
	/// <summary>
	/// 3�`��B
	/// </summary>
	virtual void Render() {}
	/// <summary>
	/// 2D�`��B
	/// </summary>
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
	/// <summary>
	/// �Q�[���I�u�W�F�N�g�̔ԍ���ݒ肷��B
	/// </summary>
	/// <param name="objectNum">�ԍ��B</param>
	void SetObjectNum(int objectNum)
	{
		m_objectNum = objectNum;
	}
	/// <summary>
	/// �Q�[���I�u�W�F�N�g�̔ԍ���Ԃ��B
	/// </summary>
	/// <returns></returns>
	int GetObjectNum()
	{
		return m_objectNum;
	}
	/// <summary>
	/// Start�֐���1�񂵂��ʂ�Ȃ��悤�ɂ��邽�߂̃t���O��ݒ肷��B
	/// </summary>
	/// <param name="flug"></param>
	void SetStartEndFlug(bool flug)
	{
		m_startEndFlug = flug;
	}
	/// <summary>
	/// Start�֐���1�񂵂��ʂ�Ȃ��悤�ɂ��邽�߂̃t���O��Ԃ��B
	/// </summary>
	/// <returns></returns>
	bool GetmStartEndFlug()
	{
		return m_startEndFlug;
	}
	/// <summary>
	/// 2D�`��̗D��x�ݒ肷��B
	/// true��D�悵�āAfalse����񂵁B
	/// </summary>
	/// <param name="priority">�D��x�B</param>
	void SetPostRenderPriority(bool priority)
	{
		m_postRenderPriority = priority;
	}
	/// <summary>
	/// 2D�`��̗D��x�Ԃ��B
	/// </summary>
	/// <returns></returns>
	bool GetPostRenderPriority()
	{
		return m_postRenderPriority;
	}
private:
	bool isReqDelete = false;           //�폜�t���O�B
	int m_objectNum = 0;                //�Q�[���I�u�W�F�N�g�̔ԍ��B
	bool m_startEndFlug = false;        //Start�֐���1�񂵂��ʂ�Ȃ��悤�ɂ��邽�߂̃t���O�B
	bool m_postRenderPriority = false;  //2D�`��̗D��x�B
protected:
	//�Q�[���I�u�W�F�N�g�̔ԍ���ݒ�B
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


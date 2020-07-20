#pragma once
class PointLightObject : public IGameObject
{
public:
	/// <summary>
	/// �R���X�g���N�^�B
	/// </summary>
	PointLightObject();
	/// <summary>
	/// �f�X�g���N�^�B
	/// </summary>
	~PointLightObject();
	/// <summary>
	/// �X�V�֐��B
	/// </summary>
	void Update();
	/// <summary>
	/// ���W��ݒ肷��B
	/// </summary>
	/// <param name="pos">���W�B</param>
	void SetPosition(CVector3 pos)
	{
		m_position = pos;
	}
	/// <summary>
	/// ���W��Ԃ��B
	/// </summary>
	/// <returns></returns>
	CVector3 GetPosition()
	{
		return m_position;
	}
private:
	SkinModel m_model;                       //�X�L�����f���B
	CVector3 m_position = CVector3::Zero();  //���W�B
};


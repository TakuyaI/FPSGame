#pragma once
#include "IGameObject.h"
#include "physics\PhysicsStaticObject.h"
#include "PhysicsGhostObject.h"
class BackGround : public IGameObject
{
public:
	/// <summary>
	/// �R���X�g���N�^�B
	/// </summary>
	BackGround();
	/// <summary>
	/// �f�X�g���N�^�B
	/// </summary>
	~BackGround();
	/// <summary>
	/// �X�^�[�g�֐��B
	/// </summary>
	/// <returns></returns>
	bool Start();
	/// <summary>
	/// �X�V�֐��B
	/// </summary>
	void Update();
	/// <summary>
	/// 3D�`��B
	/// </summary>
	void Render();
	/// <summary>
	/// ���W��ݒ肷��B
	/// </summary>
	/// <param name="position">���W�B</param>
	void SetPosition(CVector3 position)
	{
		m_position = position;
	}
	/// <summary>
	/// ���W��Ԃ��B
	/// </summary>
	/// <returns></returns>
	CVector3 GetPosition()
	{
		return m_position;
	}
	/// <summary>
	/// ��]��ݒ肷��B
	/// </summary>
	/// <param name="rotation">��]�B</param>
	void SetRotation(CQuaternion rotation)
	{
		m_rotation = rotation;
	}
	/// <summary>
	/// ��]��Ԃ��B
	/// </summary>
	/// <returns></returns>
	CQuaternion GetRotation() 
	{
		return m_rotation;
	}
private:
	//���������X�e�[�W�̔ԍ��B
	enum EStageParts {
		eStageParts_3_1,
		eStageParts_3_2,
		eStageParts_3_3,
		eStageParts_3_4,
		eStateParts_Num,
	};
	SkinModel m_model[eStateParts_Num];                         //�X�L�����f���B
	CVector3 m_position = CVector3::Zero();                     //���W�B
	CQuaternion m_rotation = CQuaternion::Identity();           //��]�B
	PhysicsStaticObject m_physicsStaticObject[eStateParts_Num]; //�ÓI�����I�u�W�F�N�g�B
	PhysicsGhostObject m_GhostObj[eStateParts_Num];             //�S�[�X�g�I�u�W�F�N�g�B
};


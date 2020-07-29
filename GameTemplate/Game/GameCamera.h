#pragma once
class Player;
#include "IGameObject.h"
#include "Player.h"
#include "GunGenerator.h"
class GameCamera : public IGameObject
{
public:
	/// <summary>
	/// �R���X�g���N�^�B
	/// </summary>
	GameCamera();
	/// <summary>
	/// �f�X�g���N�^�B
	/// </summary>
	~GameCamera();
	/// <summary>
	/// ���R�C���B
	/// </summary>
	void Recoil();
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
	/// �����_�̍��W���擾�B
	/// </summary>
	CVector3 GetTarget()
	{
		return m_target;
	}
	/// <summary>
	/// ���_�̍��W���擾�B
	/// </summary>
	CVector3 GetPosition()
	{
		return m_position;
	}
	CVector3 GetToTargetPos()
	{
		return m_toTargetPos;
	}
	CVector3 GetToTarget()
	{
		return m_toTarget;
	}
	const CQuaternion GetRotation() const
	{
		return m_rotation;
	}
	void SetAngle2(float angle2)
	{
		m_angle2 = angle2;
	}
	float GetAngle2()
	{
		return m_angle2;
	}
	void SetRotSpeed(float speed)
	{
		m_rotSpeed = speed;
	}
	float GetRotSpeed()
	{
		return m_rotSpeed;
	}
	void SetGameCameraViewAngle(float viewAngle)
	{
		m_viewAngle = viewAngle;
	}
	float GetGameCameraViewAngle()
	{
		return m_viewAngle;
	}
	void SetWidthUpperLimit(float widthUpperLimit)
	{
		m_widthUpperLimit = widthUpperLimit;
	}
	float GetWidthUpperLimit()
	{
		return m_widthUpperLimit;
	}
	void SetRecoilRightAndLeft(float recoilRightAndLeft)
	{
		m_recoilRightAndLeft = recoilRightAndLeft;
	}
	float GetRecoilRightAndLeft()
	{
		return m_recoilRightAndLeft;
	}
private:
	Player* m_player;
	GunGenerator* m_gunGen;
	CVector3 m_toTargetPos = { 0.0f, 0.0f, 1000.0f };
	CVector3 m_position = CVector3::Zero();     //���_�B
	CVector3 m_target = CVector3::Zero();       //�����_�B
	CVector3 m_toTarget = CVector3::Zero();
	float m_angle = 0.0f;                             //��]�B
	float m_angle2 = 0.0f;
	CQuaternion m_rotation;
	float m_rotSpeed = 5.0f; //�J��������]����X�s�[�h�B
	CVector3 m_cameraOffset = { 0.0f, 150.0f, 0.0f };
	float m_viewAngle = 60.0f;//��p�B
	float m_shotCount = 0.0f;//�e�����������ɃJ�E���g����B
	float m_width = 0.0f;//���R�C���̉����B
	float m_widthUpperLimit = 20.0f; //���R�C���̉����̏���B
	float m_recoilRightAndLeft = 0.3f;//���R�C���̍��E�̈ړ��ʁB
};


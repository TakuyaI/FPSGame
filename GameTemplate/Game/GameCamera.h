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
	/// �����_�̍��W��Ԃ��B
	/// </summary>
	CVector3 GetTarget()
	{
		return m_target;
	}
	/// <summary>
	/// ���_�̍��W��Ԃ��B
	/// </summary>
	CVector3 GetPosition()
	{
		return m_position;
	}
	/// <summary>
	/// �v���C���[�����_�Ƃ����^�[�Q�b�g�̍��W��Ԃ��B
	/// </summary>
	/// <returns></returns>
	CVector3 GetToTargetPos()
	{
		return m_toTargetPos;
	}
	/// <summary>
	/// �v���C���[����^�[�Q�b�g�Ɍ������x�N�g���𐳋K���������̂�Ԃ��B
	/// </summary>
	/// <returns></returns>
	CVector3 GetToTarget()
	{
		return m_toTarget;
	}
	/// <summary>
	/// ��]��Ԃ��B
	/// </summary>
	/// <returns></returns>
	const CQuaternion GetRotation()
	{
		return m_rotation;
	}
	/// <summary>
	/// �J��������]����X�s�[�h��ݒ肷��B
	/// </summary>
	/// <param name="speed"></param>
	void SetRotSpeed(float speed)
	{
		m_rotSpeed = speed;
	}
	/// <summary>
	/// �J��������]����X�s�[�h��Ԃ��B
	/// </summary>
	/// <returns></returns>
	float GetRotSpeed()
	{
		return m_rotSpeed;
	}
	/// <summary>
	/// ��p��ݒ肷��B
	/// </summary>
	/// <param name="viewAngle"></param>
	void SetGameCameraViewAngle(float viewAngle)
	{
		m_viewAngle = viewAngle;
	}
	/// <summary>
	/// ��p��Ԃ��B
	/// </summary>
	/// <returns></returns>
	float GetGameCameraViewAngle()
	{
		return m_viewAngle;
	}
	/// <summary>
	/// ���R�C���̍��E�̈ړ��ʂ�Ԃ��B
	/// </summary>
	/// <returns></returns>
	float GetRecoilRightAndLeft()
	{
		return m_recoilRightAndLeft;
	}
private:
	Player* m_player;                                   //�v���C���[�̃C���X�^���X�B
	GunGenerator* m_gunGen;                             //GunGenerator�̃C���X�^���X�B
	CVector3 m_toTargetPos = { 0.0f, 0.0f, 1000.0f };   //�v���C���[�����_�Ƃ����^�[�Q�b�g�̍��W
	CVector3 m_position = CVector3::Zero();             //���_�B
	CVector3 m_target = CVector3::Zero();               //�����_�B
	CVector3 m_toTarget = CVector3::Zero();             //�v���C���[����^�[�Q�b�g�Ɍ������x�N�g���𐳋K���������́B
	CVector3 m_cameraOffset = { 0.0f, 150.0f, 0.0f };   //�v���C���[�̍��W�����Ƃ����Ƃ��́A�J�����̃��[�J�����W�B
	CQuaternion m_rotation;                             //��]�B
	float m_angle = 0.0f;                               //���̉�]�p�x�B
	float m_angle2 = 0.0f;                              //�c�̉�]�p�x�B
	float m_rotSpeed = 5.0f;                            //�J��������]����X�s�[�h�B
	float m_viewAngle = 60.0f;                          //��p�B
	float m_shotCount = 0.0f;                           //�e�����������ɃJ�E���g����B
	float m_width = 0.0f;                               //���R�C���̉����B
	float m_widthUpperLimit = 20.0f;                    //���R�C���̉����̏���B
	float m_recoilRightAndLeft = 0.3f;                  //���R�C���̍��E�̈ړ��ʁB
};


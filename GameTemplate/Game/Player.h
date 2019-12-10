#pragma once
#include "character/CharacterController.h"
#include "IGameObject.h"
#include "GameCamera.h"
class GameCamera;
class Player:public IGameObject
{
public:
	Player();
	~Player();
	void Update();
	void Draw();

	/// <summary>
	/// ���W��ݒ�B
	/// </summary>
	void SetPosition(CVector3 pos)
	{
		m_position = pos;
	}
	/// <summary>
	/// ���W���擾�B
	/// </summary>
	CVector3 GetPosition()
	{
		return m_position;
	}
	bool GetJumpFlug()
	{
		return m_jumpFlag;
	}
	void SetGameCamera(GameCamera* gc)
	{
		m_gameCamera = gc;
	}
private:
	GameCamera* m_gameCamera;

	CVector3 m_position = CVector3::Zero(); //���W�B
	SkinModel m_model;						//�X�L�����f���B
	float ySpeed = 0.0f;                    //�d�́B
	CVector3 m_moveSpeed = CVector3::Zero();//
	CharacterController m_charaCon;         //�L�����N�^�[�R���g���[���[�B
	bool m_jumpFlag = false;                     //�W�����v�t���O�B
	float m_playerSpeed = 20.0f;            //Player�̃X�s�[�h�B
};
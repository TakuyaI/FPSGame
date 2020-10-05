#pragma once
class Enemy;
class Game;
#include "IGameObject.h"
#include "PhysicsGhostObject.h"
#include "Rifle.h"
#include "Shotgun.h"
#include "Sniper.h"
#include "BackGround.h"
class Bullet : public IGameObject
{
public:
	/// <summary>
	/// �R���X�g���N�^�B
	/// </summary>
	Bullet();
	/// <summary>
	/// �f�X�g���N�^�B
	/// </summary>
	~Bullet();
	/// <summary>
	/// �S�[�X�g�������B
	/// </summary>
	void InitGhost();
	/// <summary>
	/// �X�^�[�g�֐��B
	/// </summary>
	/// <returns></returns>
	bool Start();
	/// <summary>
	/// �X�V�֐��B
	/// </summary>
	void Update();
	//3D�`��B
	void Render();
	/// <summary>
	/// ���W��ݒ肷��B
	/// </summary>
	/// <param name="pos"></param>
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
	/// <summary>
	/// �ړ����x��ݒ肷��B
	/// </summary>
	/// <param name="moveSpeed"></param>
	void SetMoveSpeed(CVector3 moveSpeed)
	{
		m_moveSpeed = moveSpeed;
	}
	/// <summary>
	/// �L�����R����Ԃ��B
	/// </summary>
	/// <returns></returns>
	CharacterController* GetCharaCon()
	{
		return &m_charaCon;
	}
private:
	/// <summary>
	/// �e�ۂƓG�̏Փ˔���
	/// </summary>
	void CollisionBulletToEnemy();
	void CollisionBulletToDogEnemy();
private:
	GunGenerator* m_gunGen;                            //GunGenerator�̃C���X�^���X�B
	Game* m_game;                                      //Game�̃C���X�^���X�B
	Rifle* m_rifle;                                    //Rifle�̃C���X�^���X�B
	Shotgun* m_shotgun;                                //Shotgun�̃C���X�^���X�B
	Sniper* m_sniper;                                  //Sniper�̃C���X�^���X�B
	SkinModel m_model;                                 //�X�L�����f���B
	CVector3 m_position = CVector3::Zero();            //���W�B
	CVector3 m_moveSpeed = CVector3::Zero();           //�ړ����x�B
	int m_lifeTimer = 0;                               //�e�̐������Ԃ̃^�C�}�[�B
	const int m_lifeTime = 10;                         //�e�̐������ԁB 
	int m_bulletPower = 0;                             //�e�̍U���́B
	CQuaternion m_rotation = CQuaternion::Identity();  //��]�B
	PhysicsGhostObject m_GhostObject;                  //�S�[�X�g�B
	CharacterController m_charaCon;                    //�L�����R���B
	CVector3 m_hitJudgmentRange = CVector3::Zero();    //�e�̓����蔻��͈̔́B
	const float m_controllerRadius = 5.0f;             //�L�����R���̔��a�B
	const float m_controllerHeight = 5.0f;            //�L�����R���̍����B
};


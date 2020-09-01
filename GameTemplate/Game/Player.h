#pragma once
class Sprite;
class Enemy;
#include "IGameObject.h"
#include "GameCamera.h"
#include "Sprite.h"
#include "FontRender.h"
#include "Enemy.h"
class GameCamera;
class Player:public IGameObject
{
public:
	/// <summary>
	/// �R���X�g���N�^�B
	/// </summary>
	Player();
	/// <summary>
	/// �f�X�g���N�^�B
	/// </summary>
	~Player();
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
	/// �V���h�E�L���X�^�[�֐��B
	/// </summary>
	void SetRegistShadowCaster();
	/// <summary>
	/// 3D�`��B
	/// </summary>
	void Render();
	/// <summary>
	/// 2D�`��B
	/// </summary>
	void PostRender();
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
	/// <summary>
	/// �G��˂���΂������ǂ����̃t���O��ݒ肷��B
	/// </summary>
	/// <param name="flug">�t���O�B</param>
	void SetPushAwayFlug(bool flug)
	{
		m_pushAwayFlug = flug;
	}
	/// <summary>
	/// �G��˂���΂������ǂ����̃t���O��Ԃ��B
	/// </summary>
	/// <returns></returns>
	bool GetPushAwayFlug()
	{
		return m_pushAwayFlug;
	}
	/// <summary>
	/// �v���C���[���󂯂�_���[�W�ʂ�ݒ肷��B
	/// </summary>
	/// <param name="d">�_���[�W�ʁB</param>
	void SetDamage(float d)
	{
		m_damage = d;
	}
	/// <summary>
	/// �v���C���[���󂯂�_���[�W�ʂ�Ԃ��B
	/// </summary>
	/// <returns></returns>
	float GetDamage()
	{
		return m_damage;
	}
	/// <summary>
	/// HP�̕ω��ʂ�ݒ肷��B
	/// </summary>
	/// <param name="hpChanges">HP�̕ω��ʁB</param>
	void SetHpChanges(float hpChanges)
	{
		m_hpChanges = hpChanges;
	}
	/// <summary>
	/// �_���[�W���󂯂����ǂ����̃t���O��ݒ肷��B
	/// </summary>
	/// <param name="damageFlug">�t���O�B</param>
	void SetDamageFlug(bool damageFlug) 
	{
		m_damageFlug = damageFlug;
	}
	/// <summary>
	/// �_���[�W���󂯂����ǂ����̃t���O��Ԃ��B
	/// </summary>
	/// <returns></returns>
	bool GetDamageFlug()
	{
		return m_damageFlug;
	}
	/// <summary>
	/// �v���C���[�����S�������ǂ����̃t���O��Ԃ��B
	/// </summary>
	/// <returns></returns>
	bool GetDeathFlug()
	{
		return m_deathFlug;
	}
	/// <summary>
	/// Player���~�܂��Ă��邩�ǂ�����ݒ肷��B
	/// </summary>
	/// <param name="flug">�t���O�B</param>
	void SetStopFlug(bool flug)
	{
		m_stopFlug = flug;
	}
	/// <summary>
	/// Player���~�܂��Ă��邩�ǂ�����Ԃ��B
	/// </summary>
	/// <returns></returns>
	bool GetStopFlug()
	{
		return m_stopFlug;
	}
	/// <summary>
	/// �v���C���[��HP��Ԃ��B
	/// </summary>
	/// <returns></returns>
	float GetPlayerHp()
	{
		return m_playerHp;
	}
private:
	SkinModel m_model;					                 	//�X�L�����f���B
	GameCamera* m_gameCamera;                               //GameCamera�̃C���X�^���X�B
	Enemy* m_enemy;                                         //Enemy�̃C���X�^���X�B
	CVector3 m_position = CVector3::Zero();                 //���W�B
	CQuaternion m_rotation = CQuaternion::Identity();       //��]�B
	CVector3 m_moveSpeed = CVector3::Zero();                //���[�u�X�s�[�h�B
	CharacterController m_charaCon;                         //�L�����N�^�[�R���g���[���[�B
	float ySpeed = 0.0f;                                    //�d�́B
	float m_playerSpeed = 20.0f;                            //Player�̃X�s�[�h�B
	float m_playerHp = 100.0f;                              //�v���C���[��HP�B
	float m_pushAwayNum = 0;                                //���l�ɂȂ�����A�G��˂���΂��B
	float m_hpChanges = 0;                                  //HP�̕ω��ʁB
	float m_damage = 0.0f;                                  //�v���C���[���󂯂�_���[�W�ʁB
	Sprite m_damageSprite;                                  //�_���[�W���󂯂��Ƃ��ɕ\�������X�v���C�g�B
	Sprite m_greenSprite;                                   //HP�o�[�̃X�v���C�g�B
	Sprite m_hpBlackSprite;                                 //HP�o�[�̌��̃o�[�̃X�v���C�g�B
	CVector3 m_greenScale = CVector3::One();                //HP�o�[�̃X�v���C�g�̑傫���B
	CVector3 m_blackScale = CVector3::One();                //HP�o�[�̌��̃o�[�̃X�v���C�g�̑傫���B
	CVector3 m_gaugePos = { -500.0f, -300.0f, 0.0f };       //HP�o�[�̃X�v���C�g�̍��W�B
	CVector3 m_blackGaugePos = { -500.0f, -301.0f, 0.0f };  //HP�o�[�̌��̃o�[�̃X�v���C�g���W�B
	bool m_deathFlug = false;                               //�v���C���[�����S�������ǂ����B
	bool m_stopFlug = false;                                //Player���~�܂��Ă��邩�ǂ����B
	bool m_damageFlug = false;                              //�_���[�W���󂯂����ǂ����B
	bool m_moveStickFlug = false;                           //�X�e�B�b�N���������������ǂ����B�X�e�B�b�N�����E�ɓ�������true�A�㉺�ɓ�������false�ɂȂ�B
	bool m_pushAwayFlug = false;                            //�G��˂���΂������ǂ����B
};
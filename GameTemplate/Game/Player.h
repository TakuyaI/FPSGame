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
	Player();
	~Player();
	bool Start();
	void Update();
	void SetRegistShadowCaster();
	void Render();
	void PostRender();
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
	void SetRotation(CQuaternion rotation)
	{
		m_rotation = rotation;
	}
	CQuaternion GetRotation()
	{
		return m_rotation;
	}
	void SetMoveSpeed(CVector3 movespeed)
	{
		m_moveSpeed = movespeed;
	}
	CVector3 GetMoveSpeed()
	{
		return m_moveSpeed;
	}
	void SetPushAwayFlug(bool t)
	{
		m_pushAwayFlug = t;
	}
	bool GetPushAwayFlug()
	{
		return m_pushAwayFlug;
	}
	void SetDamage(float d)
	{
		m_damage = d;
	}
	float GetDamage()
	{
		return m_damage;
	}
	void SetHpChanges(float hpChanges)
	{
		m_hpChanges = hpChanges;
	}
	void SetDamageFlug(bool damageFlug) 
	{
		m_damageFlug = damageFlug;
	}
	bool GetDamageFlug()
	{
		return m_damageFlug;
	}
	bool GetDeathFlug()
	{
		return m_deathFlug;
	}
	void SetStopFlug(bool flug)
	{
		m_stopFlug = flug;
	}
	bool GetStopFlug()
	{
		return m_stopFlug;
	}
	void SetPlayerSpeed(float speed)
	{
		m_playerSpeed = speed;
	}
	float GetPlayerSpeed()
	{
		return m_playerSpeed;
	}
	float GetPlayerHp()
	{
		return m_playerHp;
	}
private:
	GameCamera* m_gameCamera;
	Enemy* m_enemy;

	SkinModel m_model;						//�X�L�����f���B
	CVector3 m_position = CVector3::Zero(); //���W�B
	CQuaternion m_rotation = CQuaternion::Identity(); //��]�B
	float ySpeed = 0.0f;                    //�d�́B
	CVector3 m_moveSpeed = CVector3::Zero();//���[�u�X�s�[�h�B
	CharacterController m_charaCon;         //�L�����N�^�[�R���g���[���[�B
	float m_playerSpeed = 20.0f;            //Player�̃X�s�[�h�B
	float m_playerHp = 100.0f; //�v���C���[��HP�B
	float m_pushAwayNum = 0; 
	float m_hpChanges = 0;//HP�̕ω��ʁB
	float m_damage = 0.0f; //�v���C���[���󂯂�_���[�W�ʁB
	Sprite m_damageSprite;
	Sprite m_greenSprite;
	Sprite m_hpBlackSprite;
	CVector3 m_greenScale = CVector3::One();
	CVector3 m_blackScale = CVector3::One();
	CVector3 m_gaugePos = { -500.0f, -300.0f, 0.0f };
	CVector3 m_blackGaugePos = { -500.0f, -301.0f, 0.0f };
	
	bool m_deathFlug = false; //�v���C���[�����S�������ǂ����B
	bool m_stopFlug = false; //Player���~�܂��Ă��邩�ǂ����B
	bool m_damageFlug = false; //�_���[�W���󂯂����ǂ����B
	bool m_moveStickFlug = false;
	bool m_pushAwayFlug = false; //�G��˂���΂������ǂ����B
};
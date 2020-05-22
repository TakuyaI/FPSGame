#pragma once
class EnemyGenerator;
#include "IGameObject.h"
#include "Item.h"
#include "IEnemyObject.h"
#include "graphics\animation\AnimationClip.h"
class IEnemyObject : public IGameObject
{
public:
	IEnemyObject();
	~IEnemyObject();
	void Loitering();
	void Tracking();
	void Attack();

	void EnemyUpdate(CVector3* position, CVector3* initPos, CQuaternion* rotation, CharacterController& charaCon);
	void Update();


	CVector3 GetPosition()
	{
		return m_position;
	}
	void SetInitPos(CVector3 initpos)
	{
		m_initPos = initpos;
	}
	CVector3 GetInitPos()
	{
		return m_initPos;
	}
	void SetRotation(CQuaternion rotation)
	{
		m_rotation = rotation;
	}
	CQuaternion GetRoation()
	{
		return m_rotation;
	}
	bool GetAttackFlug()
	{
		return m_attackFlug;
	}
	void SetEnemyHp(int enemyhp)
	{
		m_enemyHp = enemyhp;
	}
	int GetEnemyHp()
	{
		return m_enemyHp;
	}
	CharacterController* CharaCon()
	{
		return &m_charaCon;
	}
	float GetEnemyAttackPow()
	{
		return m_enemyAttackPow;
	}
	float GetDamage()
	{
		return m_damage;
	}
	void SetDamageFlug(bool damageFlug)
	{
		m_damageFlug = damageFlug;
	}
	bool GetDamageFlug()
	{
		return m_damageFlug;
	}
	void SetReceiveDamageFlug(bool receiveDamageFlug)
	{
		m_receiveDamageFlug = receiveDamageFlug;
	}
	void SetDeathFlug(bool deathflug)
	{
		m_death = deathflug;
	}
protected:
	const enum anim {
		enAnimationCrip_stay,   //�ҋ@�B
		enAnimationCrip_run,    //����B
		enAnimationCrip_attack, //�U���B
		enAnimationCrip_hirumu, //���ށB
		enAnimationCrip_death,  //���S�B
		enAnimationCrip_Num     //�A�j���[�V�����N���b�v�̐��B
	};
	int m_animationFlug = 0;
	const float ENEMY_CONTROLLER_RADIUS = 30.0f;
	const float ENEMY_CONTROLLER_HEIGHT = 100.0f;
private:
		Player* m_player;                                 //Player�̃C���X�^���X�B
	EnemyGenerator* m_enemyGen;                       //EnemyGenerator�̃C���X�^���X�B
	Item* m_item;                                     //Item�̃C���X�^���X�B

	CVector3 m_moveSpeed = CVector3::Zero();          //���[�u�X�s�[�h�B
	CVector3 m_position = CVector3::Zero();           //���W�B
	CVector3 m_initPos = CVector3::Zero();            //�������W�B
	CVector3 m_toPlayerVec = CVector3::Zero();        //Enemy����Player�֌������x�N�g���B
	CQuaternion m_rotation = CQuaternion::Identity(); //��]�B
	CharacterController m_charaCon;                   //�L�����N�^�[�R���g���[���[�B
	int m_state = 0;                                  //Enemy�̏�ԁB
	bool m_attackFlug = false;                        //�U���t���O�B
	float m_pushAwaySpeed = 100.0f;                   //�˂��������X�y�[�h�B
	bool m_endPushAwayflug = false;                   //�˂������I�������ǂ����B
	int m_enemyHp = 50;                               //Enemy��HP�B
	float m_playerHp = 100.0f;
	int m_AttackTimer = 0;
	float m_enemyAttackPow = 10.0f;
	float m_damage = 0.0f;
	bool m_damageFlug = false; //�_���[�W��^�������ǂ����B
	bool m_receiveDamageFlug = false; //�_���[�W���󂯂����ǂ����B
	int m_scaredTimer = 0; //���ގ��ԁB
	bool m_death = false; //���S�t���O�B
	int m_deathAnimtime = 0; //���S�A�j���[�V�����^�C���B
	CVector3 m_toTargetVec = CVector3::Zero();
	CVector3 m_targetPos = CVector3::Zero();

	
	
	AnimationClip m_animationClip[enAnimationCrip_Num]; //�A�j���[�V�����N���b�v�B
	Animation m_animation;                    //�A�j���[�V�����B
	Effekseer::Effect* m_sampleEffect = nullptr;
	Effekseer::Handle m_playEffectHandle = -1;
	CVector3 m_effectPos = CVector3::Zero();

	CSoundSource m_bgm;
	CSoundSource m_walk;
	CSoundSource m_damageS;

};


#pragma once
class EnemyGenerator;
class Player;
class Game;
#include "IGameObject.h"
#include "IEnemyObject.h"
#include "graphics\animation\AnimationClip.h"
class IEnemyObject : public IGameObject
{
public:
	IEnemyObject();
	~IEnemyObject();
	/// <summary>
	/// �؍݁B
	/// </summary>
	/// <param name="position">���W�B</param>
	/// <param name="initPos">�������W�B</param>
	void Saty(CVector3* position, CVector3* initPos);
	/// <summary>
	///�ǐՁB
	/// </summary>
	void Tracking();
	/// <summary>
	/// �U���B
	/// </summary>
	void Attack();
	/// <summary>
	/// �˂���΂����B
	/// </summary>
	void PushAway();
	/// <summary>
	/// ���S�B
	/// </summary>
	/// <param name="pos">���W�B</param>
	/// <param name="time">���S���ԁB</param>
	void Death(CVector3* pos, int* time);
	/// <summary>
	/// �_���[�W���󂯂�B
	/// </summary>
	/// <param name="position">���W�B</param>
	void ReceiveDamage(CVector3* position);
	void EnemyUpdate(CVector3* position, CVector3* initPos, CQuaternion* rotation, CharacterController& charaCon, int* deathTime);
	void Update();

	void SetInitPos(CVector3 initpos)
	{
		m_initPos = initpos;
	}
	CVector3 GetInitPos()
	{
		return m_initPos;
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
	float GetEnemyAttackPow()
	{
		return m_enemyAttackPow;
	}
	float GetDamage()
	{
		return m_damage;
	}
	void SetReceiveDamageFlug(bool receiveDamageFlug)
	{
		m_receiveDamageFlug = receiveDamageFlug;
	}
	void SetDeathFlug(bool deathflug)
	{
		m_death = deathflug;
	}
	void SetEffectVec(CVector3 vec)
	{
		m_effectVec = vec;
	}
	void SetBulletPos(CVector3 pos)
	{
		m_bulletPos = pos;
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
	//const float ENEMY_CONTROLLER_RADIUS = 30.0f;
	const float ENEMY_CONTROLLER_RADIUS = 100.0f;
	const float ENEMY_CONTROLLER_HEIGHT = 200.0f;
private:
		Player* m_player;                                 //Player�̃C���X�^���X�B
	EnemyGenerator* m_enemyGen;                       //EnemyGenerator�̃C���X�^���X�B
	Game* m_game;

	CVector3 m_moveSpeed = CVector3::Zero();          //���[�u�X�s�[�h�B
	CVector3 m_initPos = CVector3::Zero();            //�������W�B
	CVector3 m_toPlayerVec = CVector3::Zero();        //Enemy����Player�֌������x�N�g���B
	int m_state = 0;                                  //Enemy�̏�ԁB
	bool m_attackFlug = false;                        //�U���t���O�B
	float m_pushAwaySpeed = 100.0f;                   //�˂��������X�s�[�h�B
	bool m_endPushAwayflug = false;                   //�˂������I�������ǂ����B
	int m_enemyHp = 50;                               //Enemy��HP�B
	float m_playerHp = 100.0f;
	int m_AttackTimer = 0;
	float m_enemyAttackPow = 10.0f;
	float m_damage = 0.0f;
	//bool m_damageFlug = false; //�_���[�W��^�������ǂ����B
	bool m_receiveDamageFlug = false; //�_���[�W���󂯂����ǂ����B
	int m_scaredTimer = 0; //���ގ��ԁB
	bool m_death = false; //���S�t���O�B
	int m_deathAnimtime = 0; //���S�A�j���[�V�����^�C���B
	CVector3 m_toTargetVec = CVector3::Zero();
	CVector3 m_targetPos = CVector3::Zero();
	CVector3 m_bulletPos = CVector3::Zero();
	CVector3 m_effectVec = CVector3::Zero();
	Effekseer::Effect* m_sampleEffect = nullptr;
	Effekseer::Handle m_playEffectHandle = -1;

	CSoundSource m_bgm;
	CSoundSource m_walk;
	CSoundSource m_damageS;
	CVector3 m_lockTargetPos = CVector3::Zero();
	bool m_lockTargetPosFlug = false; //�^�[�Q�b�g�̍��W���Œ肷��t���O�B

};


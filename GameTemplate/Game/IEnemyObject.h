#pragma once
class Player;
class Game;
class ItemObject;
#include "IGameObject.h"
#include "IEnemyObject.h"
#include "graphics\animation\AnimationClip.h"
class IEnemyObject : public IGameObject
{
public:
	/// <summary>
	/// �R���X�g���N�^�B
	/// </summary>
	IEnemyObject();
	/// <summary>
	/// �f�X�g���N�^�B
	/// </summary>
	~IEnemyObject();
	/// <summary>
	///�ǐՁB
	/// </summary>
	void Tracking();
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
	/// <summary>
	/// �G�̍X�V�B
	/// </summary>
	/// <param name="position">���W�B</param>
	/// <param name="initPos">�������W</param>
	/// <param name="rotation">��]�B</param>
	/// <param name="charaCon">�L�����R���B</param>
	/// <param name="deathTime">���S�A�j���[�V�����̎��ԁB</param>
	/// <param name="AttackPow">�U���́B</param>
	/// <param name="speed">���x�B</param>
	void EnemyUpdate(CVector3* position, CVector3* initPos, CQuaternion* rotation, CharacterController& charaCon, int* deathTime, float* AttackPow, float* speed);
	/// <summary>
	/// �G��HP��ݒ肷��B
	/// </summary>
	/// <param name="enemyhp"></param>
	void SetEnemyHp(int enemyhp)
	{
		m_enemyHp = enemyhp;
	}
	/// <summary>
	/// �G��HP��Ԃ��B
	/// </summary>
	/// <returns></returns>
	int GetEnemyHp()
	{
		return m_enemyHp;
	}
	/// <summary>
	/// �_���[�W���󂯂����ǂ����̃t���O��ݒ肷��
	/// </summary>
	/// <param name="receiveDamageFlug"></param>
	void SetReceiveDamageFlug(bool receiveDamageFlug)
	{
		m_receiveDamageFlug = receiveDamageFlug;
	}
	/// <summary>
	/// ���S�t���O��ݒ肷��B
	/// </summary>
	/// <param name="deathflug"></param>
	void SetDeathFlug(bool deathflug)
	{
		m_death = deathflug;
	}
	/// <summary>
	/// �G�t�F�N�g�̃x�N�g����ݒ�B
	/// </summary>
	/// <param name="vec">�G�t�F�N�g�̃x�N�g���B</param>
	void SetEffectVec(CVector3 vec)
	{
		m_effectVec = vec;
	}
	/// <summary>
	/// �e�̍��W��ݒ�B
	/// </summary>
	/// <param name="pos">���W�B</param>
	void SetBulletPos(CVector3 pos)
	{
		m_bulletPos = pos;
	}
private:
	/// <summary>
	/// �ҋ@���B
	/// </summary>
	/// <param name="position">���W�B</param>
	/// <param name="initPos">�������W�B</param>
	virtual void Saty(CVector3* position, CVector3* initPos){}
	/// <summary>
	/// �U���B
	/// </summary>
	/// /// <param name="AttackPow">�U���́B</param>
	virtual void Attack(float AttackPow){}
protected:
	Player * m_player;                              //Player�̃C���X�^���X�B
	CVector3 m_moveSpeed = CVector3::Zero();       //���[�u�X�s�[�h�B
	CVector3 m_targetPos = CVector3::Zero();       //�^�[�Q�b�g�̍��W�B
	CVector3 m_toPlayerVec = CVector3::Zero();     //Enemy����Player�֌������x�N�g���B
	CSoundSource m_giveDamageS;                    //�G���_���[�W��^�����Ƃ��̉��B
	const enum anim {
		enAnimationCrip_stay,   //�ҋ@�B
		enAnimationCrip_run,    //����B
		enAnimationCrip_attack, //�U���B
		enAnimationCrip_hirumu, //���ށB
		enAnimationCrip_death,  //���S�B
		enAnimationCrip_Num     //�A�j���[�V�����N���b�v�̐��B
	};
	int m_animationFlug = 0;                       //�A�j���[�V���������߂�t���O�B
	int m_AttackTimer = 0;                         //�U���^�C�}�[�B
	float m_damage = 0.0f;                         //�_���[�W�B
	float ENEMY_CONTROLLER_RADIUS = 0.0f;   //�L�����R���̔��a�B
	float ENEMY_CONTROLLER_HEIGHT = 0.0f;  //�L�����R���̍����B
private:
	Game* m_game;                                  //Game�̃C���X�^���X�B
	ItemObject* m_itemObj;                         //ItemObject�̃C���X�^���X�B
	CVector3 m_toTargetVec = CVector3::Zero();     //�G����^�[�Q�b�g�Ɍ������x�N�g���B
	CVector3 m_bulletPos = CVector3::Zero();       //�e�̍��W�B
	CVector3 m_effectVec = CVector3::Zero();       //�G�t�F�N�g�̃x�N�g���B
	CVector3 m_lockTargetPos = CVector3::Zero();   //�^�[�Q�b�g�̍��W�B
	CSoundSource m_receiveDamageS;                 //�G���_���[�W���󂯂��Ƃ��̉��B
	CSoundSource m_walkS;                          //�G�������Ă���Ƃ��̉��B
    //Effekseer�}�l�[�W���Ǘ��B
	Effekseer::Effect* m_sampleEffect = nullptr;
	Effekseer::Handle m_playEffectHandle = -1;
	int m_state = 0;                               //Enemy�̏�ԁB
	int m_enemyHp = 50;                            //Enemy��HP�B
	int m_scaredTimer = 0;                         //���ގ��ԁB
	int m_deathAnimtimer = 0;                      //���S�A�j���[�V�����^�C���B
	float m_pushAwaySpeed = 100.0f;                //�˂��������X�s�[�h�B
	bool m_endPushAwayflug = false;                //�˂������I�������ǂ����B
	bool m_death = false;                          //���S�t���O�B
	bool m_receiveDamageFlug = false;              //�_���[�W���󂯂����ǂ����B
	bool m_lockTargetPosFlug = false;              //�^�[�Q�b�g�̍��W���Œ肷��t���O�B
};


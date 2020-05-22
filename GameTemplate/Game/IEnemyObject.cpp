#include "stdafx.h"
//#include "IEnemyObject.h"
#include "GameManager.h"
#include "EnemyGenerator.h"
#include "Player.h"
const int ENEMY_LOITERING = 0; //�p�j��
const int ENEMY_TRACKING = 1;  //�ǐՒ�
const int ENEMY_ATTACK = 2;    //�U��
const float ENEMY_CONTROLLER_RADIUS = 30.0f;
const float ENEMY_CONTROLLER_HEIGHT = 100.0f;
IEnemyObject::IEnemyObject()
{
	m_player = g_goMgr.FindGameObject<Player>(player);
	m_enemyGen = g_goMgr.FindGameObject<EnemyGenerator>(enemygenerator);

	//m_initPos = m_enemyGen->GetEnemyInitPos();
	//m_position = m_enemyGen->GetEnemyInitPos();
	//m_initPos = { 0.0f, 100.0f, 0.0f };
	/*m_charaCon.Init(
		ENEMY_CONTROLLER_RADIUS,
		ENEMY_CONTROLLER_HEIGHT,
		m_initPos
	);*/
	
	

	//�T���v���̃G�t�F�N�g�����[�h����B
	m_sampleEffect = Effekseer::Effect::Create(g_goMgr.GetEffekseerManager(), (const EFK_CHAR*)L"Assets/effect/test02.efk");
	//�T�E���h�����[�h�B
	m_bgm.Init(L"Assets/sound/bomb1.wav");
	m_walk.Init(L"Assets/sound/walkS.wav");
	m_damageS.Init(L"Assets/sound/damageS.wav");
}


IEnemyObject::~IEnemyObject()
{
}
void IEnemyObject::Loitering()
{
	//����A�j���[�V�����B
	m_animationFlug = enAnimationCrip_run;
	m_targetPos = m_initPos;
	CVector3 v = m_initPos - m_position;
	float fds = v.Length();
	if (fds <= 15.0f) {
		m_moveSpeed = CVector3::Zero();
		m_position = m_initPos;
		m_animationFlug = enAnimationCrip_stay;
	}
}
void IEnemyObject::Tracking()
{
	//����A�j���[�V�����B
	m_animationFlug = enAnimationCrip_run;
	m_targetPos = m_player->GetPosition();
}
void IEnemyObject::Attack()
{
	m_targetPos = m_player->GetPosition();
	m_enemyGen->SetAttackFlug(true);
	//�U���A�j���[�V�����B
	m_animationFlug = enAnimationCrip_attack;

	m_AttackTimer++;
	if (m_AttackTimer >= 30) {
		m_damage = m_enemyAttackPow / m_playerHp;
		m_player->SetDamage(m_damage);
		m_damageS.Stop();
		m_damageS.Play(false);

		m_damageFlug = true;
		m_player->SetDamageFlug(m_damageFlug);
		m_damageFlug = false;
		m_AttackTimer = 0;
	}

	if (m_player->GetPushAwayFlug() != false) {
		CVector3 toEenmyVec = m_toPlayerVec * -1.0f;
		toEenmyVec.Normalize();
		m_moveSpeed = toEenmyVec * m_pushAwaySpeed;
		m_pushAwaySpeed -= 10.0f;
		if (m_pushAwaySpeed <= 0.0f) {
			//Enemy���˂������I�����B
			m_pushAwaySpeed = 100.0f;
			m_player->SetPushAwayFlug(false);
			m_endPushAwayflug = false;
			m_enemyGen->SetAttackFlug(false);
		}
	}
}
void IEnemyObject::Update()//m_position, m_rotation, m_animationFlug
{

}
void IEnemyObject::EnemyUpdate(CVector3* position, CVector3* initPos, CQuaternion* roation, CharacterController& charaCon)
{
	//Enemy����Player�֌������x�N�g���B
	m_toPlayerVec = m_player->GetPosition() - *position;

	m_toTargetVec = m_targetPos - *position;
	m_toTargetVec.y = 0.0f;
	m_toTargetVec.Normalize();

	CVector3 v = m_toPlayerVec;
	v.Normalize();
	float d = m_toTargetVec.Dot(v);

	float angle = acos(d);
	if (m_toPlayerVec.Length() <= 750.0f) {
		//�v���C���[�Ƃ̋�����750�ȓ��ɂȂ����B
		if (m_toPlayerVec.Length() <= 70.0f) {
			//�v���C���[�Ƃ̋�����70�ȓ��ɂȂ����B
			//�U��������B
			m_state = ENEMY_ATTACK;
			m_endPushAwayflug = true;
		}
		else {
			//�ǐՂ�����B
			m_state = ENEMY_TRACKING;
		}
	}
	else {
		//�p�j����B
		m_state = ENEMY_LOITERING;
	}
	if (m_player->GetPushAwayFlug() != false &&
		m_endPushAwayflug != false) {
		//Enemy��˂��������B
		m_state = ENEMY_ATTACK;
	}

	m_moveSpeed = m_toTargetVec * 10.0f;
	float rot = atan2(m_toTargetVec.x, m_toTargetVec.z);
	roation->SetRotation(CVector3::AxisY(), rot);
	roation->Multiply(m_targetPos);


	if (m_state == ENEMY_LOITERING) {
		//Loitering();
		//����A�j���[�V�����B
		m_animationFlug = enAnimationCrip_run;
		m_targetPos = *initPos;
		CVector3 v = *initPos - *position;
		float fds = v.Length();
		if (fds <= 15.0f) {
			m_moveSpeed = CVector3::Zero();
			*position = *initPos;
			m_animationFlug = enAnimationCrip_stay;
		}
	}
	else if (m_state == ENEMY_TRACKING) {
		//Tracking();
		//����A�j���[�V�����B
		m_animationFlug = enAnimationCrip_run;
		m_targetPos = m_player->GetPosition();
	}
	else if (m_state == ENEMY_ATTACK) {
		//Attack();
		m_targetPos = m_player->GetPosition();
		m_enemyGen->SetAttackFlug(true);
		//�U���A�j���[�V�����B
		m_animationFlug = enAnimationCrip_attack;

		m_AttackTimer++;
		if (m_AttackTimer >= 30) {
			m_damage = m_enemyAttackPow / m_playerHp;
			m_player->SetDamage(m_damage);
			m_damageS.Stop();
			m_damageS.Play(false);

			m_damageFlug = true;
			m_player->SetDamageFlug(m_damageFlug);
			m_damageFlug = false;
			m_AttackTimer = 0;
		}

		if (m_player->GetPushAwayFlug() != false) {
			CVector3 toEenmyVec = m_toPlayerVec * -1.0f;
			toEenmyVec.Normalize();
			m_moveSpeed = toEenmyVec * m_pushAwaySpeed;
			m_pushAwaySpeed -= 10.0f;
			if (m_pushAwaySpeed <= 0.0f) {
				//Enemy���˂������I�����B
				m_pushAwaySpeed = 100.0f;
				m_player->SetPushAwayFlug(false);
				m_endPushAwayflug = false;
				m_enemyGen->SetAttackFlug(false);
			}
		}
	}

	if (position->y <= 0.0f) {
		m_moveSpeed.y = 0.0f;
	}
	if (m_receiveDamageFlug != false) {
		//�_���[�W���󂯂���A��莞�ԋ��ށB
		m_receiveDamageFlug = false;
		m_animationFlug = enAnimationCrip_hirumu;
		m_bgm.Stop();
		m_bgm.Play(false);
		//�Đ����̃G�t�F�N�g���~�߂�B
		g_goMgr.GetEffekseerManager()->StopEffect(m_playEffectHandle);
		//�Đ��B
		m_effectPos = *position;
		m_effectPos.y += 100.0f;
		m_playEffectHandle = g_goMgr.GetEffekseerManager()->Play(m_sampleEffect, m_effectPos.x, m_effectPos.y, m_effectPos.z);
		m_moveSpeed = CVector3::Zero();
	}

	if (m_death != false) {
		//���S�B
		m_enemyGen->SetAttackFlug(false);
		m_moveSpeed = CVector3::Zero();
		m_deathAnimtime++;
		m_animationFlug = enAnimationCrip_death;
		if (m_deathAnimtime >= 60) {
			m_item = g_goMgr.NewGameObject<Item>(item);
			position->y += 50.0f;
			m_item->SetPosition(*position);
			g_goMgr.DeleteGameObject(this);
		}
	}
	

	if (m_animationFlug == enAnimationCrip_run) {
		m_walk.Play(false);
	}
	else {
		m_walk.Stop();
	}
	m_moveSpeed.y -= 10.0f;
	*position = charaCon.Execute(1.0f, m_moveSpeed);
}
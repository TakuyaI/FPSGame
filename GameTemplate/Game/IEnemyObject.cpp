#include "stdafx.h"
#include "EnemyGenerator.h"
#include "Game.h"
#include "ItemObject.h"
const int ENEMY_STAY = 0; //�؍ݒ�
const int ENEMY_TRACKING = 1;  //�ǐՒ�
const int ENEMY_ATTACK = 2;    //�U��
const int ENEMY_PUSH_AWAY = 3; //�˂���΂��ꂽ�B
const int ENEMY_DEATH = 4; //���S�B
const float ENEMY_CONTROLLER_RADIUS = 30.0f;
const float ENEMY_CONTROLLER_HEIGHT = 100.0f;
const float TRACKING_DISTANCE = 750.0f; //�ǐՂ��Ă��鋗���B
const float ATTACK_DISTANCE = 150.0f;  //�U�����Ă��鋗���B
IEnemyObject::IEnemyObject()
{
	m_player = g_goMgr.FindGameObject<Player>(player);
	//�T���v���̃G�t�F�N�g�����[�h����B
	m_sampleEffect = Effekseer::Effect::Create(g_goMgr.GetEffekseerManager(), (const EFK_CHAR*)L"Assets/effect/test03.efk");
	//�T�E���h�����[�h�B
	m_bgm.Init(L"Assets/sound/bomb1.wav");
	m_walk.Init(L"Assets/sound/walkS.wav");
	m_damageS.Init(L"Assets/sound/damageS.wav");
}


IEnemyObject::~IEnemyObject()
{
}
void IEnemyObject::ReceiveDamage(CVector3* position)
{
	//�_���[�W���󂯂���A��莞�ԋ��ށB
	m_receiveDamageFlug = false;
	m_animationFlug = enAnimationCrip_hirumu;
	m_bgm.Stop();
	m_bgm.Play(false);
	//�Đ����̃G�t�F�N�g���~�߂�B
	auto effMgr = g_goMgr.GetEffekseerManager();
	//effMgr->StopEffect(m_playEffectHandle);
	//�Đ��B
	CVector3 effectPos = *position;
	effectPos.y = m_bulletPos.y;
	m_effectVec.Normalize();
	effectPos += m_effectVec;
	m_playEffectHandle = effMgr->Play(
		m_sampleEffect,
		0.0f,
		0.0f,
		0.0f
	);
	//�J�����̉�]�s������߂�B
	CMatrix mCameraRot;
	//�J�����s��̋t�s��̓J�����̃��[���h�s��B
	mCameraRot.Inverse(g_camera3D.GetViewMatrix());
	//
	mCameraRot.m[3][0] = effectPos.x;
	mCameraRot.m[3][1] = effectPos.y;
	mCameraRot.m[3][2] = effectPos.z;

	Effekseer::Matrix43 effMat;
	for (int x = 0; x < 4; x++) {
		for (int y = 0; y < 3; y++) {
			effMat.Value[x][y] = mCameraRot.m[x][y];
		}
	}

	effMgr->SetBaseMatrix(m_playEffectHandle, effMat);
	effMgr->SetScale(m_playEffectHandle, 2.0f, 2.0f, 2.0f);
	m_moveSpeed = CVector3::Zero();
}
//void IEnemyObject::Saty(CVector3* position, CVector3* initPos)
//{
//	//����A�j���[�V�����B
//	m_animationFlug = enAnimationCrip_run;
//	m_targetPos = *initPos;
//	CVector3 v = *initPos - *position;
//	float fds = v.Length();
//	if (fds <= 15.0f) {
//		m_moveSpeed = CVector3::Zero();
//		*position = *initPos;
//		m_animationFlug = enAnimationCrip_stay;
//	}
//}
void IEnemyObject::Tracking()
{
	//����A�j���[�V�����B
	m_animationFlug = enAnimationCrip_run;
	m_targetPos = m_player->GetPosition();
}
//void IEnemyObject::Attack(float AttackPow)
//{
//	m_targetPos = m_player->GetPosition();
//	m_player->SetStopFlug(true);
//	//�U���A�j���[�V�����B
//	m_animationFlug = enAnimationCrip_attack;
//
//	m_AttackTimer++;
//	if (m_AttackTimer >= 30) {
//		m_player->SetDamageFlug(true);
//		m_damage = AttackPow / m_player->GetPlayerHp();
//		m_player->SetDamage(m_damage);
//		m_damageS.Stop();
//		m_damageS.Play(false);
//		m_AttackTimer = 0;
//	}
//}
void IEnemyObject::PushAway()
{
	//�v���C���[����G�Ɍ������ĐL�т�x�N�g�������߂�B
		CVector3 toEenmyVec = m_toPlayerVec * -1.0f;
		toEenmyVec.Normalize();
		//m_moveSpeed�ɁA���K������m_toPlayerVec�~�˂��������X�s�[�h������B
		m_moveSpeed = toEenmyVec * m_pushAwaySpeed;
		//�˂��������X�s�[�h�����X�Ɍ��������Ă����B
		m_pushAwaySpeed -= 10.0f;
		if (m_pushAwaySpeed <= 0.0f) {
			//Enemy���˂������I�����B
			//m_pushAwaySpeed�����Z�b�g�B
			m_pushAwaySpeed = 100.0f;
			m_player->SetPushAwayFlug(false);
			m_endPushAwayflug = false;
		}
}
void IEnemyObject::Death(CVector3* pos, int* time)
{
	m_enemyGen = g_goMgr.FindGameObject<EnemyGenerator>(enemygenerator);
	//m_enemyGen->SetAttackFlug(false);
	m_moveSpeed = CVector3::Zero();
	m_targetPos = m_lockTargetPos;
	m_deathAnimtime++;
	m_animationFlug = enAnimationCrip_death;
	if (m_deathAnimtime >= *time) {
		pos->y += 50.0f;
		m_game = g_goMgr.FindGameObject<Game>(game);
		int num = m_game->GetKnockDownEnemyNum();
		m_game->SetKnockDownEnemyNum(--num);

		m_itemObj = g_goMgr.NewGameObject<ItemObject>(itemobject);
		CVector3 Ipos = *pos;
		Ipos.y = 100.0f;
		m_itemObj->SetPosition(Ipos);
		g_goMgr.DeleteGameObject(this);
	}
}
void IEnemyObject::Update()
{
}
void IEnemyObject::EnemyUpdate(CVector3* position, CVector3* initPos, CQuaternion* rotation, CharacterController& charaCon, int* deathTime, float* AttackPow)
{
	m_player = g_goMgr.FindGameObject<Player>(player);
	//Enemy����Player�֌������x�N�g���B
	m_toPlayerVec = m_player->GetPosition() - *position;

	if (m_toPlayerVec.Length() <= TRACKING_DISTANCE) {
		//�v���C���[�Ƃ̋�����750�ȓ��ɂȂ����B
		if (m_toPlayerVec.Length() <= ATTACK_DISTANCE) {
			//�v���C���[�Ƃ̋�����70�ȓ��ɂȂ����B
			//�U��������B
			m_state = ENEMY_ATTACK;
			if (m_player->GetPushAwayFlug() != false) {
				m_endPushAwayflug = true;
			}
		}
		else {
			//�ǐՂ�����B
			m_state = ENEMY_TRACKING;
		}
	}
	else {
		//���܂�B
		m_state = ENEMY_STAY;
	}
	if (m_endPushAwayflug != false) {
		//Enemy��˂��������B
		m_state = ENEMY_PUSH_AWAY;
	}
	if (m_death != false) {
		m_state = ENEMY_DEATH;
		if (m_lockTargetPosFlug != true) {
			//�^�[�Q�b�g�̍��W���Œ肷��B
			m_lockTargetPos = m_targetPos;
			m_lockTargetPosFlug = false;
		}
	}

	m_toTargetVec = m_targetPos - *position;
	m_toTargetVec.y = 0.0f;
	m_toTargetVec.Normalize();
	m_moveSpeed = m_toTargetVec * 10.0f;
	float rot = atan2(m_toTargetVec.x, m_toTargetVec.z);
	rotation->SetRotation(CVector3::AxisY(), rot);
	rotation->Multiply(m_targetPos);
	if (position->y <= 0.0f) {
		m_moveSpeed.y = 0.0f;
	}
	if (m_receiveDamageFlug != false) {
		//�_���[�W���󂯂�B
		ReceiveDamage(position);
	}

	if (m_state == ENEMY_STAY) {
		//�؍݁B
		Saty(position, initPos);
	}
	else if (m_state == ENEMY_TRACKING) {
		//�ǐՁB
		Tracking();
	}
	else if (m_state == ENEMY_ATTACK) {
		//�U���B
		Attack(*AttackPow);
	}
	else if (m_state == ENEMY_PUSH_AWAY) {
		//�˂���΂��ꂽ�B
		PushAway();
	}
	else if (m_state == ENEMY_DEATH){
		//���S�B
		Death(position, deathTime);
	}
	
	if (m_animationFlug == enAnimationCrip_run) {
		m_walk.Play(false);
		CVector3 toPlV = m_toPlayerVec;
		//�ǐՂ��J�n���鋗����10�Ƃ����Ƃ��A�ǐՂ��Ă��鍡�̋��������߂�B
		//�܂��A���߂��l��10�Ŋ���B�i1�ȉ��̒l�ɂ��邽�߁j
		float len = ((10 * toPlV.Length()) / TRACKING_DISTANCE) / 10.0f;
		float volnme = 1.0f - len;
		m_walk.SetVolume(powf(volnme, 1.5f));
	}
	else {
		m_walk.Stop();
	}
	m_moveSpeed.y -= 10.0f;
	*position = charaCon.Execute(1.0f,0, m_moveSpeed);
}
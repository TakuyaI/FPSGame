#include "stdafx.h"
#include "Game.h"
#include "ItemObject.h"
const int ENEMY_STAY = 0; //�ҋ@��
const int ENEMY_TRACKING = 1;  //�ǐՒ�
const int ENEMY_ATTACK = 2;    //�U��
const int ENEMY_PUSH_AWAY = 3; //�˂���΂��ꂽ�B
const int ENEMY_DEATH = 4; //���S�B
const float TRACKING_DISTANCE = 750.0f; //�ǐՂ��Ă��鋗���B
const float ATTACK_DISTANCE = 150.0f;  //�U�����Ă��鋗���B
IEnemyObject::IEnemyObject()
{
	//�T���v���̃G�t�F�N�g�����[�h����B
	m_sampleEffect = Effekseer::Effect::Create(
		g_goMgr.GetEffekseerManager(),
		(const EFK_CHAR*)L"Assets/effect/test03.efk"
	);
	//�T�E���h�����[�h�B
	m_receiveDamageS.Init(L"Assets/sound/bomb1.wav");
	m_walkS.Init(L"Assets/sound/walkS.wav");
	m_giveDamageS.Init(L"Assets/sound/damageS.wav");
	//�v���C���[�̃C���X�^���X��T���B
	m_player = g_goMgr.FindGameObject<Player>(player);
}


IEnemyObject::~IEnemyObject()
{
}
void IEnemyObject::ReceiveDamage(CVector3* position)
{
	//�_���[�W���󂯂���A��莞�ԋ��ށB
	m_receiveDamageFlug = false;
	m_animationFlug = enAnimationCrip_hirumu;
	m_receiveDamageS.Stop();
	m_receiveDamageS.Play(false);
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
void IEnemyObject::Tracking()
{
	//����A�j���[�V�����B
	m_animationFlug = enAnimationCrip_run;
	//�^�[�Q�b�g���v���C���[�ɂ���B
	m_targetPos = m_player->GetPosition();
}
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
	//�ړ����Ȃ��悤�ɂ���B
	m_moveSpeed = CVector3::Zero();
	//�^�[�Q�b�g�͎��S���钼�O�ɌŒ肷��B
	m_targetPos = m_lockTargetPos;
	//�^�C�}�[�����Z�B
	m_deathAnimtimer++;
	//���S�A�j���[�V�����B
	m_animationFlug = enAnimationCrip_death;
	if (m_deathAnimtimer >= *time) {
		//�^�C�}�[����莞�ԂɂȂ����B
		//Game�̃C���X�^���X��T���B
		m_game = g_goMgr.FindGameObject<Game>(game);
		//�|���G�̎c��̐������炷�B
		int num = m_game->GetKnockDownEnemyNum();
		m_game->SetKnockDownEnemyNum(--num);
		//�A�C�e�����o��������B�B
		m_itemObj = g_goMgr.NewGameObject<ItemObject>(itemobject);
		//�A�C�e���̍��W��ݒ肷��B
		CVector3 Ipos = *pos;
		//Y�����ɏ����v���X���āA�n�ʂɖ��܂�Ȃ��悤�ɂ���B
		Ipos.y = 100.0f;
		m_itemObj->SetPosition(Ipos);
		//�G�̃C���X�^���X���폜����B
		g_goMgr.DeleteGameObject(this);
	}
}

void IEnemyObject::EnemyUpdate(CVector3* position, CVector3* initPos, CQuaternion* rotation, CharacterController& charaCon, int* deathTime, float* AttackPow, float* speed)
{
	//Enemy����Player�֌������x�N�g���B
	m_toPlayerVec = m_player->GetPosition() - *position;
	float len = m_toPlayerVec.Length();
	if (len <= TRACKING_DISTANCE) {
		//�v���C���[�Ƃ̋�����750�ȓ��ɂȂ����B
		if (m_toPlayerVec.Length() <= ATTACK_DISTANCE) {
			//�v���C���[�Ƃ̋�����70�ȓ��ɂȂ����B
			//�U��������B
			m_state = ENEMY_ATTACK;
			if (m_player->GetPushAwayFlug() != false) {
				//�v���C���[�ɓ˂���΂��ꂽ�B
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
	//�G�̍��W����^�[�Q�b�g�Ɍ������ĐL�т�x�N�g�������߂�B
	m_toTargetVec = m_targetPos - *position;
	//Y�̗v�f��0�ɂ���B
	m_toTargetVec.y = 0.0f;
	//���K���B
	m_toTargetVec.Normalize();
	//���[�u�X�s�[�h��ݒ肷��B
	m_moveSpeed = m_toTargetVec * *speed;
	//�G�̌���������ݒ肷��B
	float rot = atan2(m_toTargetVec.x, m_toTargetVec.z);
	rotation->SetRotation(CVector3::AxisY(), rot);
	rotation->Multiply(m_targetPos);
	
	if (m_receiveDamageFlug != false) {
		//�_���[�W���󂯂�B
		ReceiveDamage(position);
	}
	if (m_state == ENEMY_STAY) {
		//�ҋ@�B
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
		m_walkS.Play(false);
		CVector3 toPlV = m_toPlayerVec;
		//�ǐՂ��J�n���鋗����10�Ƃ����Ƃ��A�ǐՂ��Ă��鍡�̋��������߂�B
		//�܂��A���߂��l��10�Ŋ���B�i1�ȉ��̒l�ɂ��邽�߁j
		float len = ((10 * toPlV.Length()) / TRACKING_DISTANCE) / 10.0f;
		float volnme = 1.0f - len;
		m_walkS.SetVolume(powf(volnme, 1.5f));
	}
	else {
		//�����~�߂�B
		m_walkS.Stop();
	}
	//�d�͂��󂯂�B
	m_moveSpeed.y -= 10.0f;
	//�G�̍��W��ݒ�B
	*position = charaCon.Execute(1.0f,0, m_moveSpeed);
}
#include "stdafx.h"
#include "DogEnemy.h"
#include "Player.h"

DogEnemy::DogEnemy()
{
	//���f���̏������B
	m_model.Init(L"Assets/modelData/dogEnemy.cmo");
	//�A�j���[�V�����N���b�v�̃��[�h�B
	m_animationClip[enAnimationCrip_stay].Load(L"Assets/animData/stay_dog.tka");
	m_animationClip[enAnimationCrip_run].Load(L"Assets/animData/run_dog.tka");
	m_animationClip[enAnimationCrip_attack].Load(L"Assets/animData/ata_dog.tka");
	m_animationClip[enAnimationCrip_hirumu].Load(L"Assets/animData/hirumu_dog.tka");
	m_animationClip[enAnimationCrip_death].Load(L"Assets/animData/death_dog.tka");
	//���[�v�t���O��ݒ�B
	m_animationClip[enAnimationCrip_stay].SetLoopFlag(true);
	m_animationClip[enAnimationCrip_run].SetLoopFlag(true);
	m_animationClip[enAnimationCrip_attack].SetLoopFlag(true);
	m_animationClip[enAnimationCrip_hirumu].SetLoopFlag(true);
	m_animationClip[enAnimationCrip_death].SetLoopFlag(true);
	//�A�j���[�V�����̏������B
	m_animation.Init(m_model, m_animationClip, enAnimationCrip_Num);
}


DogEnemy::~DogEnemy()
{
}
bool DogEnemy::Start()
{
	//�������W��ݒ�B
	m_initPos = m_position;
	//�L�����R���̏������B
	m_charaCon.Init(
		ENEMY_CONTROLLER_RADIUS,
		ENEMY_CONTROLLER_HEIGHT,
		m_position
	);
	return true;
}
void DogEnemy::Update()
{
	//�G���X�V�B
	EnemyUpdate(
		&m_position,
		&m_initPos,
		&m_rotation,
		m_charaCon,
		&m_deathAnimTime,
		&m_attackPow,
		&m_speed
	);
	//�A�j���[�V�������Đ��B
	m_animation.Play(m_animationFlug);
	//�A�j���[�V�������X�V�B
	m_animation.Update(1.0f / 30.0f);
	//���f�����X�V�B
	m_model.UpdateWorldMatrix(m_position, m_rotation, CVector3::One() * 2.0f);
}

void DogEnemy::SetRegistShadowCaster()
{
	//�V���h�E�L���X�^�[�ɃZ�b�g�B
	g_goMgr.GetShadowMap()->RegistShadowCaster(&m_model);
}
void DogEnemy::Render()
{
	//�`��B
	m_model.Draw(
		enRenderMode_Normal,
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}
void DogEnemy::Saty(CVector3* position, CVector3* initPos)
{
	//����A�j���[�V�����B
	m_animationFlug = enAnimationCrip_stay;
	if (m_toPlayerVec.Length() <= m_lockOnRange) {
		//�v���C���[�Ƃ̋�����1500�ȓ��ɂȂ�����A
		//�v���C���[�̕��������B
		m_targetPos = m_player->GetPosition();
	}
	else {
		m_targetPos = *initPos;
	}
	//���݂̍��W���珉�����W�Ɍ������ĐL�т�x�N�g�����v�Z�B
	CVector3 toInitPosV = *initPos - *position;
	if (toInitPosV.Length() <= m_initPosRange) {
		//toInitPosV.Length()��15�ȉ��̏ꍇ�A
		//�������Ƃ߂āA���W���������W�ɑ������B
		m_moveSpeed = CVector3::Zero();
		*position = *initPos;
		//�ҋ@�A�j���[�V�����B
		m_animationFlug = enAnimationCrip_stay;
	}
}
void DogEnemy::Attack(float AttackPow)
{
	//�v���C���[�������Ȃ��Ȃ�悤�ɁA�t���O�𑗂�B
	m_player->SetStopFlug(true);
	//�v���C���[���^�[�Q�b�g�ɂ���B
	m_targetPos = m_player->GetPosition();
	//�U���A�j���[�V�����B
	m_animationFlug = enAnimationCrip_attack;
	//���t���[���^�C�}�[�����Z���Ă����B
	m_AttackTimer++;
	if (m_AttackTimer >= m_AttackTime) {
		//�^�C�}�[��20�ɂȂ����B
		//�v���C���[�Ƀ_���[�W��^�����t���O�𑗂�B
		m_player->SetDamageFlug(true);
		//�v���C���[���󂯂�_���[�W�𑗂�B
		//m_damage��1��100�Ƃ����Ƃ��̒l�𑗂�B
		m_damage = AttackPow / m_player->GetPlayerHp();
		m_player->SetDamage(m_damage);
		//�_���[�W�T�E���h�B
		m_giveDamageS.Stop();
		m_giveDamageS.Play(false);
		//�^�C�}�[�����Z�b�g�B
		m_AttackTimer = 0;
	}
}
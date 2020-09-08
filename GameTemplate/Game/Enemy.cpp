#include "stdafx.h"
#include "Enemy.h"
#include "Player.h"

Enemy::Enemy()
{
	//���f���̏������B
	m_model.Init(L"Assets/modelData/enemy.cmo");
	//�A�j���[�V�����N���b�v�̃��[�h�B
	m_animationClip[enAnimationCrip_stay].Load(L"Assets/animData/stay.tka");
	m_animationClip[enAnimationCrip_run].Load(L"Assets/animData/run.tka");
	m_animationClip[enAnimationCrip_attack].Load(L"Assets/animData/ata.tka");
	m_animationClip[enAnimationCrip_hirumu].Load(L"Assets/animData/hirumu.tka");
	m_animationClip[enAnimationCrip_death].Load(L"Assets/animData/death.tka");
	//���[�v�t���O��ݒ�B
	m_animationClip[enAnimationCrip_stay].SetLoopFlag(true);
	m_animationClip[enAnimationCrip_run].SetLoopFlag(true);
	m_animationClip[enAnimationCrip_attack].SetLoopFlag(true);
	m_animationClip[enAnimationCrip_hirumu].SetLoopFlag(true);
	m_animationClip[enAnimationCrip_death].SetLoopFlag(true);
	//�A�j���[�V�����̏������B
	m_animation.Init(m_model, m_animationClip, enAnimationCrip_Num);
}

Enemy::~Enemy()
{
}
bool Enemy::Start()
{
	//�������W��ݒ�B
	m_initPos = m_position;
	//�L�����R���̏������B
	m_charaCon.Init(
		m_controllerRadius,
		m_controllerHeight,
		m_position
	);
	return true;
}
void Enemy::Update()
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
	m_model.UpdateWorldMatrix(m_position, m_rotation, CVector3::One() * 1.5f);
}
void Enemy::SetRegistShadowCaster()
{
	//�V���h�E�L���X�^�[�ɃZ�b�g�B
	g_goMgr.GetShadowMap()->RegistShadowCaster(&m_model);
}
void Enemy::Render()
{
	//�`��B
	m_model.Draw(
		enRenderMode_Normal,
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}
void Enemy::Saty(CVector3* position, CVector3* initPos)
{
	//����A�j���[�V�����B
	m_animationFlug = enAnimationCrip_stay;
	m_targetPos = *initPos;
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
void Enemy::Attack(float AttackPow)
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
		//�^�C�}�[��30�ɂȂ����B
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
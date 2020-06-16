#include "stdafx.h"
#include "Enemy.h"
//#include "GameManager.h"

Enemy::Enemy()
{
	
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
	m_initPos = m_position;
	m_charaCon.Init(
		ENEMY_CONTROLLER_RADIUS,
		ENEMY_CONTROLLER_HEIGHT,
		m_position
	);
	return true;
}
void Enemy::Update()
{
	EnemyUpdate(
		&m_position,
		&m_initPos,
		&m_rotation,
		m_charaCon
	);
	//�A�j���[�V����������B
	m_animation.Play(m_animationFlug);
	m_animation.Update(1.0f / 30.0f);
	m_model.UpdateWorldMatrix(m_position, m_rotation, CVector3::One());
}
void Enemy::Render()
{
	m_model.Draw(
		enRenderMode_Normal,
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}
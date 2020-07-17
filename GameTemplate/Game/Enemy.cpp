#include "stdafx.h"
#include "Enemy.h"
#include "Player.h"
Enemy::Enemy()
{
	
	m_model.Init(L"Assets/modelData/enemy.cmo");
	
	//アニメーションクリップのロード。
	m_animationClip[enAnimationCrip_stay].Load(L"Assets/animData/stay.tka");
	m_animationClip[enAnimationCrip_run].Load(L"Assets/animData/run.tka");
	m_animationClip[enAnimationCrip_attack].Load(L"Assets/animData/ata.tka");
	m_animationClip[enAnimationCrip_hirumu].Load(L"Assets/animData/hirumu.tka");
	m_animationClip[enAnimationCrip_death].Load(L"Assets/animData/death.tka");
	//ループフラグを設定。
	m_animationClip[enAnimationCrip_stay].SetLoopFlag(true);
	m_animationClip[enAnimationCrip_run].SetLoopFlag(true);
	m_animationClip[enAnimationCrip_attack].SetLoopFlag(true);
	m_animationClip[enAnimationCrip_hirumu].SetLoopFlag(true);
	m_animationClip[enAnimationCrip_death].SetLoopFlag(true);
	//アニメーションの初期化。
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
		m_charaCon,
		&m_deathAnimTime,
		&m_attackPow,
		&m_speed
	);
	//アニメーションを決定。
	m_animation.Play(m_animationFlug);
	m_animation.Update(1.0f / 30.0f);
	m_model.UpdateWorldMatrix(m_position, m_rotation, CVector3::One() * 1.5f);
}
void Enemy::SetRegistShadowCaster()
{
	g_goMgr.GetShadowMap()->RegistShadowCaster(&m_model);
}
void Enemy::Render()
{
	m_model.Draw(
		enRenderMode_Normal,
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}
void Enemy::Saty(CVector3* position, CVector3* initPos)
{
	//走るアニメーション。
	m_animationFlug = enAnimationCrip_stay;
	m_targetPos = *initPos;
	CVector3 v = *initPos - *position;
	float fds = v.Length();
	if (fds <= 15.0f) {
		m_moveSpeed = CVector3::Zero();
		*position = *initPos;
		m_animationFlug = enAnimationCrip_stay;
	}
}
void Enemy::Attack(float AttackPow)
{
	m_targetPos = m_player->GetPosition();
	m_player->SetStopFlug(true);
	//攻撃アニメーション。
	m_animationFlug = enAnimationCrip_attack;

	m_AttackTimer++;
	if (m_AttackTimer >= 30) {
		m_player->SetDamageFlug(true);
		m_damage = AttackPow / m_player->GetPlayerHp();
		m_player->SetDamage(m_damage);
		m_damageS.Stop();
		m_damageS.Play(false);
		m_AttackTimer = 0;
	}
}
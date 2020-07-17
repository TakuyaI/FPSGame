#include "stdafx.h"
#include "DogEnemy.h"
#include "Player.h"

DogEnemy::DogEnemy()
{
	m_model.Init(L"Assets/modelData/dogEnemy.cmo");

	//アニメーションクリップのロード。
	m_animationClip[enAnimationCrip_stay].Load(L"Assets/animData/stay_dog.tka");
	m_animationClip[enAnimationCrip_run].Load(L"Assets/animData/run_dog.tka");
	m_animationClip[enAnimationCrip_attack].Load(L"Assets/animData/ata_dog.tka");
	m_animationClip[enAnimationCrip_hirumu].Load(L"Assets/animData/hirumu_dog.tka");
	m_animationClip[enAnimationCrip_death].Load(L"Assets/animData/death_dog.tka");
	//ループフラグを設定。
	m_animationClip[enAnimationCrip_stay].SetLoopFlag(true);
	m_animationClip[enAnimationCrip_run].SetLoopFlag(true);
	m_animationClip[enAnimationCrip_attack].SetLoopFlag(true);
	m_animationClip[enAnimationCrip_hirumu].SetLoopFlag(true);
	m_animationClip[enAnimationCrip_death].SetLoopFlag(true);
	//アニメーションの初期化。
	m_animation.Init(m_model, m_animationClip, enAnimationCrip_Num);
}


DogEnemy::~DogEnemy()
{
}
bool DogEnemy::Start()
{
	m_initPos = m_position;
	m_charaCon.Init(
		ENEMY_CONTROLLER_RADIUS,
		ENEMY_CONTROLLER_HEIGHT,
		m_position
	);
	return true;
}
void DogEnemy::Update()
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

void DogEnemy::SetRegistShadowCaster()
{
	g_goMgr.GetShadowMap()->RegistShadowCaster(&m_model);
}
void DogEnemy::Render()
{
	m_model.Draw(
		enRenderMode_Normal,
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}
void DogEnemy::Saty(CVector3* position, CVector3* initPos)
{
	//走るアニメーション。
	m_animationFlug = enAnimationCrip_stay;
	float sd = m_toPlayerVec.Length();
	if ( sd <= 1500.0f) {
		m_targetPos = m_player->GetPosition();
	}
	else {
		m_targetPos = *initPos;
	}
	CVector3 v = *initPos - *position;
	float fds = v.Length();
	if (fds <= 15.0f) {
		m_moveSpeed = CVector3::Zero();
		*position = *initPos;
		m_animationFlug = enAnimationCrip_stay;
	}
}
void DogEnemy::Attack(float AttackPow)
{
	m_targetPos = m_player->GetPosition();
	m_player->SetStopFlug(true);
	//攻撃アニメーション。
	m_animationFlug = enAnimationCrip_attack;

	m_AttackTimer++;
	if (m_AttackTimer >= 20) {
		m_player->SetDamageFlug(true);
		m_damage = AttackPow / m_player->GetPlayerHp();
		m_player->SetDamage(m_damage);
		m_damageS.Stop();
		m_damageS.Play(false);
		m_AttackTimer = 0;
	}
}
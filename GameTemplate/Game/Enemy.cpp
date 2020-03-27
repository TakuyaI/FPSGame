#include "stdafx.h"
#include "Enemy.h"
#include "GameManager.h"
#include "EnemyGenerator.h"

const int ENEMY_LOITERING = 0; //徘徊中
const int ENEMY_TRACKING = 1;  //追跡中
const int ENEMY_ATTACK = 2;    //攻撃
const float ENEMY_CONTROLLER_RADIUS = 30.0f;
const float ENEMY_CONTROLLER_HEIGHT = 100.0f;

Enemy::Enemy()
{
	m_player = g_goMgr.FindGameObject<Player>(player);
	m_enemyGen = g_goMgr.FindGameObject<EnemyGenerator>(enemygenerator);

	m_initPos = m_enemyGen->GetEnemyInitPos();
	m_position = m_enemyGen->GetEnemyInitPos();
	m_model.Init(L"Assets/modelData/enemy.cmo");
	m_charaCon.Init(
		ENEMY_CONTROLLER_RADIUS,
		ENEMY_CONTROLLER_HEIGHT,
		m_initPos
	);
	if (g_goMgr.Rand(2) == 0) {
		m_enemyHp = 50;
	}
	else if (g_goMgr.Rand(2) == 1) {
		m_enemyHp = 70;
	}
	else if (g_goMgr.Rand(2) == 2) {
		m_enemyHp = 100;
	}
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
	
	//サンプルのエフェクトをロードする。
	m_sampleEffect = Effekseer::Effect::Create(g_goMgr.GetEffekseerManager(), (const EFK_CHAR*)L"Assets/effect/test02.efk");
	//サウンドをロード。
	m_bgm.Init(L"Assets/sound/bomb1.wav");
	m_walk.Init(L"Assets/sound/walkS.wav");
	m_damageS.Init(L"Assets/sound/damageS.wav");
}


Enemy::~Enemy()
{
}

void Enemy::Loitering()
{
	//走るアニメーション。
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
void Enemy::Tracking()
{
	//走るアニメーション。
	m_animationFlug = enAnimationCrip_run;
	m_targetPos = m_player->GetPosition();
}
void Enemy::Attack()
{
	m_targetPos = m_player->GetPosition();
	m_enemyGen->SetAttackFlug(true);
	//攻撃アニメーション。
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
			//Enemyが突き放し終えた。
			m_pushAwaySpeed = 100.0f;
			m_player->SetPushAwayFlug(false);
			m_endPushAwayflug = false;
			m_enemyGen->SetAttackFlug(false);
		}
	}
}
void Enemy::Update()
{
	
	//EnemyからPlayerへ向かうベクトル。
	m_toPlayerVec = m_player->GetPosition() - m_position;

	m_toTargetVec = m_targetPos - m_position;
	m_toTargetVec.y = 0.0f;
	m_toTargetVec.Normalize();

	CVector3 v = m_toPlayerVec;
	v.Normalize();
	float d = m_toTargetVec.Dot(v);

	float angle = acos(d);
	//if (fabsf(angle) < CMath::DegToRad(90.0f)) {
		if (m_toPlayerVec.Length() <= 750.0f) {
			//プレイヤーとの距離が100以内になった。
			if (m_toPlayerVec.Length() <= 70.0f) {
				//プレイヤーとの距離が10以内になった。
				//攻撃をする。
				m_state = ENEMY_ATTACK;
				m_endPushAwayflug = true;
			}
			else {
				//追跡をする。
				m_state = ENEMY_TRACKING;
			}
		}
		else {
			//徘徊する。
			m_state = ENEMY_LOITERING;
		}
	//}
	if (m_player->GetPushAwayFlug() != false &&
		m_endPushAwayflug != false) {
		//Enemyを突き放した。
		m_state = ENEMY_ATTACK;
	}
	
	m_moveSpeed = m_toTargetVec * 10.0f;
	float rot = atan2(m_toTargetVec.x, m_toTargetVec.z);
	m_rotation.SetRotation(CVector3::AxisY(), rot);
	m_rotation.Multiply(m_targetPos);

	
	if (m_state == ENEMY_LOITERING){
		Loitering();
	}
	else if (m_state == ENEMY_TRACKING) {
		Tracking();
	}
	else if (m_state == ENEMY_ATTACK) {
		Attack();
	}

	if (m_position.y <= 0.0f) {
		m_moveSpeed.y = 0.0f;
	}
	if (m_receiveDamageFlug != false) {
		//ダメージを受けたら、一定時間怯む。
		m_receiveDamageFlug = false;
		m_animationFlug = enAnimationCrip_hirumu;
		m_bgm.Stop();
		m_bgm.Play(false);
		//再生中のエフェクトを止める。
		g_goMgr.GetEffekseerManager()->StopEffect(m_playEffectHandle);
		//再生。
		m_effectPos = m_position;
		m_effectPos.y += 100.0f;
		m_playEffectHandle = g_goMgr.GetEffekseerManager()->Play(m_sampleEffect, m_effectPos.x, m_effectPos.y, m_effectPos.z);
		m_moveSpeed = CVector3::Zero();
	}

	if (m_death != false) {
		//死亡。
		m_moveSpeed = CVector3::Zero();
		m_deathAnimtime++;
		m_animationFlug = enAnimationCrip_death;
		if (m_deathAnimtime >= 60) {
			g_goMgr.DeleteGameObject(this);
		}
	}
	//アニメーションを決定。
	if (m_animationFlug == enAnimationCrip_stay) {
		m_animation.Play(enAnimationCrip_stay);
	}
	else if (m_animationFlug == enAnimationCrip_run) {

		m_animation.Play(enAnimationCrip_run);
	}
	else if (m_animationFlug == enAnimationCrip_attack) {
		m_animation.Play(enAnimationCrip_attack);
	}
	else if (m_animationFlug == enAnimationCrip_hirumu) {
		m_animation.Play(enAnimationCrip_hirumu);
	}
	else if (m_animationFlug == enAnimationCrip_death) {
		m_animation.Play(enAnimationCrip_death);
	}
	m_animation.Update(1.0f / 30.0f);

	if (m_animationFlug == enAnimationCrip_run) {
		m_walk.Play(false);
	}
	else {
		m_walk.Stop();
	}

	m_position = m_charaCon.Execute(1.0f, m_moveSpeed);
	m_model.UpdateWorldMatrix(m_position, m_rotation, CVector3::One());
	
}
void Enemy::Render()
{
	m_model.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}
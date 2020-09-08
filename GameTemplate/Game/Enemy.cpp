#include "stdafx.h"
#include "Enemy.h"
#include "Player.h"

Enemy::Enemy()
{
	//モデルの初期化。
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
	//初期座標を設定。
	m_initPos = m_position;
	//キャラコンの初期化。
	m_charaCon.Init(
		m_controllerRadius,
		m_controllerHeight,
		m_position
	);
	return true;
}
void Enemy::Update()
{
	//敵を更新。
	EnemyUpdate(
		&m_position,
		&m_initPos,
		&m_rotation,
		m_charaCon,
		&m_deathAnimTime,
		&m_attackPow,
		&m_speed
	);
	//アニメーションを再生。
	m_animation.Play(m_animationFlug);
	//アニメーションを更新。
	m_animation.Update(1.0f / 30.0f);
	//モデルを更新。
	m_model.UpdateWorldMatrix(m_position, m_rotation, CVector3::One() * 1.5f);
}
void Enemy::SetRegistShadowCaster()
{
	//シャドウキャスターにセット。
	g_goMgr.GetShadowMap()->RegistShadowCaster(&m_model);
}
void Enemy::Render()
{
	//描画。
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
	//現在の座標から初期座標に向かって伸びるベクトルを計算。
	CVector3 toInitPosV = *initPos - *position;
	if (toInitPosV.Length() <= m_initPosRange) {
		//toInitPosV.Length()が15以下の場合、
		//動きをとめて、座標を初期座標に代入する。
		m_moveSpeed = CVector3::Zero();
		*position = *initPos;
		//待機アニメーション。
		m_animationFlug = enAnimationCrip_stay;
	}
}
void Enemy::Attack(float AttackPow)
{
	//プレイヤーが動かなくなるように、フラグを送る。
	m_player->SetStopFlug(true);
	//プレイヤーをターゲットにする。
	m_targetPos = m_player->GetPosition();
	//攻撃アニメーション。
	m_animationFlug = enAnimationCrip_attack;
	//毎フレームタイマーを加算していく。
	m_AttackTimer++;
	if (m_AttackTimer >= m_AttackTime) {
		//タイマーが30になった。
		//プレイヤーにダメージを与えたフラグを送る。
		m_player->SetDamageFlug(true);
		//プレイヤーが受けるダメージを送る。
		//m_damageは1を100としたときの値を送る。
		m_damage = AttackPow / m_player->GetPlayerHp();
		m_player->SetDamage(m_damage);
		//ダメージサウンド。
		m_giveDamageS.Stop();
		m_giveDamageS.Play(false);
		//タイマーをリセット。
		m_AttackTimer = 0;
	}
}
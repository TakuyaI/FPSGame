#include "stdafx.h"
#include "DogEnemy.h"
#include "Player.h"

DogEnemy::DogEnemy()
{
	//モデルの初期化。
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
	//初期座標を設定。
	m_initPos = m_position;
	//キャラコンの初期化。
	m_charaCon.Init(
		ENEMY_CONTROLLER_RADIUS,
		ENEMY_CONTROLLER_HEIGHT,
		m_position
	);
	return true;
}
void DogEnemy::Update()
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
	m_model.UpdateWorldMatrix(m_position, m_rotation, CVector3::One() * 2.0f);
}

void DogEnemy::SetRegistShadowCaster()
{
	//シャドウキャスターにセット。
	g_goMgr.GetShadowMap()->RegistShadowCaster(&m_model);
}
void DogEnemy::Render()
{
	//描画。
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
	if (m_toPlayerVec.Length() <= m_lockOnRange) {
		//プレイヤーとの距離が1500以内になったら、
		//プレイヤーの方を向く。
		m_targetPos = m_player->GetPosition();
	}
	else {
		m_targetPos = *initPos;
	}
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
void DogEnemy::Attack(float AttackPow)
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
		//タイマーが20になった。
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
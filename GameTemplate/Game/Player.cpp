#include "stdafx.h"
#include "Player.h"
//#include "GameManager.h"
#include "EnemyGenerator.h"
#include "Enemy.h"

const float PLAYER_CONTROLLER_RADIUS = 30.0f;
const float PLAYER_CONTROLLER_HEIGHT = 200.0f;

Player::Player()
{
	m_greenSprite.Init(L"Resource/sprite/oamidori.dds", 200.0f, 15.0f);
	m_redSprite.Init(L"Resource/sprite/aka.dds", 200.0f, 15.0f);
	m_hpBlackSprite.Init(L"Resource/sprite/kuro.dds", 200.0f, 17.0f);

	//cmoファイルの読み込み。
	m_model.Init(L"Assets/modelData/player.cmo");
	/*m_charaCon.Init(
		PLAYER_CONTROLLER_RADIUS,
		PLAYER_CONTROLLER_HEIGHT,
		m_position
	);*/
}


Player::~Player()
{
}
bool Player::Start()
{
	m_charaCon.Init(
		PLAYER_CONTROLLER_RADIUS,
		PLAYER_CONTROLLER_HEIGHT,
		m_position
	);
	m_enemyGen = g_goMgr.FindGameObject<EnemyGenerator>(enemygenerator);
	return true;
}
void Player::Update()
{
	
	m_gameCamera = g_goMgr.FindGameObject<GameCamera>(gamecamera);
	//視点から注視点に向かって伸びるベクトルを求める。
	CVector3 cameraDir = m_gameCamera->GetTarget() -
		                 m_gameCamera->GetPosition();
	cameraDir.y = 0.0f;
	//正規化。
	cameraDir.Normalize();

	CVector3 cameraDirX;
	cameraDirX.Cross(
		cameraDir,
		CVector3::AxisY()
	);

	if (g_pad->IsPress(enButtonLB3)) {
		//Bボタン長押しでダッシュする。
		if (m_jumpFlag != true) {
			//ジャンプ中はダッシュできない。
			m_playerSpeed = 40.0f;
			m_dashFlug = true;
		}
	}
	else {
		//離したら戻る。
		m_playerSpeed = 20.0f;
		m_dashFlug = false;
	}
	m_moveSpeed.x = 0.0f;
	m_moveSpeed.z = 0.0f;
	m_moveSpeed += cameraDirX * g_pad->GetLStickXF()* -m_playerSpeed;
	m_moveSpeed += cameraDir * g_pad->GetLStickYF()* m_playerSpeed;

	//if (g_pad->IsTrigger(enButtonA)) {
	//	if (m_jumpFlag != true) {
	//		//m_jumpFlagが0ならジャンプできる。
	//		m_moveSpeed.y = 20.0f;
	//		//m_jumpFlagに1を代入して、
	//		//空中でジャンプできないようにする。
	//		m_jumpFlag = true;
	//	}
	//}
	m_moveSpeed.y -= 1.0f;
	
	m_position.y += m_moveSpeed.y;
	//if (m_position.y <= -5.0f) {
	//	//Playerの座標が0以下になったら、
	//	//重力を0にする。
	//	m_moveSpeed.y = -5.0f;
	//	if (m_jumpFlag != false) {
	//		m_jumpFlag = false;
	//	}
	//}

	//if (m_enemyGen->GetEnemyOccurrenceFlug() != false) {
		//Enemyが出現した。
		if (m_stopFlug != false) {
			//Enemyが攻撃してきた。
			//つかまれているから、Playerは動けない。
			m_moveSpeed = CVector3::Zero();
			float stickX = fabsf(g_pad->GetLStickXF());
			float stickY = fabsf(g_pad->GetLStickYF());
			if (b != true) {
				if (stickX >= 0.5f) {
					a += stickX;
					b = true;
				}
			}
			else {
				if (stickY >= 0.5f) {
					a += fabsf(g_pad->GetLStickYF());
					b = false;
				}
			}
			//十字ボタンを連打したら、脱出する。
				if (a >= 10.0f) {
					//十字ボタンを10回押した。
					m_pushAwayFlug = true;
					m_stopFlug = false;
					a = 0.0f;
				}
			//}
		}
	//}
	

	if (m_deathFlug != false) {
		m_moveSpeed = CVector3::Zero();
	}

	m_position = m_charaCon.Execute(1.0f, m_moveSpeed);

	//ワールド行列の更新。
	m_model.UpdateWorldMatrix(m_position, m_rotation, CVector3::One() * 1.0f);
	g_goMgr.SetmPlayerPos(m_position);
}
void Player::SetRegistShadowCaster()
{
	g_goMgr.GetShadowMap()->RegistShadowCaster(&m_model);
}
void Player::Render()
{
	/*m_model.Draw(
	enRenderMode_Normal,
	g_camera3D.GetViewMatrix(),
	g_camera3D.GetProjectionMatrix()
	);*/
}

void Player::PostRender()
{
	{//HPバー。
		m_enemyGen = g_goMgr.FindGameObject<EnemyGenerator>(enemygenerator);
		if (m_greenScale.x <= 0.0f) {
			m_deathFlug = true;
		}
		//if (m_enemyGen->GetEnemyOccurrenceFlug() != false) {
			//敵が出現中。
			if (m_damageFlug != false) {
				m_flug = true;
			
				m_greenScale.x -= m_damage;
				m_redDamage += m_damage;
				m_redDamage /= 2.0f;
				m_damage = 0.0f;
				m_damageFlug = false;
			}
			if (m_flug != false) {
				float aa = 0.01;
				m_redScale.x -= aa;
				m_redDamage -= aa;
				if (m_redDamage <= 0.0f) {
					m_flug = false;
				}
			}
		//}

		if (m_greenScale.x < m_redScale.x) {
			m_recoveryTimer++;
			if (m_recoveryTimer >= 60) {
				m_greenScale.x += 0.005f;
				m_recoveryTimer = 0;
			}
		}

		//1番後ろの黒ゲージ。
		m_hpBlackSprite.Update(
			m_blackGaugePos,
			CQuaternion::Identity(),
			m_blackScale,
			CVector2::Zero()
		);
		//真ん中の赤ゲージ。
		m_redSprite.Update(
			m_gaugePos,
			CQuaternion::Identity(),
			m_redScale,
			CVector2::Zero()
		);
		//1番前の緑ゲージ
		m_greenSprite.Update(
			m_gaugePos,
			CQuaternion::Identity(),
			m_greenScale,
			CVector2::Zero()
		);

		m_hpBlackSprite.Draw();
		m_redSprite.Draw();
		m_greenSprite.Draw();

	}
}
#include "stdafx.h"
#include "Player.h"

const float PLAYER_CONTROLLER_RADIUS = 30.0f;
const float PLAYER_CONTROLLER_HEIGHT = 200.0f;

Player::Player()
{
	m_damageSprite.Init(L"Resource/sprite/damage.dds", FRAME_BUFFER_W, FRAME_BUFFER_H);
	m_damageSprite.DeltaAlpha(-1.0f);
	m_greenSprite.Init(L"Resource/sprite/oamidori.dds", 200.0f, 15.0f);
	m_hpBlackSprite.Init(L"Resource/sprite/kuro.dds", 200.0f, 17.0f);
}


Player::~Player()
{
}
bool Player::Start()
{
	m_model.Init(L"Assets/modelData/player.cmo");
	m_charaCon.Init(
		PLAYER_CONTROLLER_RADIUS,
		PLAYER_CONTROLLER_HEIGHT,
		m_position
	);
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
			m_playerSpeed = 40.0f;
	}
	else {
		//離したら戻る。
		m_playerSpeed = 20.0f;
	}
	if (g_pad->GetLStickXF() >= 0.5f || g_pad->GetLStickYF() >= 0.5f) {
		//移動中はリコイルのブレが大きくなる。
		m_gameCamera->SetWidthUpperLimit(100.0f);
		m_gameCamera->SetRecoilRightAndLeft(1.0f);
	}
	else {
		m_gameCamera->SetWidthUpperLimit(50.0f);
		m_gameCamera->SetRecoilRightAndLeft(0.3f);
	}
	m_moveSpeed = CVector3::Zero();
	m_moveSpeed += cameraDirX * g_pad->GetLStickXF()* -m_playerSpeed;
	m_moveSpeed += cameraDir * g_pad->GetLStickYF()* m_playerSpeed;

	//重力を受ける。
	m_moveSpeed.y -= 1.0f;
	if (m_position.y <= -5.0f) {
		//Playerの座標が0以下になったら、
		//重力を0にする。
		m_moveSpeed.y = -5.0f;
	}

	if (m_stopFlug != false) {
		//Enemyが攻撃してきた。
		//つかまれているから、Playerは動けない。
		m_moveSpeed = CVector3::Zero();
		float stickX = fabsf(g_pad->GetLStickXF());
		float stickY = fabsf(g_pad->GetLStickYF());
		if (m_moveStickFlug != true) {
			if (stickX >= 0.5f) {
				m_pushAwayNum += stickX;
				m_moveStickFlug = true;
			}
		}
		else {
			if (stickY >= 0.5f) {
				m_pushAwayNum += fabsf(g_pad->GetLStickYF());
				m_moveStickFlug = false;
			}
		}
		//十字ボタンを連打したら、脱出する。
			if (m_pushAwayNum >= 10.0f) {
				//十字ボタンを10回押した。
				m_pushAwayFlug = true;
				m_stopFlug = false;
				m_pushAwayNum = 0.0f;
			}
	}
	

	if (m_deathFlug != false) {
		m_moveSpeed = CVector3::Zero();
	}

	m_position = m_charaCon.Execute(1.0f,0, m_moveSpeed);

	//ワールド行列の更新。
	m_model.UpdateWorldMatrix(m_position, m_rotation, CVector3::One() * 0.5f);
	g_goMgr.SetmPlayerPos(m_position);
	g_goMgr.SetPointLightPos(m_position, 0);
}
void Player::SetRegistShadowCaster()
{
	g_goMgr.GetShadowMap()->RegistShadowCaster(&m_model);
}
void Player::Render()
{
	m_model.Draw(
	enRenderMode_Normal,
	g_camera3D.GetViewMatrix(),
	g_camera3D.GetProjectionMatrix()
	);
}

void Player::PostRender()
{
	{//HPバー。
		if (m_greenScale.x <= 0.0f) {
			m_deathFlug = true;
		}
		if (m_damageFlug != false) {
			//ダメージを受けた。
			m_hpChanges -= m_damage;
			m_damageFlug = false;
		}
		m_greenScale.x += m_hpChanges;
		
		//後ろの黒ゲージ。
		m_hpBlackSprite.Update(
			m_blackGaugePos,
			CQuaternion::Identity(),
			m_blackScale,
			CVector2::Zero()
		);
		
		//前の緑ゲージ
		m_greenSprite.Update(
			m_gaugePos,
			CQuaternion::Identity(),
			m_greenScale,
			CVector2::Zero()
		);
		m_hpBlackSprite.Draw();
		m_greenSprite.Draw();

		m_hpChanges *= -1.0f;
		m_damageSprite.DeltaAlpha(m_hpChanges);
		m_hpChanges = 0.0f;
		m_damageSprite.Draw();
	}
}
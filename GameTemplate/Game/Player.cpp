#include "stdafx.h"
#include "Player.h"
#include "GameManager.h"
#include "EnemyGenerator.h"
#include "Enemy.h"

const float PLAYER_CONTROLLER_RADIUS = 30.0f;
const float PLAYER_CONTROLLER_HEIGHT = 200.0f;

Player::Player()
{
	//cmoファイルの読み込み。
	m_model.Init(L"Assets/modelData/unityChan.cmo");
	m_charaCon.Init(
		PLAYER_CONTROLLER_RADIUS,
		PLAYER_CONTROLLER_HEIGHT,
		m_position
	);
}


Player::~Player()
{
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

	if (g_pad->IsPress(enButtonB)) {
		//Bボタン長押しでダッシュする。
		if (m_jumpFlag != true) {
			//ジャンプ中はダッシュできない。
			m_playerSpeed = 40.0f;
		}
	}
	else {
		//離したら戻る。
		m_playerSpeed = 20.0f;
	}

	m_moveSpeed.x = 0.0f;
	m_moveSpeed.z = 0.0f;
	m_moveSpeed += cameraDirX * g_pad->GetLStickXF()* -m_playerSpeed;
	m_moveSpeed += cameraDir * g_pad->GetLStickYF()* m_playerSpeed;

	if (g_pad->IsTrigger(enButtonA)) {
		if (m_jumpFlag != true) {
			//m_jumpFlagが0ならジャンプできる。
			m_moveSpeed.y = 20.0f;
			//m_jumpFlagに1を代入して、
			//空中でジャンプできないようにする。
			m_jumpFlag = true;
		}
	}
	m_moveSpeed.y -= 1.0f;
	
	m_position.y += m_moveSpeed.y;
	if (m_position.y <= 0.0f) {
		//Playerの座標が0以下になったら、
		//重力を0にする。
		m_moveSpeed.y = 0.0f;
		if (m_jumpFlag != false) {
			m_jumpFlag = false;
		}
	}

	m_enemyGen = g_goMgr.FindGameObject<EnemyGenerator>(enemygenerator);
	if (m_enemyGen->GetEnemyOccurrenceFlug() != false) {
		//Enemyが出現した。
		m_enemy = g_goMgr.FindGameObject<Enemy>(enemy);
		if (m_enemyGen->GetAttackFlug() != false) {
			//Enemyが攻撃してきた。
			//つかまれているから、Playerは動けない。
			m_moveSpeed = CVector3::Zero();
			if (g_pad->IsTrigger(enButtonY)) {
				a++;
				if (a >= 5) {
					//Yボタンを5回押した。
					m_pushAwayFlug = true;
					a = 0;
				}
			}
		}
	}

	m_position = m_charaCon.Execute(1.0f, m_moveSpeed);

	//ワールド行列の更新。
	m_model.UpdateWorldMatrix(m_position, CQuaternion::Identity(), CVector3::One() * 1.0f);
	
}
void Player::Render()
{
	/*m_model.Draw(
	g_camera3D.GetViewMatrix(),
	g_camera3D.GetProjectionMatrix()
	);*/
}
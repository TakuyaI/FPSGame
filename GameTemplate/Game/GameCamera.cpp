#include "stdafx.h"
#include "GameCamera.h"

const float MAX_SHOT_COUNT = 10.0f;//m_shotCountの最大値。
const float RECOIL_UP = -0.1f;//リコイルの上の移動量。
const float WIDTH_UPPER_LIMIT = 50.0f; //リコイルの横幅の上限。
const float NOAIM_RECOIL_RIGHT_AND_LEFT = 0.3f;//エイムしていないときのリコイルの左右の移動量。
const float AIM_RECOIL_RIGHT_AND_LEFT = 0.1f;//エイム中のリコイルの左右の移動量。
GameCamera::GameCamera()
{
	//近平面を設定。
	g_camera3D.SetNear(1.0f);
	//遠平面を設定。
	g_camera3D.SetFar(20000.0f);
}


GameCamera::~GameCamera()
{
}

void GameCamera::Recoil()
{
	GunNumber gunNum;
	if (g_goMgr.GetShotFlug() != false &&          //弾を撃った。
		m_gunGen->GetGunNum() == gunNum.RIFLE_NUMBER //銃がライフル。
		) {
		if (m_gunGen->GetAimFlug() != false) {
			//エイム中はリコイルの左右の移動量を減らす。
			m_recoilRightAndLeft = AIM_RECOIL_RIGHT_AND_LEFT;
		}
		else {
			//エイムしていないときはリコイルの左右の移動量を。
			m_recoilRightAndLeft = NOAIM_RECOIL_RIGHT_AND_LEFT;
		}
		//randomにランダムで、0か１が入る。
		int random = g_goMgr.Rand(1);
		if (random != 0) {
			//randomが１だった。
			if (m_width >= m_widthUpperLimit) {
				//m_widthがプラスの上限に達したので、マイナスする。
				m_angle -= m_recoilRightAndLeft;
				m_width -= m_recoilRightAndLeft;
			}
			else {
				//m_widthをプラスする。
				m_angle += m_recoilRightAndLeft;
				m_width += m_recoilRightAndLeft;
			}
		}
		else{//randomが0だった。
			if (m_width <= -m_widthUpperLimit) {
				//m_widthがマイナスの上限に達したので、プラスする。
				m_angle += m_recoilRightAndLeft;
				m_width =+m_recoilRightAndLeft;
			}
			else {
				//m_widthをマイナスする。
				m_angle -= m_recoilRightAndLeft;
				m_width =-m_recoilRightAndLeft;
			}

		}
		//少し上を向く。
		m_angle2 += RECOIL_UP;
		m_shotCount += fabsf(RECOIL_UP);
		//パット操作した分だけ、m_shotCountをマイナスする。
		m_shotCount -= g_pad->GetRStickYF() * -m_rotSpeed;
		if (m_shotCount >= MAX_SHOT_COUNT) {
			//m_shotCountが最大値に達した。
			m_angle2 = g_pad->GetRStickYF() * -m_rotSpeed;
			m_shotCount = MAX_SHOT_COUNT;
		}
	}
	else {//弾を撃っていない。
		m_width = 0.0f;
		m_shotCount -= m_angle2;
	}
}

bool GameCamera::Start()
{
	//プレイヤーのインスタンスを探す。
	m_player = g_goMgr.FindGameObject<Player>(player);
	//GunGeneratorのインスタンスを探す。
	m_gunGen = g_goMgr.FindGameObject<GunGenerator>(gungenerator);
	CQuaternion pRot = m_player->GetRotation();
	pRot.Multiply(m_toTargetPos);
	return true;
}
void GameCamera::Update()
{
	//座標にプレイヤーの座標を代入。
	m_position = m_player->GetPosition();
	//カメラの上下の回転の上限を決めるために、m_toTargetPosとm_cameraOffsetを保存しておく。
	CVector3 toCameraPosOld = m_toTargetPos;
	CVector3 cameraOffsetOld = m_cameraOffset;

	if (m_player->GetDeathFlug() != true) {
		//Playerが死んでいない。
		m_angle2 = g_pad->GetRStickYF() * -m_rotSpeed;
		m_angle = g_pad->GetRStickXF() * m_rotSpeed;
	}
	//リコイル。
	Recoil();

	//Y軸周りの回転。
	m_rotation.SetRotationDeg(CVector3::AxisY(), m_angle);
	m_rotation.Multiply(m_toTargetPos);
	m_rotation.Multiply(m_cameraOffset);

	//X軸周りの回転。
	CVector3 axisX = CVector3::Zero();
	//Y軸とm_toTargetPosの外積を求めて、X軸を求める。
	axisX.Cross(CVector3::AxisY(), m_toTargetPos);
	axisX.Normalize();

	m_rotation.SetRotationDeg(axisX, m_angle2);
	m_rotation.Multiply(m_toTargetPos);
	m_rotation.Multiply(m_cameraOffset);
	
	m_position += m_cameraOffset;

	//プレイヤーからターゲットへ向かうベクトルを求める。
	CVector3 cameraForward = m_target - m_position;
	//正規化。
	cameraForward.Normalize();
	m_toTarget = cameraForward;
	
	CVector3 toPosDir = m_toTargetPos;
	toPosDir.Normalize();
	if (toPosDir.y < -0.5f) {
		//カメラが下向きすぎ。
		m_toTargetPos = toCameraPosOld;
		m_cameraOffset = cameraOffsetOld;
		m_shotCount++;
	}
	else if (toPosDir.y > 0.8f) {
		//カメラが上向きすぎ。
		m_toTargetPos = toCameraPosOld;
		m_cameraOffset = cameraOffsetOld;
		m_shotCount--;
	}

	m_target = m_position + m_toTargetPos;
	g_camera3D.SetTarget(m_target);
	g_camera3D.SetPosition(m_position);
	g_camera3D.SetViewAngle(CMath::DegToRad(m_viewAngle));
	g_camera3D.Update();

}
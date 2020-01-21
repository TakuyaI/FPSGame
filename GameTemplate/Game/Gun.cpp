#include "stdafx.h"
#include "Gun.h"
#include "GunGenerator.h"
#include "GameManager.h"

//銃の情報。
struct GunInformation {
	const int RIFLE_INTERVAL_TIME = 5;     //ライフルバレットのインターバルタイム。
	const int SHOTGUN_INTERVAL_TIME = 10;  //ショットガンバレットのインターバルタイム。
	const int SNIPER_INTERVAL_TIME = 20;  //スナイパーバレットのインターバルタイム。
	const float RIFLE_MOVE_SPEED = 200.0f; //ライフルバレットの速度。
	const float SHOTGUN_MOVE_SPEED = 100.0f; //ショットガンバレットの速度。
	const float SNIPER_MOVE_SPEED = 400.0f; //スナイパーバレットの速度。
	const int RIFLE_BLAZE = 50;              //ライフル弾の連射弾数。
	const int SHOTGUN_BLAZE = 3;              //ショットガン弾の連射弾数。
	const int SNIPER_BLAZE = 4;              //スナイパー弾の連射弾数。
};
Gun::Gun()
{
	GunInformation gunInf;
	GunNumber gunNum;
	m_gunGen = g_goMgr.FindGameObject<GunGenerator>(gungenerator);
	if (m_gunGen->GetNextNum() == gunNum.RIFLE_NUMBER) {
		m_model.Init(L"Assets/modelData/riful.cmo");
		m_bulletIntervalTime = gunInf.RIFLE_INTERVAL_TIME;
		m_bulletMoveSpeed = gunInf.RIFLE_MOVE_SPEED;
		m_maxBlaze = gunInf.RIFLE_BLAZE;
	}
	else if (m_gunGen->GetNextNum() == gunNum.SHOTGUN_NUMBER) {
		m_model.Init(L"Assets/modelData/gun2.cmo");
		m_bulletIntervalTime = gunInf.SHOTGUN_INTERVAL_TIME;
		m_bulletMoveSpeed = gunInf.SHOTGUN_MOVE_SPEED;
		m_maxBlaze = gunInf.SHOTGUN_BLAZE;
	}
	else if (m_gunGen->GetNextNum() == gunNum.SNIPER_NUMBER) {
		m_model.Init(L"Assets/modelData/sniper.cmo");
		m_bulletIntervalTime = gunInf.SNIPER_INTERVAL_TIME;
		m_bulletMoveSpeed = gunInf.SNIPER_MOVE_SPEED;
		m_maxBlaze = gunInf.SNIPER_BLAZE;
	}
	m_ammo = m_gunGen->GetGunAmmo();
	m_blaze = m_gunGen->GetGunBlaze();
	m_gameCam = g_goMgr.FindGameObject<GameCamera>(gamecamera);
}

Gun::~Gun()
{
}

void Gun::Update()
{
	CVector3 pos = m_gameCam->GetToTargetPos();
	pos.y = 0.0f;
	
	m_angle = CMath::RadToDeg(atan2(pos.x, pos.z));// acos(pos.Dot(CVector3::Front())));

	pos = m_gameCam->GetToTargetPos();
	float y = pos.y;
	pos.y = 0.0f;
	float x = pos.Length();
	m_angle2 = CMath::RadToDeg(atan2(-y,x));

	CQuaternion YRot;
	YRot.SetRotationDeg(CVector3::AxisY(), m_angle);
	CQuaternion XRot;
	XRot.SetRotationDeg(CVector3::AxisX(), m_angle2);
	m_rotation.Multiply(YRot, XRot);


	m_position = m_gameCam->GetPosition();

	CQuaternion PosRot;
	m_Pos = m_gunLocalPosition;
	PosRot.SetRotationDeg(CVector3::AxisY(), m_angle);
	PosRot.Multiply(m_Pos);

	m_position += m_Pos;


	if (g_pad->IsPress(enButtonRB1)) {
		if (m_ammo > 0 && m_blaze > 0) {
			m_bulletIntervalTimer++;
			if (m_bulletIntervalTimer >= m_bulletIntervalTime) {
				m_bullet = g_goMgr.NewGameObject<Bullet>(bullet);
				m_bullet->SetPosition(m_position);
				CVector3 v = m_gameCam->GetTargetPos() - m_position;
				v.Normalize();
				m_bulletPos = v * m_bulletMoveSpeed;
				m_bullet->SetMoveSpeed(m_bulletPos);
				m_ammo--;
				m_blaze--;
				m_bulletIntervalTimer = 0;
				m_shootingBulletFlug = true;
			}
		}
	}
	else {
		m_shootingBulletFlug = false;
	}

	//リロード。
	if (g_pad->IsTrigger(enButtonY)) {
		//Yボタンを押した。
		if (m_maxBlaze > m_blaze) {
			//装填されている弾が最大でない。
			if (m_ammo < m_maxBlaze) {
				//残り弾数が最大装填弾数より少ない。
				//残りの弾数を装填する。
				m_blaze = m_ammo;
			}
			else {
				//使った弾数分、装填する。
				m_usedBullet = m_maxBlaze - m_blaze;
				m_blaze += m_usedBullet;
			}
		}
	}

	m_model.UpdateWorldMatrix(m_position, m_rotation, CVector3::One());
	
}
void Gun::Render()
{
	m_model.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}

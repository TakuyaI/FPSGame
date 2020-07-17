#include "stdafx.h"
#include "Player.h"
#include "Enemy.h"
#include "GameCamera.h"
#include "Bullet.h"

IGunObject::IGunObject()
{
	m_gameCam = g_goMgr.FindGameObject<GameCamera>(gamecamera);
	m_gunGen = g_goMgr.FindGameObject<GunGenerator>(gungenerator);
	m_player = g_goMgr.FindGameObject<Player>(player);

	m_sprite.Init(L"Resource/sprite/gage.dds", 100.0f, 70.0f);
	m_gunShot.Init(L"Assets/sound/raifulS.wav");
}

IGunObject::~IGunObject()
{
	g_goMgr.QueryGameObject<Bullet>(bullet, [](Bullet * bul)->bool
		{
			g_goMgr.DeleteGameObject(bul);
			return true;
		});
}

void IGunObject::GunRotation(CQuaternion* rotation)
{
	//カメラのターゲットを代入。
	CVector3 pos = m_gameCam->GetToTargetPos();
	pos.y = 0.0f;

	m_angle = CMath::RadToDeg(atan2(pos.x, pos.z));

	pos = m_gameCam->GetToTargetPos();
	float y = pos.y;
	pos.y = 0.0f;
	float x = pos.Length();
	m_angle2 = CMath::RadToDeg(atan2(-y, x));

	CQuaternion YRot;
	YRot.SetRotationDeg(CVector3::AxisY(), m_angle);
	CQuaternion XRot;
	XRot.SetRotationDeg(CVector3::AxisX(), m_angle2);
	rotation->Multiply(YRot, XRot);
}

void IGunObject::GunUpdate(
	CVector3* position, CQuaternion* rotation,  
	int* ammo, int* loading, int* maxLoading, int* bulletIntervalTime, 
	float* bulletMoveSpeed, float* reaction, int* reloadTime,
	CVector3* aimingPos, CVector3* notAimPos
){
	GunRotation(rotation);
	m_gunGen->SetmAimFlug(false);
	Aim(position, rotation, aimingPos, notAimPos);
	m_bulletIntervalTimer++;
	if (m_bulletIntervalTimer >= *bulletIntervalTime) {
		m_bulletIntervalTimer = *bulletIntervalTime;
	}
	//弾を発射。
	if (m_reloadFlug != true && m_player->GetDeathFlug() != true) {
		//リロード中は発射できないかつ、Playerが死んでいない。
		//発射。
		if (g_pad->IsPress(enButtonRB1)) {
			//RB1を押した。
			float camearaViewAngle = m_gameCam->GetGameCameraViewAngle();
			if (*loading > 0) {
				//弾数が残っている。
				if (m_bulletIntervalTimer >= *bulletIntervalTime) {
					//一定間隔で弾を発射する。
					m_gunGen->SetShootingBulletFlug(true);
					m_bullet = g_goMgr.NewGameObject<Bullet>(bullet);
					m_bullet->SetPosition(*position);
					//弾のスピードを設定する。
					CVector3 v = m_gameCam->GetToTarget();
					m_bulletPos = v * *bulletMoveSpeed;
					m_bullet->SetMoveSpeed(m_bulletPos);
					//反動。
					*position += v * *reaction;
					--*loading;
					//反動をうけたので、画角を少し広くする。
					camearaViewAngle += 0.5f;
					m_gameCam->SetGameCameraViewAngle(camearaViewAngle);
					m_recoiledFlug = true;

					m_bulletIntervalTimer = 0;
					//弾を撃った時のイベント関数を呼び出す
					OnShot(position, rotation);
					g_goMgr.SetShotFlug(true);
				}
				else {
					if (m_recoiledFlug != false) {
						//前のフレームで反動を受けたので、戻す。
						camearaViewAngle -= 0.5f;
						m_gameCam->SetGameCameraViewAngle(camearaViewAngle);
						//前の反動を受けてから1回しか通らないから、
						//フラグをfalseにする。
						m_recoiledFlug = false;
					}
					g_goMgr.SetShotFlug(false);
				}
			}
			else {
				g_goMgr.SetShotFlug(false);
			}
		}
		else {
			//m_bulletIntervalTimer = *bulletIntervalTime;
			m_gunGen->SetShootingBulletFlug(false);
			g_goMgr.SetShotFlug(false);
		}
	}


	//リロード。
	if (g_pad->IsTrigger(enButtonX)) {
		//Xボタンを押した。
		if (*maxLoading > *loading && *ammo > 0 && m_gunGen->GetAimFlug() != true) {
			//装填されている弾が、最大装填弾数より少ないかつ、
			//弾が残っている。
			m_reloadFlug = true;
			m_gunGen->SetReloadFlug(true);
		}
	}

	if (m_reloadFlug != false) {
		m_reloadTimer++;
		if (m_reloadTimer > *reloadTime) {

			//装填されている弾が最大でない。
			if (*maxLoading - *loading > *ammo) {
				//残り弾数が最大装填弾数より少ない。
				//残りの弾数を装填する。
				*loading += *ammo;
				*ammo = 0;
				m_reloadFlug = false;
				m_gunGen->SetReloadFlug(false);
				m_reloadTimer = 0;
			}
			else {

				//使った弾数分、装填する。
				m_usedBullet = *maxLoading - *loading;
				*loading += m_usedBullet;
				*ammo -= m_usedBullet;
				m_reloadFlug = false;
				m_gunGen->SetReloadFlug(false);
				m_reloadTimer = 0;
			}
		}
	}

}



void IGunObject::Update()
{
}

void IGunObject::GunPostRender(int* reloadTime, int* ammo, int* loading, int* maxLoading)
{
	if (m_reloadFlug != false) {
		if (m_reloadTimer < *reloadTime) {
			scale.x += 0.5f / *reloadTime;
			m_sprite.Update(
				m_reloadGagePos,
				CQuaternion::Identity(),
				scale,
				{ 0.0f, 0.0f }
			);
			m_sprite.Draw();
		}
	}
	else {
		scale.x = 0.0f;
	}

	if (ammo < 0) {
		m_red = 1.0f;
		m_green = 0.0f;
		m_blue = 0.0f;
	}
	else {
		m_red = 1.0f;
		m_green = 1.0f;
		m_blue = 1.0f;
	}


	wchar_t text[256];
	swprintf_s(text, L"%d  /  %d ", *loading, *ammo);
	m_font.Draw(text, { 100.0f, 600.0f }, { m_red, m_green, m_blue, 1.0f }, 1.0f);
}
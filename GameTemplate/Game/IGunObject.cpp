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
	//�J�����̃^�[�Q�b�g�����B
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
	//�e�𔭎ˁB
	if (m_reloadFlug != true && m_player->GetDeathFlug() != true) {
		//�����[�h���͔��˂ł��Ȃ����APlayer������ł��Ȃ��B
		//���ˁB
		if (g_pad->IsPress(enButtonRB1)) {
			//RB1���������B
			float camearaViewAngle = m_gameCam->GetGameCameraViewAngle();
			if (*loading > 0) {
				//�e�����c���Ă���B
				if (m_bulletIntervalTimer >= *bulletIntervalTime) {
					//���Ԋu�Œe�𔭎˂���B
					m_gunGen->SetShootingBulletFlug(true);
					m_bullet = g_goMgr.NewGameObject<Bullet>(bullet);
					m_bullet->SetPosition(*position);
					//�e�̃X�s�[�h��ݒ肷��B
					CVector3 v = m_gameCam->GetToTarget();
					m_bulletPos = v * *bulletMoveSpeed;
					m_bullet->SetMoveSpeed(m_bulletPos);
					//�����B
					*position += v * *reaction;
					--*loading;
					//�������������̂ŁA��p�������L������B
					camearaViewAngle += 0.5f;
					m_gameCam->SetGameCameraViewAngle(camearaViewAngle);
					m_recoiledFlug = true;

					m_bulletIntervalTimer = 0;
					//�e�����������̃C�x���g�֐����Ăяo��
					OnShot(position, rotation);
					g_goMgr.SetShotFlug(true);
				}
				else {
					if (m_recoiledFlug != false) {
						//�O�̃t���[���Ŕ������󂯂��̂ŁA�߂��B
						camearaViewAngle -= 0.5f;
						m_gameCam->SetGameCameraViewAngle(camearaViewAngle);
						//�O�̔������󂯂Ă���1�񂵂��ʂ�Ȃ�����A
						//�t���O��false�ɂ���B
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


	//�����[�h�B
	if (g_pad->IsTrigger(enButtonX)) {
		//X�{�^�����������B
		if (*maxLoading > *loading && *ammo > 0 && m_gunGen->GetAimFlug() != true) {
			//���U����Ă���e���A�ő呕�U�e����菭�Ȃ����A
			//�e���c���Ă���B
			m_reloadFlug = true;
			m_gunGen->SetReloadFlug(true);
		}
	}

	if (m_reloadFlug != false) {
		m_reloadTimer++;
		if (m_reloadTimer > *reloadTime) {

			//���U����Ă���e���ő�łȂ��B
			if (*maxLoading - *loading > *ammo) {
				//�c��e�����ő呕�U�e����菭�Ȃ��B
				//�c��̒e���𑕓U����B
				*loading += *ammo;
				*ammo = 0;
				m_reloadFlug = false;
				m_gunGen->SetReloadFlug(false);
				m_reloadTimer = 0;
			}
			else {

				//�g�����e�����A���U����B
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
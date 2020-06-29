#include "stdafx.h"
//#include "IGunObject.h"
#include "GunGenerator.h"
//#include "GameManager.h"
#include "EnemyGenerator.h"
#include "Player.h"
#include "Enemy.h"
#include "GameCamera.h"
#include "Bullet.h"

IGunObject::IGunObject()
{
	m_gameCam = g_goMgr.FindGameObject<GameCamera>(gamecamera);
	m_gunGen = g_goMgr.FindGameObject<GunGenerator>(gungenerator);
	m_enemyGen = g_goMgr.FindGameObject<EnemyGenerator>(enemygenerator);
	m_player = g_goMgr.FindGameObject<Player>(player);

	m_sprite.Init(L"Resource/sprite/gage.dds", 100.0f, 70.0f);
	
	m_gunShot.Init(L"Assets/sound/raifulS.wav");
	
	m_ammo = m_gunGen->GetGunAmmo();
	m_loading = m_gunGen->GetGunLoading();

}

IGunObject::~IGunObject(/*m_blaze m_bulletIntervalTime m_bulletMoveSpeed m_reaction m_ammo m_reloadTime*/)
{
	g_goMgr.QueryGameObject<Bullet>(bullet, [](Bullet * bul)->bool
		{
			g_goMgr.DeleteGameObject(bul);
			return true;
		});
	g_goMgr.GetEffekseerManager()->StopEffect(m_playEffectHandle);
}
/*
void IGunObject::Aim(CVector3* position, CQuaternion* rotation, CVector3* aimingPos, CVector3* notaimPos)
{
	*position = m_gameCam->GetPosition();
	CQuaternion PosRot = *rotation;
	
	//�G�C�����Ă���Ƃ��̏e�̃��[�J�����W�B
	CVector3 aimPos = *aimingPos;
	//�G�C�����Ă��Ȃ��Ƃ��̏e�̃��[�J�����W�B
	CVector3 notAimPos = *notaimPos;

	if (m_gameCam->GetAimFlug() != false) {
		//�G�C�����Ă���B
		PosRot.Multiply(aimPos);
		PosRot.Multiply(notAimPos);

		//�G�C�����Ă��Ȃ��Ƃ��̏e�̃��[�J�����W����A
		//�G�C�����Ă���Ƃ��̏e�̃��[�J�����W�Ɍ������x�N�g�������߂�B
		m_aimMoveSpeed = aimPos - notAimPos;
		m_aimMoveSpeed /= DIVIDE_NUM;

		if (m_count < (int)DIVIDE_NUM) {
			//m_count��DIVIDE_NUM��菭�Ȃ��Ȃ�ړ�����B
			m_gunLocalPosition += m_aimMoveSpeed;
			m_count++;
		}
		else {
			m_gunLocalPosition = *aimingPos;
			PosRot.Multiply(m_gunLocalPosition);

		}
	}
	else {//�G�C�����Ă��Ȃ��B
		if (m_count > 0) {
			//m_count��0��葽���Ȃ�ړ�����B
			PosRot.Multiply(aimPos);
			PosRot.Multiply(notAimPos);

			m_aimMoveSpeed = aimPos - notAimPos;
			m_aimMoveSpeed /= DIVIDE_NUM;
			m_gunLocalPosition -= m_aimMoveSpeed;
			m_count--;
		}
		else {
			m_gunLocalPosition = notAimPos;
			PosRot.Multiply(m_gunLocalPosition);
		}
	}
	*position += m_gunLocalPosition;
}
*/
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

	Aim(position, rotation, aimingPos, notAimPos);
	if (f != false) {
		float vv = m_gameCam->GetGameCameraViewAngle();
		vv -= 0.5f;
		m_gameCam->SetGameCameraViewAngle(vv);
		f = false;
	}

	
	//�e�𔭎ˁB
	if (m_reloadFlug != true && m_enemyGen->GetAttackFlug() != true && m_player->GetDeathFlug() != true) {
		//�����[�h���͔��˂ł��Ȃ����A�G���U�����Ă��Ȃ����APlayer������ł��Ȃ��B
		//���ˁB
		if (g_pad->IsPress(enButtonRB1)) {
			//RB1���������B
			if (*loading > 0) {
				//�e�����c���Ă���B
				m_bulletIntervalTimer++;
				if (m_bulletIntervalTimer >= *bulletIntervalTime) {
					//���Ԋu�Œe�𔭎˂���B
					m_gunGen->SetShootingBulletFlug(true);
					m_bullet = g_goMgr.NewGameObject<Bullet>(bullet);
					/*CVector3 p = *position;
					p.y += 10.0f;*/
					m_bullet->SetPosition(*position);
					//�e�̃X�s�[�h��ݒ肷��B
					CVector3 v = m_gameCam->GetToTarget();
					m_bulletPos = v * *bulletMoveSpeed;
					m_bullet->SetMoveSpeed(m_bulletPos);
					//�����B
					*position += v * *reaction;
					--*loading;

					float vv2 = m_gameCam->GetGameCameraViewAngle();
					vv2 += 0.5f;
					m_gameCam->SetGameCameraViewAngle(vv2);
					f = true;

					m_bulletIntervalTimer = 0;
					//�e�����������̃C�x���g�֐����Ăяo��
					OnShot(position, rotation);
					
				}
			}
			else {
				m_gameCam->SetShotFlug(false);
			}
		}
		else {
			m_bulletIntervalTimer = *bulletIntervalTime;
			m_gunGen->SetShootingBulletFlug(false);
			m_gameCam->SetShotFlug(false);
		}
	}


	//�����[�h�B
	if (g_pad->IsTrigger(enButtonX)) {
		//X�{�^�����������B
		if (*maxLoading > *loading) {
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
			pos.x = -24.0f;
			pos.y = -30.0f;
			scale.x += 0.5f / *reloadTime;
			m_sprite.Update(
				pos,
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

	if (ammo <= 0) {
		m_red = 1.0f;
		m_green = 0.0f;
		m_blue = 0.0f;
	}
	else if (*maxLoading / 2 >= *ammo) {
		m_red = 1.0f;
		m_green = 1.0f;
		m_blue = 0.0f;
	}
	else {
		m_red = 1.0f;
		m_green = 1.0f;
		m_blue = 1.0f;
	}


	wchar_t text[256];
	swprintf_s(text, L"%d  /  %d ", *loading, *ammo);
	m_font.Draw(text, { 100.0f, 600.0f }, { m_red, m_green, m_blue, 1.0f });
}
#include "stdafx.h"
#include "Player.h"
#include "Enemy.h"
#include "GameCamera.h"
#include "Bullet.h"

IGunObject::IGunObject()
{
	//GameCamera�̃C���X�^���X��T���B
	m_gameCam = g_goMgr.FindGameObject<GameCamera>(gamecamera);
	//GunGenerator�̃C���X�^���X��T���B
	m_gunGen = g_goMgr.FindGameObject<GunGenerator>(gungenerator);
	//Player�̃C���X�^���X��T���B
	m_player = g_goMgr.FindGameObject<Player>(player);
	//�����[�h�Q�[�W�̃X�v���C�g�����[�h�B
	m_sprite.Init(L"Resource/sprite/gage.dds", 100.0f, 70.0f);
}

IGunObject::~IGunObject()
{
	//�e��T���č폜����B
	g_goMgr.QueryGameObject<Bullet>(bullet, [](Bullet * bul)->bool
		{
			g_goMgr.DeleteGameObject(bul);
			return true;
		});
	//�e���o���^�C�}�[�����Z�b�g�B
	m_putOutTimer = 0;
}

void IGunObject::GunRotation(CQuaternion* rotation)
{
	//�J�����̃^�[�Q�b�g�����B
	CVector3 pos = m_gameCam->GetToTargetPos();
	pos.y = 0.0f;
	//���̉�]�p�x���v�Z�B
	m_angle = CMath::RadToDeg(atan2(pos.x, pos.z));
	//�J�����̃^�[�Q�b�g�����B
	pos = m_gameCam->GetToTargetPos();
	float y = pos.y;
	pos.y = 0.0f;
	float x = pos.Length();
	//�c�̉�]�p�x���v�Z�B
	m_angle2 = CMath::RadToDeg(atan2(-y, x));
	//�e�̉�]������B
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
	//���t���[���AGunUpdate�̏����̑O�ɁA�A�j���[�V�����͉������Ȃ��悤�ɐݒ肵�Ă����B
	m_animationFlug = enAnimationCrip_nothing;
	//�e�̉�]�B
	GunRotation(rotation);
	m_gunGen->SetmAimFlug(false);
	//�G�C���B
	Aim(position, rotation, aimingPos, notAimPos);
	//�e�̃C���^�[�o���^�C�}�[�����Z���Ă����B
	m_bulletIntervalTimer++;
	if (m_bulletIntervalTimer >= *bulletIntervalTime) {
		//�e�̃C���^�[�o���^�C�}�[���e�ɐݒ肳��Ă���C���^�[�o���^�C���ɂȂ�����A
		//�e�̃C���^�[�o���^�C�}�[�ɏe�ɐݒ肳��Ă���C���^�[�o���^�C����������B
		m_bulletIntervalTimer = *bulletIntervalTime;
	}
	//�e�𔭎ˁB
		if (
			g_pad->IsPress(enButtonRB1) &&         //RB1���������B
			m_reloadFlug != true &&                //�����[�h���łȂ��B
			m_player->GetDeathFlug() != true &&    //Player������ł��Ȃ��B
			*loading > 0 &&                        //�e�����c���Ă���B
			m_player->GetStopFlug() != true &&     //�v���C���[���߂܂��Ă��Ȃ��B
			m_gunGen->GetPutAwayFlug() != true &&  //�e�����܂��Ă���Œ��łȂ��B
			m_gunGen->GetPutOutFlug() != true      //�e���o���Ă���Œ��łȂ��B
			) {
			float camearaViewAngle = m_gameCam->GetGameCameraViewAngle();
				if (m_bulletIntervalTimer >= *bulletIntervalTime) {
					//���Ԋu�Œe�𔭎˂���B
					//�e�����������̃C�x���g�֐����Ăяo��
					OnShot(position, rotation);
					m_bullet = g_goMgr.NewGameObject<Bullet>(bullet);
					m_bullet->SetPosition(m_initBulletPos);
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
					//�e�̔��C�t���O��true�ɂ���B
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
				}
		}
		else {
			//�e�̔��C�t���O��false�ɂ���B
			g_goMgr.SetShotFlug(false);
		}


	//�����[�h�B
	if (g_pad->IsTrigger(enButtonX)) {
		//X�{�^�����������B
		if (
			*maxLoading > *loading &&        //���U�e�����ő�łȂ��B
			*ammo > 0 &&                     //�e�����c���Ă���B
			m_gunGen->GetAimFlug() != true   //�G�C�����łȂ��B
			) {
			//�t���O��ݒ肷��B
			m_reloadFlug = true;
			m_gunGen->SetReloadFlug(true);
		}
	}
	if (m_reloadFlug != false) {
		//�����[�h�̃t���O���������B
		//�A�j���[�V������ݒ�B
		m_animationFlug = enAnimationCrip_reload;
		//�^�C�}�[�����Z���Ă����B
		m_reloadTimer++;
		if (m_reloadTimer > *reloadTime) {
			//���U����Ă���e���ő�łȂ��B
			if (*maxLoading - *loading > *ammo) {
				//�c��e�������U�\�e����菭�Ȃ��B
				//�c��̒e���𑕓U����B
				*loading += *ammo;
				*ammo = 0;
			}
			else {
				//�g�����e�����A���U����B
				m_usedBullet = *maxLoading - *loading;
				*loading += m_usedBullet;
				*ammo -= m_usedBullet;
			}
			//�t���O��߂��B
			m_reloadFlug = false;
			m_gunGen->SetReloadFlug(false);
			//�^�C�}�[�����Z�b�g�B
			m_reloadTimer = 0;
		}
	}
	if (m_gunGen->GetPutAwayFlug() != false) {
		//�e�����܂��Ă���Œ��B
		//�A�j���[�V������ݒ�B
		m_animationFlug = enAnimationCrip_putAway;
		//�^�C�}�[�����Z�B
		m_putAwayTimer++;
		if (m_putAwayTimer >= m_putOutAndPutAwayTime) {
			//�e�����܂��A�j���[�V�������I������B
			//�e�����܂��Ă���Œ��̃t���O��false�ɂ���B
			m_gunGen->SetPutAwayFlug(false);
			//�e���o���t���O�𗧂Ă�B
			m_gunGen->SetPutOutFlug(true);
		}
		//if (m_putOutTimer < m_putOutAndPutAwayTime) {
		//	//�e���o���Ă���B
		//	m_animationFlug = enAnimationCrip_putOut;
		//	//�^�C�}�[�����Z�B
		//	m_putOutTimer++;
		//	if (m_putOutTimer >= m_putOutAndPutAwayTime) {
		//		//�e���o���I�����B
		//		//�e���o���Ă���Œ��̃t���O��false�ɂ���B
		//		m_gunGen->SetPutOutFlug(false);
		//	}
		//}
	}
}
void IGunObject::GunPostRender(int* reloadTime, int* ammo, int* loading, int* maxLoading)
{
	if (m_reloadFlug != false) {
		//�����[�h�����B
		if (m_reloadTimer < *reloadTime) {
			//�����[�h���B
			//m_reloadGageScale.x�������Â傫������B
			m_reloadGageScale.x += 0.5f / *reloadTime;
			m_sprite.Update(
				m_reloadGagePos,
				CQuaternion::Identity(),
				m_reloadGageScale,
				{ 0.0f, 0.0f }
			);
			//�`��B
			m_sprite.Draw();
		}
	}
	else {
		//�����[�h���Ă��Ȃ��ꍇ�Am_reloadGageScale.x ��0�ɂ���B
		m_reloadGageScale.x = 0.0f;
	}

	if (ammo < 0) {
		//�e���������Ȃ�ƁA�����̐F��Ԃ�����B
		m_fontRed = 1.0f;
		m_fontGreen = 0.0f;
		m_fontBlue = 0.0f;
	}
	else {
		//�����̐F�𔒂ɂ���B
		m_fontRed = 1.0f;
		m_fontGreen = 1.0f;
		m_fontBlue = 1.0f;
	}

	//�����`��B
	wchar_t text[256];
	swprintf_s(text, L"%d  /  %d ", *loading, *ammo);
	m_font.Draw(
		text,
		m_fontPos,
		{ m_fontRed, m_fontGreen, m_fontBlue, 1.0f }, 
		m_fontScale
	);
}
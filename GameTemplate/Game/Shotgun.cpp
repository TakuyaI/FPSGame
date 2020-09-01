#include "stdafx.h"
#include "Shotgun.h"
#include "GameCamera.h"

Shotgun::Shotgun()
{
	//���f�������[�h�B
	m_model.Init(L"Assets/modelData/shotGun.cmo");
	//���������̉������[�h�B
	m_gunShot.Init(L"Assets/sound/shotgunS.wav");
	//���������̃G�t�F�N�g�����[�h�B
	m_sampleEffect = Effekseer::Effect::Create(
		g_goMgr.GetEffekseerManager(),
		(const EFK_CHAR*)L"Assets/effect/happou.efk"
	);
	
	//�A�j���[�V�����N���b�v�����[�h�B
	m_animationClip[enAnimationCrip_nothing].Load(L"Assets/animData/nothingAnim_shotGun.tka");
	m_animationClip[enAnimationCrip_reload].Load(L"Assets/animData/reload_shotGun.tka");
	//���[�v�t���O��ݒ�B
	m_animationClip[enAnimationCrip_nothing].SetLoopFlag(true);
	m_animationClip[enAnimationCrip_reload].SetLoopFlag(true);

	m_animationClip[enAnimationCrip_putAway].Load(L"Assets/animData/putAwayshotGun.tka");
	m_animationClip[enAnimationCrip_putAway].SetLoopFlag(true);
	m_animationClip[enAnimationCrip_putOut].Load(L"Assets/animData/putOutshotGun.tka");
	m_animationClip[enAnimationCrip_putOut].SetLoopFlag(true);
	//�A�j���[�V�����̏������B
	m_animation.Init(m_model, m_animationClip, enAnimationCrip_num);
	//�e�����擾�B
	m_ammo = m_gunGen->GetGunAmmo();
	//���U�e�����擾�B
	m_loading = m_gunGen->GetGunLoading();
	//�ŏ��͏e�̃C���^�[�o���^�C�}�[��m_bulletIntervalTime�ɂ��Ă����B
	m_bulletIntervalTimer = m_bulletIntervalTime;
}


Shotgun::~Shotgun()
{
	//GunGenerator�ɒe����ۑ��B
	m_gunGen->SetGunAmmo(m_ammo);
	//GunGenerator�ɑ��U�e����ۑ��B
	m_gunGen->SetGunLoading(m_loading);
}

void Shotgun::Update()
{
	//�e�̍X�V�����B
	GunUpdate(
		&m_positon,
		&m_rotation,
		&m_ammo,
		&m_loading,
		&m_maxLoading,
		&m_bulletIntervalTime,
		&m_bulletMoveSpeed,
		&m_reaction,
		&m_reloadTime,
		&m_aimingPos,
		&m_notAimPos
	);
	if (m_putOutTimer < m_putOutAndPutAwayTime) {
		m_animationFlug = enAnimationCrip_putOut;
		m_putOutTimer++;
		if (m_putOutTimer >= m_putOutAndPutAwayTime) {
			m_gunGen->SetPutOutFlug(false);
		}
	}
	//�A�j���[�V�������Đ��B
	m_animation.Play(m_animationFlug);
	//�A�j���[�V�������X�V�B
	m_animation.Update(1.0f / 30.0f);
	m_model.UpdateWorldMatrix(m_positon, m_rotation, m_scale);
}
void Shotgun::SetRegistShadowCaster()
{
	//�V���h�E�L���X�^�[�ɃZ�b�g�B
	g_goMgr.GetShadowMap()->RegistShadowCaster(&m_model);
}
void Shotgun::Render()
{
	//3D�`��B
	m_model.Draw(
		enRenderMode_Normal,
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}
void Shotgun::PostRender()
{
	//2D�`��B
	GunPostRender(
		&m_reloadTime,
		&m_ammo,
		&m_loading,
		&m_maxLoading
	);
}
void Shotgun::OnShot(CVector3* position, CQuaternion* rotation)
{
	//�����Đ��B
	m_gunShot.Stop();
	m_gunShot.Play(false);
	g_goMgr.GetEffekseerManager()->StopEffect(m_playEffectHandle);
	//�Đ��B
	m_initBulletPos = *position;
	CVector3 pos = m_gameCam->GetToTargetPos();
	pos.Normalize();
	m_initBulletPos += pos * 170.0f;

	auto effMgr = g_goMgr.GetEffekseerManager();
	m_playEffectHandle = effMgr->Play(
		m_sampleEffect,
		0.0f,
		0.0f,
		0.0f
	);
	//�J�����̉�]�s������߂�B
	CMatrix mCameraRot;
	//�J�����s��̋t�s��̓J�����̃��[���h�s��B
	mCameraRot.Inverse(g_camera3D.GetViewMatrix());
	//
	mCameraRot.m[3][0] = m_initBulletPos.x;
	mCameraRot.m[3][1] = m_initBulletPos.y;
	mCameraRot.m[3][2] = m_initBulletPos.z;

	Effekseer::Matrix43 effMat;
	for (int x = 0; x < 4; x++) {
		for (int y = 0; y < 3; y++) {
			effMat.Value[x][y] = mCameraRot.m[x][y];
		}
	}

	effMgr->SetBaseMatrix(m_playEffectHandle, effMat);
}
void Shotgun::Aim(CVector3* position, CQuaternion* rotation, CVector3* aimingPos, CVector3* notAimPos)
{
	*position = m_gameCam->GetPosition();
	CQuaternion PosRot = *rotation;
	//��p�B
	float GameCameraViewAngle = m_gameCam->GetGameCameraViewAngle();
	//�G�C�����Ă���Ƃ��̏e�̃��[�J�����W�B
	CVector3 aimPos = *aimingPos;
	//�G�C�����Ă��Ȃ��Ƃ��̏e�̃��[�J�����W�B
	CVector3 notaimPos = *notAimPos;

	if (
		g_pad->IsPress(enButtonLB1) && //LB1�{�^���������Ă���B
		m_reloadFlug != true           //�����[�h���ł͂Ȃ��B
		) {
		//�G�C�����Ă���B
		m_gunGen->SetmAimFlug(true);
		PosRot.Multiply(aimPos);
		PosRot.Multiply(notaimPos);

		//�G�C�����Ă��Ȃ��Ƃ��̏e�̃��[�J�����W����A
		//�G�C�����Ă���Ƃ��̏e�̃��[�J�����W�Ɍ������x�N�g�������߂�B
		m_aimMoveSpeed = aimPos - notaimPos;
		m_aimMoveSpeed /= DIVIDE_NUM;

		if (m_count < (int)DIVIDE_NUM) {
			//m_count��DIVIDE_NUM��菭�Ȃ��Ȃ�ړ�����B
			m_gunLocalPosition += m_aimMoveSpeed;
			//��p����������B
			m_gameCam->SetGameCameraViewAngle(GameCameraViewAngle - 3.0f);
			m_gameCam->SetRotSpeed(1.0f);
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
			PosRot.Multiply(notaimPos);

			m_aimMoveSpeed = aimPos - notaimPos;
			m_aimMoveSpeed /= DIVIDE_NUM;
			m_gunLocalPosition -= m_aimMoveSpeed;
			//��p���L������B�B
			m_gameCam->SetGameCameraViewAngle(GameCameraViewAngle + 3.0f);
			m_gameCam->SetRotSpeed(m_rotSpeed);
			m_count--;
		}
		else {
			m_gunLocalPosition = *notAimPos;
			PosRot.Multiply(m_gunLocalPosition);
		}
	}
	*position += m_gunLocalPosition;
}
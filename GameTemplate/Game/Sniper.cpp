#include "stdafx.h"
#include "Sniper.h"
#include "GameCamera.h"

Sniper::Sniper()
{
	//���f�������[�h�B
	m_model.Init(L"Assets/modelData/sniper_rifle.cmo");
	//���������̉������[�h�B
	m_gunShot.Init(L"Assets/sound/sniperS.wav");
	//���������̃G�t�F�N�g�����[�h�B
	m_sampleEffect = Effekseer::Effect::Create(
		g_goMgr.GetEffekseerManager(),
		(const EFK_CHAR*)L"Assets/effect/happou.efk"
	);
	//�X�R�[�v�̉摜�����[�h�B
	m_aim.Init(L"Resource/sprite/SR_scope.dds", FRAME_BUFFER_W, FRAME_BUFFER_H);
	//2D�`���D�悵�čs���B
	SetPostRenderPriority(true);
	//�e�����擾�B
	m_ammo = m_gunGen->GetGunAmmo();
	//���U�e�����擾�B
	m_loading = m_gunGen->GetGunLoading();
	//�ŏ��͏e�̃C���^�[�o���^�C�}�[��m_bulletIntervalTime�ɂ��Ă����B
	m_bulletIntervalTimer = m_bulletIntervalTime;
}


Sniper::~Sniper()
{
	//GunGenerator�ɒe����ۑ��B
	m_gunGen->SetGunAmmo(m_ammo);
	//GunGenerator�ɑ��U�e����ۑ��B
	m_gunGen->SetGunLoading(m_loading);
}

void Sniper::Update()
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
	m_model.UpdateWorldMatrix(m_positon, m_rotation, m_scale);
}
void Sniper::SetRegistShadowCaster()
{
	//�V���h�E�L���X�^�[�ɃZ�b�g�B
	g_goMgr.GetShadowMap()->RegistShadowCaster(&m_model);
}
void Sniper::Render()
{
	if (m_aimFlug != true) {
		//�G�C�������B
		//3D�`��B
		m_model.Draw(
			enRenderMode_Normal,
			g_camera3D.GetViewMatrix(),
			g_camera3D.GetProjectionMatrix()
		);
	}
}
void Sniper::PostRender()
{
	//2D�`��B
	if (m_aimFlug != false) {
		m_aim.Draw();
	}
	GunPostRender(
		&m_reloadTime,
		&m_ammo,
		&m_loading,
		&m_maxLoading
	);
}
void Sniper::OnShot(CVector3* position, CQuaternion* rotation)
{
	//�����Đ��B
	m_gunShot.Stop();
	m_gunShot.Play(false);
	
	g_goMgr.GetEffekseerManager()->StopEffect(m_playEffectHandle);
	//�Đ��B
	CVector3 p = *position;
	p.y += 5.0f;
	CVector3 effectPos = p;
	CVector3 pos = m_gameCam->GetToTargetPos();
	pos.Normalize();
	effectPos += pos * 250.0f;

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
	mCameraRot.m[3][0] = effectPos.x;
	mCameraRot.m[3][1] = effectPos.y;
	mCameraRot.m[3][2] = effectPos.z;

	Effekseer::Matrix43 effMat;
	for (int x = 0; x < 4; x++) {
		for (int y = 0; y < 3; y++) {
			effMat.Value[x][y] = mCameraRot.m[x][y];
		}
	}

	effMgr->SetBaseMatrix(m_playEffectHandle, effMat);
	
}
void Sniper::Aim(CVector3* position, CQuaternion* rotation, CVector3* aimingPos, CVector3* notAimPos)
{
	*position = m_gameCam->GetPosition();
	CQuaternion PosRot = *rotation;
	m_aimFlug = false;
	//�G�C�����Ă���Ƃ��̏e�̃��[�J�����W�B
	CVector3 aimPos = *aimingPos;
	//�G�C�����Ă��Ȃ��Ƃ��̏e�̃��[�J�����W�B
	CVector3 notaimPos = *notAimPos;

	m_gameCam->SetGameCameraViewAngle(60.0f);

	if (g_pad->IsPress(enButtonLB1)) {
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
			m_gameCam->SetRotSpeed(0.5f);
			m_count++;
		}
		else {
			m_gunLocalPosition = *aimingPos;
			PosRot.Multiply(m_gunLocalPosition);
			m_gameCam->SetGameCameraViewAngle(10.0f);
			m_aimFlug = true;
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
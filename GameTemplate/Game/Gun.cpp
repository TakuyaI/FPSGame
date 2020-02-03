#include "stdafx.h"
#include "Gun.h"
#include "GunGenerator.h"
#include "GameManager.h"

//�e�̏��B
struct GunInformation {
	const int RIFLE_INTERVAL_TIME = 3;     //���C�t���o���b�g�̃C���^�[�o���^�C���B
	const int SHOTGUN_INTERVAL_TIME = 20;  //�V���b�g�K���o���b�g�̃C���^�[�o���^�C���B
	const int SNIPER_INTERVAL_TIME = 30;  //�X�i�C�p�[�o���b�g�̃C���^�[�o���^�C���B
	const float RIFLE_MOVE_SPEED = 200.0f; //���C�t���o���b�g�̑��x�B
	const float SHOTGUN_MOVE_SPEED = 150.0f; //�V���b�g�K���o���b�g�̑��x�B
	const float SNIPER_MOVE_SPEED = 400.0f; //�X�i�C�p�[�o���b�g�̑��x�B
	const int RIFLE_BLAZE = 50;              //���C�t���e�̘A�˒e���B
	const int SHOTGUN_BLAZE = 10;              //�V���b�g�K���e�̘A�˒e���B
	const int SNIPER_BLAZE = 4;              //�X�i�C�p�[�e�̘A�˒e���B
	const float RIFLE_REACTION = 1.0f;    //���C�t���̔����B
	const float SHOTGUN_REACTION = 10.0f;//�V���b�g�K���̔����B
	const float SNIPER_REACTION = 10.0f;//�X�i�C�p�[�̔����B
	const int RIFLE_RELOAD_TIME = 60;  //���C�t���̃����[�h�^�C���B
	const int SHOTGUN_RELOAD_TIME = 120;  //�V���b�g�K���̃����[�h�^�C���B
	const int SNIPER_RELOAD_TIME = 90;  //�X�i�C�p�[�̃����[�h�^�C���B
};
Gun::Gun()
{
	m_sprite.Init(L"Resource/sprite/gage.dds", 100.0f, 70.0f);
	GunInformation gunInf;
	GunNumber gunNum;
	m_gunGen = g_goMgr.FindGameObject<GunGenerator>(gungenerator);
	if (m_gunGen->GetNextNum() == gunNum.RIFLE_NUMBER) {
		m_model.Init(L"Assets/modelData/riful.cmo");
		m_bulletIntervalTime = gunInf.RIFLE_INTERVAL_TIME;
		m_bulletMoveSpeed = gunInf.RIFLE_MOVE_SPEED;
		m_maxBlaze = gunInf.RIFLE_BLAZE;
		m_reaction = gunInf.RIFLE_REACTION;
		m_reloadTime = gunInf.RIFLE_RELOAD_TIME;
	}
	else if (m_gunGen->GetNextNum() == gunNum.SHOTGUN_NUMBER) {
		m_model.Init(L"Assets/modelData/gun2.cmo");
		m_bulletIntervalTime = gunInf.SHOTGUN_INTERVAL_TIME;
		m_bulletMoveSpeed = gunInf.SHOTGUN_MOVE_SPEED;
		m_maxBlaze = gunInf.SHOTGUN_BLAZE;
		m_reaction = gunInf.SHOTGUN_REACTION;
		m_reloadTime = gunInf.SHOTGUN_RELOAD_TIME;
	}
	else if (m_gunGen->GetNextNum() == gunNum.SNIPER_NUMBER) {
		m_model.Init(L"Assets/modelData/sniper.cmo");
		m_bulletIntervalTime = gunInf.SNIPER_INTERVAL_TIME;
		m_bulletMoveSpeed = gunInf.SNIPER_MOVE_SPEED;
		m_maxBlaze = gunInf.SNIPER_BLAZE;
		m_reaction = gunInf.SNIPER_REACTION;
		m_reloadTime = gunInf.SNIPER_RELOAD_TIME;
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

	if (m_reloadFlug != true) {
		//�����[�h���͔��˂ł��Ȃ��B
		//���ˁB
		if (g_pad->IsPress(enButtonRB1)) {
			//RB1���������B
			if (m_ammo > 0 && m_blaze > 0) {
				//�e�����c���Ă���B
				m_bulletIntervalTimer++;
				if (m_bulletIntervalTimer >= m_bulletIntervalTime) {
					//���Ԋu�Œe�𔭎˂���B
					m_bullet = g_goMgr.NewGameObject<Bullet>(bullet);
					m_bullet->SetPosition(m_position);
					CVector3 v = m_gameCam->GetTargetPos() - m_position;
					v.Normalize();
					m_bulletPos = v * m_bulletMoveSpeed;
					m_bullet->SetMoveSpeed(m_bulletPos);
					m_position += v * m_reaction;
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
	}
	

	//�����[�h�B
	if (g_pad->IsTrigger(enButtonY)) {
		//Y�{�^�����������B
		if (m_maxBlaze > m_blaze) {
			m_reloadFlug = true;
		}
	}

	if (m_reloadFlug != false) {
		m_reloadTimer++;
		if (m_reloadTimer > m_reloadTime) {
			//���U����Ă���e���ő�łȂ��B
			if (m_ammo < m_maxBlaze) {
				//�c��e�����ő呕�U�e����菭�Ȃ��B
				//�c��̒e���𑕓U����B
				m_blaze = m_ammo;
				m_reloadFlug = false;
				m_reloadTimer = 0;
			}
			else {
				//�g�����e�����A���U����B
				m_usedBullet = m_maxBlaze - m_blaze;
				m_blaze += m_usedBullet;
				m_reloadFlug = false;
				m_reloadTimer = 0;
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
void Gun::PostRender()
{
	if (m_reloadFlug != false) {
		if (m_reloadTimer < m_reloadTime) {
			pos.x = -24.0f;
			pos.y = -30.0f;
			scale.x += 0.5 / m_reloadTime;
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
}

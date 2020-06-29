#include "stdafx.h"
#include "GameCamera.h"

const float MAX_SHOT_COUNT = 100.0f;//m_shotCount�̍ő�l�B
const float MIN_SHOT_COUNT = 0.0f;//m_shotCount�̍ŏ��l�B
const float RECOIL_UP = -0.5f;//���R�C���̏�̈ړ��ʁB
const float RECOIL_DOWN = 1.0f;//���R�C���̉��̈ړ��ʁB
const float WIDTH_UPPER_LIMIT = 50.0f; //���R�C���̉����̏���B
const float RECOIL_RIGHT_AND_LEFT = 0.5f;//���R�C���̍��E�̈ړ��ʁB
GameCamera::GameCamera()
{
	g_camera3D.SetNear(1.0f);
	g_camera3D.SetFar(10000.0f);
	m_toTargetPos = { 0.0f, 0.0f, 1000.0f };
}


GameCamera::~GameCamera()
{
}

void GameCamera::Recoil()
{
	if (m_shotFlug != false) {
		//�e���������B
		//random�Ƀ����_���ŁA0���P������B
		int random =g_goMgr.Rand(1);
		if (random != 0) {
			//random���P�������B
			if (m_width >= WIDTH_UPPER_LIMIT) {
				//m_width���v���X�̏���ɒB�����̂ŁA�}�C�i�X����B
				m_angle -= RECOIL_RIGHT_AND_LEFT;
				m_width--;
			}
			else {
				//m_width���v���X����B
				m_angle += RECOIL_RIGHT_AND_LEFT;
				m_width++;
			}
		}
		else{//random��0�������B
			if (m_width <= -WIDTH_UPPER_LIMIT) {
				//m_width���}�C�i�X�̏���ɒB�����̂ŁA�v���X����B
				m_angle += RECOIL_RIGHT_AND_LEFT;
				m_width++;
			}
			else {
				//m_width���}�C�i�X����B
				m_angle -= RECOIL_RIGHT_AND_LEFT;
				m_width--;
			}

		}

		//������������B
		m_angle2 += RECOIL_UP;
		m_shotCount += fabsf(RECOIL_UP);
		//�p�b�g���삵���������Am_shotCount���}�C�i�X����B
		m_shotCount -= g_pad->GetRStickYF() * -m_rotSpeed;
		if (m_shotCount >= MAX_SHOT_COUNT) {
			//m_shotCount���ő�l�ɒB�����B
			m_angle2 = g_pad->GetRStickYF() * -m_rotSpeed;
			m_shotCount = MAX_SHOT_COUNT;
		}
	}
	else {//�e�������Ă��Ȃ��B
		m_width = 0.0f;
		//���������������B
		m_angle2 += RECOIL_DOWN;
		m_shotCount -= fabsf(RECOIL_DOWN);
		if (m_shotCount < MIN_SHOT_COUNT) {
			//m_shotCount���ŏ��l�ɒB�����B
			m_angle2 = g_pad->GetRStickYF() * -m_rotSpeed;
			m_shotCount = MIN_SHOT_COUNT;
		}
	}
}

bool GameCamera::Start()
{
	m_player = g_goMgr.FindGameObject<Player>(player);
	CQuaternion pRot = m_player->GetRotation();
	pRot.Multiply(m_toTargetPos);
	return true;
}
void GameCamera::Update()
{
	m_position = m_player->GetPosition();
	CVector3 toCameraPosOld = m_toTargetPos;
	CVector3 cameraOffsetOld = m_cameraOffset;

	if (m_player->GetDeathFlug() != true) {
		//Player������ł��Ȃ��B
		m_angle2 = g_pad->GetRStickYF() * -m_rotSpeed;
		m_angle = g_pad->GetRStickXF() * m_rotSpeed;
	}
	//���R�C���B
	Recoil();

	//Y������̉�]�B
	m_rotation.SetRotationDeg(CVector3::AxisY(), m_angle);
	m_rotation.Multiply(m_toTargetPos);

	m_rotation.Multiply(m_cameraOffset);

	//X������̉�]�B
	CVector3 axisX = CVector3::Zero();
	axisX.Cross(CVector3::AxisY(), m_toTargetPos);
	axisX.Normalize();

	
	m_rotation.SetRotationDeg(axisX, m_angle2);
	m_rotation.Multiply(m_toTargetPos);

	m_rotation.Multiply(m_cameraOffset);
	
	m_position += m_cameraOffset;

	CVector3 cameraForward = m_target - m_position;
	cameraForward.Normalize();
	m_toTarget = cameraForward;
	
	CVector3 toPosDir = m_toTargetPos;
	toPosDir.Normalize();
	if (toPosDir.y < -0.5f) {
		//�J�����������������B
		m_toTargetPos = toCameraPosOld;
		m_cameraOffset = cameraOffsetOld;
		m_shotCount++;
	}
	else if (toPosDir.y > 0.8f) {
		//�J����������������B
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
#include "stdafx.h"
#include "GameCamera.h"



GameCamera::GameCamera()
{
	g_camera3D.SetNear(10.0f);
	g_camera3D.SetFar(10000.0f);
	m_toTargetPos = { 0.0f, 0.0f, 1000.0f };
}


GameCamera::~GameCamera()
{
}

void GameCamera::ToTarget()
{
	m_enemyPos = m_enemy->GetPosition();
	m_enemyPos.y += 100.0f;

	//�J��������G�֌������x�N�g�������߂�B
	CVector3 toEnemyV = m_enemyPos - m_position;
	//�x�N�g���̑傫����100�ɂ���B
	toEnemyV.Normalize();
	toEnemyV *= 100.0f;

	//�J��������^�[�Q�b�g�֌������x�N�g�������߂�B
	CVector3 toTargetV = m_target - m_position;
	//�x�N�g���̑傫����100�ɂ���B
	toTargetV.Normalize();
	toTargetV *= 100.0f;

	//�^�[�Q�b�g����G�֌������x�N�g�������߂�B
	CVector3 tToE = toEnemyV - toTargetV;
	//�^�[�Q�b�g��G�Ɉړ�������B
	float diff = tToE.Length();
	tToE.Normalize();
	m_toTargetPos += tToE * 50.0f;

	//�^�[�Q�b�g�ƓG�̋�����10�ȉ��ɂȂ�����A
	//�G�̍��W���^�[�Q�b�g�ɑ������B
	if (diff <= 15.0f) {
		m_toTargetPos = m_enemyPos - m_position;
	}
}

void GameCamera::Update()
{
	m_position = m_player->GetPosition();
	
	
	if (m_lockOnTargetFlug != true) {
		m_angle2 = g_pad->GetRStickYF() * -2.0f;
		m_angle = g_pad->GetRStickXF() * 2.0f;
	}

		//Y������̉�]�B
		//m_angle = g_pad->GetRStickXF() * 2.0f;
		m_rotation.SetRotationDeg(CVector3::AxisY(), m_angle);
		m_rotation.Multiply(m_toTargetPos);

		m_rotation.Multiply(m_cameraOffset);

		//X������̉�]�B
		//m_angle2 = g_pad->GetRStickYF() * -2.0f;
		CVector3 axisX;
		axisX.Cross(CVector3::AxisY(), m_toTargetPos);
		axisX.Normalize();
		m_rotation.SetRotationDeg(axisX, m_angle2);
		m_rotation.Multiply(m_toTargetPos);

	
	m_rotation.Multiply(m_cameraOffset);
	m_position += m_cameraOffset;


	CVector3 cameraForward = m_target - m_position;
	m_toTarget = cameraForward;
	cameraForward.Normalize();
	//����Y�{�^������������(������)�A�G���^�[�Q�b�g����B
	if (g_pad->IsPress(enButtonLB1)) {
		if (m_enemyGen->GetFlug() != 0) {
			m_lockOnTargetFlug = true;
			/*CVector3 cameraForward = m_target - m_position;
			m_toTarget = cameraForward;
			cameraForward.Normalize();*/

			CVector3 toEnemyDir = m_enemy->GetPosition() - m_position;
			toEnemyDir.Normalize();

			float d = toEnemyDir.Dot(cameraForward);

			float angle = acos(d);

			if (fabsf(angle) < CMath::DegToRad(50.0f)) {
				ToTarget();
			}
		}
		
	}
	else {
		m_lockOnTargetFlug = false;
	}
	
	m_target = m_position + m_toTargetPos;
	
	g_camera3D.SetTarget(m_target);
	g_camera3D.SetPosition(m_position);
	g_camera3D.Update();

}
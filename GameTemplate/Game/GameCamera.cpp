#include "stdafx.h"
#include "GameCamera.h"
#include "GameManager.h"


GameCamera::GameCamera()
{
	g_camera3D.SetNear(10.0f);
	g_camera3D.SetFar(10000.0f);
	m_toTargetPos = { 0.0f, 0.0f, 1000.0f };
	//m_enemyGen = g_goMgr.FindGameObject<EnemyGenerator>(enemygenerator);
	m_enemy = g_goMgr.FindGameObject<Enemy>(enemy);
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
	m_player = g_goMgr.FindGameObject<Player>(player);
	m_position = m_player->GetPosition();
	CVector3 toCameraPosOld = m_toTargetPos;
	CVector3 cameraOffsetOld = m_cameraOffset;
	if (m_lockOnTargetFlug != true) {
		m_angle2 = g_pad->GetRStickYF() * -2.0f;
		m_angle = g_pad->GetRStickXF() * 2.0f;
	}

		//Y������̉�]�B
		m_rotation.SetRotationDeg(CVector3::AxisY(), m_angle);
		m_rotation.Multiply(m_toTargetPos);

		m_rotation.Multiply(m_cameraOffset);

		//X������̉�]�B
		CVector3 axisX;
		axisX.Cross(CVector3::AxisY(), m_toTargetPos);
		axisX.Normalize();
		m_rotation.SetRotationDeg(axisX, m_angle2);
		m_rotation.Multiply(m_toTargetPos);

	
	m_rotation.Multiply(m_cameraOffset);
	m_position += m_cameraOffset;


	CVector3 cameraForward = m_target - m_position;
	cameraForward.Normalize();
	m_toTarget = cameraForward;
	//����Y�{�^������������(������)�A�G���^�[�Q�b�g����B
	if (g_pad->IsPress(enButtonLB1)) {
		m_enemyGen = g_goMgr.FindGameObject<EnemyGenerator>(enemygenerator);
		if (m_enemyGen->GetEnemyOccurrenceFlug() != false) {
			m_enemy = m_enemyGen->GetClosestEnemyToPlayer();
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

	CVector3 toPosDir = m_toTargetPos;
	toPosDir.Normalize();
	if (toPosDir.y < -0.5f) {
		//�J����������������B
		m_toTargetPos = toCameraPosOld;
		m_cameraOffset = cameraOffsetOld;
	}
	else if (toPosDir.y > 0.8f) {
		//�J�����������������B
		m_toTargetPos = toCameraPosOld;
		m_cameraOffset = cameraOffsetOld;
	}

	m_target = m_position + m_toTargetPos;
	
	g_camera3D.SetTarget(m_target);
	g_camera3D.SetPosition(m_position);
	g_camera3D.Update();

}
void GameCamera::Render()
{

}
#include "stdafx.h"
#include "Player.h"


const float PLAYER_CONTROLLER_RADIUS = 150.0f;
const float PLAYER_CONTROLLER_HEIGHT = 200.0f;

Player::Player()
{
	//cmo�t�@�C���̓ǂݍ��݁B
	m_model.Init(L"Assets/modelData/unityChan.cmo");
	m_charaCon.Init(
		PLAYER_CONTROLLER_RADIUS,
		PLAYER_CONTROLLER_HEIGHT,
		m_position
	);
}


Player::~Player()
{
}

void Player::Update()
{
	//���_���璍���_�Ɍ������ĐL�т�x�N�g�������߂�B
	CVector3 cameraDir = m_gameCamera->GetTarget() -
		                 m_gameCamera->GetPosition();
	cameraDir.y = 0.0f;
	//���K���B
	cameraDir.Normalize();

	CVector3 cameraDirX;
	cameraDirX.Cross(
		cameraDir,
		CVector3::AxisY()
	);

	if (g_pad->IsPress(enButtonB)) {
		//B�{�^���������Ń_�b�V������B
		if (m_jumpFlag != true) {
			//�W�����v���̓_�b�V���ł��Ȃ��B
			m_playerSpeed = 40.0f;
		}
	}
	else {
		//��������߂�B
		m_playerSpeed = 20.0f;
	}

	m_moveSpeed.x = 0.0f;
	m_moveSpeed.z = 0.0f;
	m_moveSpeed += cameraDirX * g_pad->GetLStickXF()* -m_playerSpeed;
	m_moveSpeed += cameraDir * g_pad->GetLStickYF()* m_playerSpeed;

	if (g_pad->IsTrigger(enButtonA)) {
		if (m_jumpFlag != true) {
			//m_jumpFlag��0�Ȃ�W�����v�ł���B
			m_moveSpeed.y = 20.0f;
			//m_jumpFlag��1�������āA
			//�󒆂ŃW�����v�ł��Ȃ��悤�ɂ���B
			m_jumpFlag = true;
		}
	}
	m_moveSpeed.y -= 1.0f;
	
	m_position.y += m_moveSpeed.y;
	if (m_position.y <= 0.0f) {
		//Player�̍��W��0�ȉ��ɂȂ�����A
		//�d�͂�0�ɂ���B
		m_moveSpeed.y = 0.0f;
		if (m_jumpFlag != false) {
			m_jumpFlag = false;
		}
	}

	m_position = m_charaCon.Execute(1.0f, m_moveSpeed);

	//���[���h�s��̍X�V�B
	m_model.UpdateWorldMatrix(m_position, CQuaternion::Identity(), CVector3::One() * 1.0f);
	/*m_model.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);*/
}
void Player::Draw()
{
	
}
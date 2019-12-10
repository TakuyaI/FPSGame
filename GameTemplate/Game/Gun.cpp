#include "stdafx.h"
#include "Gun.h"
#include "GameManager.h"


Gun::Gun()
{
	m_model.Init(L"Assets/modelData/riful.cmo");
	//m_pos = { 0.0f, 0.0f, 1000.0f };
	m_bullet = g_goMgr.NewGameObject<Bullet>();
	//m_bullet->SetPosition(m_position);

}


Gun::~Gun()
{
}

void Gun::Update()
{
	

	CVector3 pos = m_gameCam->GetToTargetPos();
	pos.y = 0.0f;
	//pos.Normalize();
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

	CQuaternion q;
	m_Pos = m_gunLocalPosition;
	q.SetRotationDeg(CVector3::AxisY(), m_angle);
	q.Multiply(m_Pos);


	m_position += m_Pos;

	m_model.UpdateWorldMatrix(m_position, m_rotation, CVector3::One());
	m_model.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}

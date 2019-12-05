#include "stdafx.h"
#include "Gun.h"


Gun::Gun()
{
	m_model.Init(L"Assets/modelData/riful.cmo");
	//m_pos = { 0.0f, 0.0f, 1000.0f };
	m_Pos = { 0.0f, 0.0f, 0.0f };
}


Gun::~Gun()
{
}

void Gun::Update()
{
	/*
	m_position = m_player->GetPosition();
	m_position.x += 15.0f;
	m_position.y += 95.0f;

	CVector3 pos;
	pos = m_gc->GetPosition() + m_pos;
	CVector3 pos2;
	pos2 = pos - m_position;


	//XŽ²Žü‚è‚Ì‰ñ“]B
	m_angle2 = g_pad->GetRStickYF() * -2.0f;
	CVector3 axisX;
	axisX.Cross(CVector3::AxisY(), pos2);
	axisX.Normalize();
	rotation.SetRotationDeg(axisX, m_angle2);
	m_rotation.Multiply(rotation);
	//YŽ²Žü‚è‚Ì‰ñ“]B
	m_angle = g_pad->GetRStickXF() * 2.0f;
	rotation.SetRotationDeg(CVector3::AxisY(), m_angle);
	m_rotation.Multiply(rotation);
	
	*/

	//YŽ²Žü‚è‚Ì‰ñ“]B
	m_angle = g_pad->GetRStickXF() * 2.0f;
	m_rot.SetRotationDeg(CVector3::AxisY(), m_angle);
	m_rotation.Multiply(m_rot);

	m_position = m_player->GetPosition() + m_Pos;
	
	/*m_rotation = m_gameCam->GetRotation();*/
	m_model.UpdateWorldMatrix(m_position, m_rotation, CVector3::One());
	m_model.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}

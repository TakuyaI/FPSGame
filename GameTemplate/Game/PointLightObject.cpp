#include "stdafx.h"
#include "PointLightObject.h"


PointLightObject::PointLightObject()
{
	m_model.Init(L"Assets/modelData/pointLightObj.cmo");
}


PointLightObject::~PointLightObject()
{
}

void PointLightObject::Update()
{
	m_model.UpdateWorldMatrix(m_position, CQuaternion::Identity(), CVector3::One());
}
void PointLightObject::Render()
{
	m_model.Draw(
		enRenderMode_Normal,
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}

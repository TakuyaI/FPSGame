#include "stdafx.h"
#include "PointLightObject.h"


PointLightObject::PointLightObject()
{
	//���f�������[�h�B
	m_model.Init(L"Assets/modelData/pointLightObj.cmo");
}


PointLightObject::~PointLightObject()
{
}

void PointLightObject::Update()
{
	m_model.UpdateWorldMatrix(m_position, CQuaternion::Identity(), CVector3::One());
}
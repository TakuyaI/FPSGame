#pragma once
class PointLightObject : public IGameObject
{
public:
	PointLightObject();
	~PointLightObject();
	void Update();
	void Render();

	void SetPosition(CVector3 pos)
	{
		m_position = pos;
	}
	CVector3 GetPosition()
	{
		return m_position;
	}
private:
	SkinModel m_model;
	CVector3 m_position = CVector3::Zero();
};


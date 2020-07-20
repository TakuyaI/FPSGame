#pragma once
class PointLightObject : public IGameObject
{
public:
	/// <summary>
	/// コンストラクタ。
	/// </summary>
	PointLightObject();
	/// <summary>
	/// デストラクタ。
	/// </summary>
	~PointLightObject();
	/// <summary>
	/// 更新関数。
	/// </summary>
	void Update();
	/// <summary>
	/// 座標を設定する。
	/// </summary>
	/// <param name="pos">座標。</param>
	void SetPosition(CVector3 pos)
	{
		m_position = pos;
	}
	/// <summary>
	/// 座標を返す。
	/// </summary>
	/// <returns></returns>
	CVector3 GetPosition()
	{
		return m_position;
	}
private:
	SkinModel m_model;                       //スキンモデル。
	CVector3 m_position = CVector3::Zero();  //座標。
};


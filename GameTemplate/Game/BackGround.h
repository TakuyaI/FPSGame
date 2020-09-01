#pragma once
#include "IGameObject.h"
#include "physics\PhysicsStaticObject.h"
#include "PhysicsGhostObject.h"
class BackGround : public IGameObject
{
public:
	/// <summary>
	/// コンストラクタ。
	/// </summary>
	BackGround();
	/// <summary>
	/// デストラクタ。
	/// </summary>
	~BackGround();
	/// <summary>
	/// スタート関数。
	/// </summary>
	/// <returns></returns>
	bool Start();
	/// <summary>
	/// 更新関数。
	/// </summary>
	void Update();
	/// <summary>
	/// 3D描画。
	/// </summary>
	void Render();
	/// <summary>
	/// 座標を設定する。
	/// </summary>
	/// <param name="position">座標。</param>
	void SetPosition(CVector3 position)
	{
		m_position = position;
	}
	/// <summary>
	/// 座標を返す。
	/// </summary>
	/// <returns></returns>
	CVector3 GetPosition()
	{
		return m_position;
	}
	/// <summary>
	/// 回転を設定する。
	/// </summary>
	/// <param name="rotation">回転。</param>
	void SetRotation(CQuaternion rotation)
	{
		m_rotation = rotation;
	}
	/// <summary>
	/// 回転を返す。
	/// </summary>
	/// <returns></returns>
	CQuaternion GetRotation() 
	{
		return m_rotation;
	}
private:
	//分割したステージの番号。
	enum EStageParts {
		eStageParts_3_1,
		eStageParts_3_2,
		eStageParts_3_3,
		eStageParts_3_4,
		eStateParts_Num,
	};
	SkinModel m_model[eStateParts_Num];                         //スキンモデル。
	CVector3 m_position = CVector3::Zero();                     //座標。
	CQuaternion m_rotation = CQuaternion::Identity();           //回転。
	PhysicsStaticObject m_physicsStaticObject[eStateParts_Num]; //静的物理オブジェクト。
	PhysicsGhostObject m_GhostObj[eStateParts_Num];             //ゴーストオブジェクト。
};


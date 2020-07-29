#pragma once
class Player;
#include "IGameObject.h"
#include "Player.h"
#include "GunGenerator.h"
class GameCamera : public IGameObject
{
public:
	/// <summary>
	/// コンストラクタ。
	/// </summary>
	GameCamera();
	/// <summary>
	/// デストラクタ。
	/// </summary>
	~GameCamera();
	/// <summary>
	/// リコイル。
	/// </summary>
	void Recoil();
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
	/// 注視点の座標を取得。
	/// </summary>
	CVector3 GetTarget()
	{
		return m_target;
	}
	/// <summary>
	/// 視点の座標を取得。
	/// </summary>
	CVector3 GetPosition()
	{
		return m_position;
	}
	CVector3 GetToTargetPos()
	{
		return m_toTargetPos;
	}
	CVector3 GetToTarget()
	{
		return m_toTarget;
	}
	const CQuaternion GetRotation() const
	{
		return m_rotation;
	}
	void SetAngle2(float angle2)
	{
		m_angle2 = angle2;
	}
	float GetAngle2()
	{
		return m_angle2;
	}
	void SetRotSpeed(float speed)
	{
		m_rotSpeed = speed;
	}
	float GetRotSpeed()
	{
		return m_rotSpeed;
	}
	void SetGameCameraViewAngle(float viewAngle)
	{
		m_viewAngle = viewAngle;
	}
	float GetGameCameraViewAngle()
	{
		return m_viewAngle;
	}
	void SetWidthUpperLimit(float widthUpperLimit)
	{
		m_widthUpperLimit = widthUpperLimit;
	}
	float GetWidthUpperLimit()
	{
		return m_widthUpperLimit;
	}
	void SetRecoilRightAndLeft(float recoilRightAndLeft)
	{
		m_recoilRightAndLeft = recoilRightAndLeft;
	}
	float GetRecoilRightAndLeft()
	{
		return m_recoilRightAndLeft;
	}
private:
	Player* m_player;
	GunGenerator* m_gunGen;
	CVector3 m_toTargetPos = { 0.0f, 0.0f, 1000.0f };
	CVector3 m_position = CVector3::Zero();     //視点。
	CVector3 m_target = CVector3::Zero();       //注視点。
	CVector3 m_toTarget = CVector3::Zero();
	float m_angle = 0.0f;                             //回転。
	float m_angle2 = 0.0f;
	CQuaternion m_rotation;
	float m_rotSpeed = 5.0f; //カメラが回転するスピード。
	CVector3 m_cameraOffset = { 0.0f, 150.0f, 0.0f };
	float m_viewAngle = 60.0f;//画角。
	float m_shotCount = 0.0f;//弾を撃った時にカウントする。
	float m_width = 0.0f;//リコイルの横幅。
	float m_widthUpperLimit = 20.0f; //リコイルの横幅の上限。
	float m_recoilRightAndLeft = 0.3f;//リコイルの左右の移動量。
};


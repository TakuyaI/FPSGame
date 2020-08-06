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
	/// 注視点の座標を返す。
	/// </summary>
	CVector3 GetTarget()
	{
		return m_target;
	}
	/// <summary>
	/// 視点の座標を返す。
	/// </summary>
	CVector3 GetPosition()
	{
		return m_position;
	}
	/// <summary>
	/// プレイヤーを原点としたターゲットの座標を返す。
	/// </summary>
	/// <returns></returns>
	CVector3 GetToTargetPos()
	{
		return m_toTargetPos;
	}
	/// <summary>
	/// プレイヤーからターゲットに向かうベクトルを正規化したものを返す。
	/// </summary>
	/// <returns></returns>
	CVector3 GetToTarget()
	{
		return m_toTarget;
	}
	/// <summary>
	/// 回転を返す。
	/// </summary>
	/// <returns></returns>
	const CQuaternion GetRotation()
	{
		return m_rotation;
	}
	/// <summary>
	/// カメラが回転するスピードを設定する。
	/// </summary>
	/// <param name="speed"></param>
	void SetRotSpeed(float speed)
	{
		m_rotSpeed = speed;
	}
	/// <summary>
	/// カメラが回転するスピードを返す。
	/// </summary>
	/// <returns></returns>
	float GetRotSpeed()
	{
		return m_rotSpeed;
	}
	/// <summary>
	/// 画角を設定する。
	/// </summary>
	/// <param name="viewAngle"></param>
	void SetGameCameraViewAngle(float viewAngle)
	{
		m_viewAngle = viewAngle;
	}
	/// <summary>
	/// 画角を返す。
	/// </summary>
	/// <returns></returns>
	float GetGameCameraViewAngle()
	{
		return m_viewAngle;
	}
	/// <summary>
	/// リコイルの左右の移動量を返す。
	/// </summary>
	/// <returns></returns>
	float GetRecoilRightAndLeft()
	{
		return m_recoilRightAndLeft;
	}
private:
	Player* m_player;                                   //プレイヤーのインスタンス。
	GunGenerator* m_gunGen;                             //GunGeneratorのインスタンス。
	CVector3 m_toTargetPos = { 0.0f, 0.0f, 1000.0f };   //プレイヤーを原点としたターゲットの座標
	CVector3 m_position = CVector3::Zero();             //視点。
	CVector3 m_target = CVector3::Zero();               //注視点。
	CVector3 m_toTarget = CVector3::Zero();             //プレイヤーからターゲットに向かうベクトルを正規化したもの。
	CVector3 m_cameraOffset = { 0.0f, 150.0f, 0.0f };   //プレイヤーの座標を軸としたときの、カメラのローカル座標。
	CQuaternion m_rotation;                             //回転。
	float m_angle = 0.0f;                               //横の回転角度。
	float m_angle2 = 0.0f;                              //縦の回転角度。
	float m_rotSpeed = 5.0f;                            //カメラが回転するスピード。
	float m_viewAngle = 60.0f;                          //画角。
	float m_shotCount = 0.0f;                           //弾を撃った時にカウントする。
	float m_width = 0.0f;                               //リコイルの横幅。
	float m_widthUpperLimit = 20.0f;                    //リコイルの横幅の上限。
	float m_recoilRightAndLeft = 0.3f;                  //リコイルの左右の移動量。
};


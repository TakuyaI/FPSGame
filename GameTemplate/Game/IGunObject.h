#pragma once
class GameCamera;
class Bullet;
class GunGenerator;
class Sprite;
class Player;
class Enemy;
#include "IGunObject.h"
#include "IGameObject.h"
#include "GunGenerator.h"
#include "Sprite.h"
#include "FontRender.h"
class IGunObject : public IGameObject
{
public:
	IGunObject();
	~IGunObject();

	/// <summary>
	/// 銃の更新
	/// </summary>
	/// <param name="position">座標</param>
	/// <param name="rotation">回転</param>
	/// <param name="ammo">弾数</param>
	/// <param name="loading">装填弾数</param>
	/// <param name="maxLoading">最大装填弾数</param>
	/// <param name="bulletIntervalTime">弾のインターバル</param>
	/// <param name="bulletMoveSpeed">銃の速度</param>
	/// <param name="reaction">発砲時の反動</param>
	/// <param name="reloadTime">リロードにかかる時間</param>
	/// <param name="aimingPos">エイムしているときの銃のローカル座標</param>
	/// <param name="notAimPos">//エイムしていないときの銃のローカル座標</param>
	void GunUpdate(
		CVector3* position, CQuaternion* rotation,
		int* ammo, int* loading, int* maxLoading, int* bulletIntervalTime,
		float* bulletMoveSpeed, float* reaction, int* reloadTime,
		CVector3* aimingPos, CVector3* notAimPos
		);
	/// <summary>
	///　ポストレンダー。
	/// </summary>
	/// <param name="reloadTime">リロード時間。</param>
	/// <param name="ammo">弾数。</param>
	/// <param name="loading">装填弾数。</param>
	/// <param name="maxLoading">最大装填弾数。</param>
	void GunPostRender(int* reloadTime, int* ammo, int* loading, int* maxLoading);
	/// <summary>
	/// 銃の回転。
	/// </summary>
	/// <param name="rotation">回転。</param>
	void GunRotation(CQuaternion* rotation);
private:
	/// <summary>
	/// 弾を撃った時に呼ばれる関数。
	/// </summary>
	virtual void OnShot(CVector3* position, CQuaternion* rotation) {}
	/// <summary>
	/// エイミング。
	/// </summary>
	virtual void Aim(CVector3* position, CQuaternion* rotation, CVector3* aimingPos, CVector3* notAimaos){}

protected:
	Effekseer::Handle m_playEffectHandle = -1;
	GameCamera* m_gameCam;
	GunGenerator* m_gunGen;

	float m_rotSpeed = 3.0f;
	int m_bulletIntervalTimer = 0;
	const float DIVIDE_NUM = 4.0f; //m_aimMoveSpeedを割る数値。
	CVector3 m_gunLocalPosition = CVector3::Zero();
	CVector3 m_aimMoveSpeed = CVector3::Zero();
	int m_count = 0;

private:
	Player* m_player;
	Enemy* m_enemy;
	Bullet* m_bullet;
	FontRender m_font;

	CVector3 m_bulletPos = CVector3::Zero();
	float m_angle = 0.0f;
	float m_angle2 = 0.0f;
	int m_usedBullet = 0; //使い終えた弾。
	int m_reloadTimer = 0;  //リロードタイマー。
	bool m_reloadFlug = false; //リロードしているかどうか。

	Sprite m_sprite;
	CVector3 m_reloadGagePos = {-24.0f, -30.0f, 0.0f};
	CVector3 scale = { 0.6f, 0.1f, 1.0f };

	float m_red = 0.0f;
	float m_green = 0.0f;
	float m_blue = 0.0f;

	bool m_recoiledFlug = false;//反動を受けたかどうか。
};


#pragma once
class GameCamera;
class Bullet;
class GunGenerator;
class EnemyGenerator;
class Sprite;
class Player;
class Enemy;
#include "IGunObject.h"
#include "IGameObject.h"
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
	/*/// <summary>
	/// エイミング。
	/// </summary>
	/// <param name="position">座標。</param>
	void Aim(CVector3* position, CQuaternion* rotation, CVector3* aimingPos, CVector3* notAimaos);*/
	/// <summary>
	/// 銃の回転。
	/// </summary>
	/// <param name="rotation">回転。</param>
	void GunRotation(CQuaternion* rotation);
	void Update();

	void SetNum(int num)
	{
		m_setNum = num;
	}
	int GetNum()
	{
		return m_setNum;
	}
	int GetAmmo()
	{
		return m_ammo;
	}
	int GetLoading()
	{
		return m_loading;
	}
	bool GetReloadFlug()
	{
		return m_reloadFlug;
	}
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

	const float DIVIDE_NUM = 4.0f; //m_aimMoveSpeedを割る数値。
	CVector3 m_gunLocalPosition = CVector3::Zero();
	CVector3 m_aimMoveSpeed = CVector3::Zero();
	int m_count = 0;

private:
	//SkinModel m_model;
	CSoundSource m_gunShot; //銃声の音。
	Player* m_player;
	Enemy* m_enemy;
	
	Bullet* m_bullet;
	GunGenerator* m_gunGen;
	EnemyGenerator* m_enemyGen;
	FontRender m_font;

	CVector3 m_position = CVector3::Zero();
	CVector3 m_Pos = { 15.0f, -8.0f, 10.0f };
	CVector3 m_bulletPos = CVector3::Zero();
	CQuaternion m_rotation = CQuaternion::Identity();
	float m_angle = 0.0f;
	float m_angle2 = 0.0f;
	int m_bulletIntervalTimer = 0;
	int m_bulletIntervalTime;
	float m_bulletMoveSpeed;
	int m_setNum = 0;
	int m_ammo = 0; //弾数。
	int m_loading = 0;//装填弾数。
	int m_usedBullet = 0; //使い終えた弾。
	int m_maxLoading = 0;//最大装填弾数。
	float m_reaction = 0.0f;   //銃の反動。
	int m_reloadTimer = 0;  //リロードタイマー。
	int m_reloadTime = 0;  //リロードタイム。
	bool m_reloadFlug = false; //リロードしているかどうか。
	bool m_shootingBulletFlug = false; //弾を撃っているかどうか。

	
	
	CVector3 m_effectPos = CVector3::Zero();

	Sprite m_sprite;
	CVector3 pos = CVector3::Zero();
	CVector3 scale = { 0.6f, 0.1f, 1.0f };

	float m_red = 0.0f;
	float m_green = 0.0f;
	float m_blue = 0.0f;

	float sss = 0.0f;

	bool f = false;
};


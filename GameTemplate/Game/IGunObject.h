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
	/// <summary>
	/// コンストラクタ。
	/// </summary>
	IGunObject();
	/// <summary>
	/// デストラクタ。
	/// </summary>
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
	GameCamera* m_gameCam;                              //GameCameraのインスタンス。
	GunGenerator* m_gunGen;                             //GunGeneratorのインスタンス。
	float m_rotSpeed = 3.0f;                            //カメラの回転スピード。
	int m_bulletIntervalTimer = 0;                      //弾を撃つまでのインターバルのタイマー。
	const float DIVIDE_NUM = 4.0f;                      //m_aimMoveSpeedを割る数値。割った後のm_aimMoveSpeedをm_gunLocalPositionに足していく回数。
	CVector3 m_gunLocalPosition = CVector3::Zero();     //カメラを原点とした銃のローカル座標。
	CVector3 m_aimMoveSpeed = CVector3::Zero();         //エイムするときのスピード。
	CVector3 m_initBulletPos = CVector3::Zero();        //弾を撃った時の弾の最初の座標。
	int m_count = 0;                                    //エイムに上限を持たせるためのカウント。
	const enum {
		enAnimationCrip_nothing,   //何もしない。
		enAnimationCrip_reload,    //リロード。
		enAnimationCrip_putOut,    //銃を出す。
		enAnimationCrip_putAway,   //銃をしまう。
		enAnimationCrip_num        //アニメーションクリップの数。
	};
	int m_animationFlug = 0;                            //アニメーションを決めるフラグ。
	bool m_reloadFlug = false;                          //リロードしているかどうか。
	int m_putAwayTimer = 0;                             //銃をしまうまでのタイマー。
	int m_putOutTimer = 0;                              //銃を出すまでのタイマー。
	const int m_putOutAndPutAwayTime = 10;              //銃をしまうまでと銃を出すまでのタイム。
private:
	Player* m_player;                                   //プレイヤーのインスタンス。
	Bullet* m_bullet;                                   //弾のインスタンス。
	FontRender m_font;                                  //装填弾数と弾数を表示している文字。
	CVector3 m_bulletPos = CVector3::Zero();            //弾の座標。
	float m_angle = 0.0f;                               //横の回転角度。
	float m_angle2 = 0.0f;                              //縦の回転角度。
	int m_usedBullet = 0;                               //使い終えた弾。
	int m_reloadTimer = 0;                              //リロードタイマー。
	Sprite m_sprite;                                    //リロードゲージのスプライト。
	CVector3 m_reloadGagePos = {-24.0f, -30.0f, 0.0f};  //リロードゲージのスプライトの座標。
	CVector3 m_reloadGageScale = { 0.6f, 0.1f, 1.0f };  //リロードゲージのスプライトの大きさ。
	DirectX::XMFLOAT2 m_fontPos = { 100.0f, 600.0f };   //文字の座標。
	float m_fontRed = 0.0f;                             //文字の赤の成分。
	float m_fontGreen = 0.0f;                           //文字の緑の成分。
	float m_fontBlue = 0.0f;                            //文字の青の成分。
	float m_fontScale = 1.0f;                           //文字の大きさ。
	bool m_recoiledFlug = false;                        //反動を受けたかどうか。
};


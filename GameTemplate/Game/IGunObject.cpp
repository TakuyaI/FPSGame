#include "stdafx.h"
#include "Player.h"
#include "Enemy.h"
#include "GameCamera.h"
#include "Bullet.h"

IGunObject::IGunObject()
{
	//GameCameraのインスタンスを探す。
	m_gameCam = g_goMgr.FindGameObject<GameCamera>(gamecamera);
	//GunGeneratorのインスタンスを探す。
	m_gunGen = g_goMgr.FindGameObject<GunGenerator>(gungenerator);
	//Playerのインスタンスを探す。
	m_player = g_goMgr.FindGameObject<Player>(player);
	//リロードゲージのスプライトをロード。
	m_sprite.Init(L"Resource/sprite/gage.dds", 100.0f, 70.0f);
}

IGunObject::~IGunObject()
{
	//弾を探して削除する。
	g_goMgr.QueryGameObject<Bullet>(bullet, [](Bullet * bul)->bool
		{
			g_goMgr.DeleteGameObject(bul);
			return true;
		});
	//銃を出すタイマーをリセット。
	m_putOutTimer = 0;
}

void IGunObject::GunRotation(CQuaternion* rotation)
{
	//カメラのターゲットを代入。
	CVector3 pos = m_gameCam->GetToTargetPos();
	pos.y = 0.0f;
	//横の回転角度を計算。
	m_angle = CMath::RadToDeg(atan2(pos.x, pos.z));
	//カメラのターゲットを代入。
	pos = m_gameCam->GetToTargetPos();
	float y = pos.y;
	pos.y = 0.0f;
	float x = pos.Length();
	//縦の回転角度を計算。
	m_angle2 = CMath::RadToDeg(atan2(-y, x));
	//銃の回転させる。
	CQuaternion YRot;
	YRot.SetRotationDeg(CVector3::AxisY(), m_angle);
	CQuaternion XRot;
	XRot.SetRotationDeg(CVector3::AxisX(), m_angle2);
	rotation->Multiply(YRot, XRot);
}

void IGunObject::GunUpdate(
	CVector3* position, CQuaternion* rotation,  
	int* ammo, int* loading, int* maxLoading, int* bulletIntervalTime, 
	float* bulletMoveSpeed, float* reaction, int* reloadTime,
	CVector3* aimingPos, CVector3* notAimPos
){
	//毎フレーム、GunUpdateの処理の前に、アニメーションは何もしないように設定しておく。
	m_animationFlug = enAnimationCrip_nothing;
	//銃の回転。
	GunRotation(rotation);
	m_gunGen->SetmAimFlug(false);
	//エイム。
	Aim(position, rotation, aimingPos, notAimPos);
	//弾のインターバルタイマーを加算していく。
	m_bulletIntervalTimer++;
	if (m_bulletIntervalTimer >= *bulletIntervalTime) {
		//弾のインターバルタイマーが銃に設定されているインターバルタイムになったら、
		//弾のインターバルタイマーに銃に設定されているインターバルタイムを代入する。
		m_bulletIntervalTimer = *bulletIntervalTime;
	}
	//弾を発射。
		if (
			g_pad->IsPress(enButtonRB1) &&         //RB1を押した。
			m_reloadFlug != true &&                //リロード中でない。
			m_player->GetDeathFlug() != true &&    //Playerが死んでいない。
			*loading > 0 &&                        //弾数が残っている。
			m_player->GetStopFlug() != true &&     //プレイヤーが捕まっていない。
			m_gunGen->GetPutAwayFlug() != true &&  //銃をしまっている最中でない。
			m_gunGen->GetPutOutFlug() != true      //銃を出している最中でない。
			) {
			float camearaViewAngle = m_gameCam->GetGameCameraViewAngle();
				if (m_bulletIntervalTimer >= *bulletIntervalTime) {
					//一定間隔で弾を発射する。
					//弾を撃った時のイベント関数を呼び出す
					OnShot(position, rotation);
					m_bullet = g_goMgr.NewGameObject<Bullet>(bullet);
					m_bullet->SetPosition(m_initBulletPos);
					//弾のスピードを設定する。
					CVector3 v = m_gameCam->GetToTarget();
					m_bulletPos = v * *bulletMoveSpeed;
					m_bullet->SetMoveSpeed(m_bulletPos);
					//反動。
					*position += v * *reaction;
					--*loading;
					//反動をうけたので、画角を少し広くする。
					camearaViewAngle += 0.5f;
					m_gameCam->SetGameCameraViewAngle(camearaViewAngle);
					m_recoiledFlug = true;

					m_bulletIntervalTimer = 0;
					//銃の発砲フラグをtrueにする。
					g_goMgr.SetShotFlug(true);
				}
				else {
					if (m_recoiledFlug != false) {
						//前のフレームで反動を受けたので、戻す。
						camearaViewAngle -= 0.5f;
						m_gameCam->SetGameCameraViewAngle(camearaViewAngle);
						//前の反動を受けてから1回しか通らないから、
						//フラグをfalseにする。
						m_recoiledFlug = false;
					}
				}
		}
		else {
			//銃の発砲フラグをfalseにする。
			g_goMgr.SetShotFlug(false);
		}


	//リロード。
	if (g_pad->IsTrigger(enButtonX)) {
		//Xボタンを押した。
		if (
			*maxLoading > *loading &&        //装填弾数が最大でない。
			*ammo > 0 &&                     //弾数が残っている。
			m_gunGen->GetAimFlug() != true   //エイム中でない。
			) {
			//フラグを設定する。
			m_reloadFlug = true;
			m_gunGen->SetReloadFlug(true);
		}
	}
	if (m_reloadFlug != false) {
		//リロードのフラグが立った。
		//アニメーションを設定。
		m_animationFlug = enAnimationCrip_reload;
		//タイマーを加算していく。
		m_reloadTimer++;
		if (m_reloadTimer > *reloadTime) {
			//装填されている弾が最大でない。
			if (*maxLoading - *loading > *ammo) {
				//残り弾数が装填可能弾数より少ない。
				//残りの弾数を装填する。
				*loading += *ammo;
				*ammo = 0;
			}
			else {
				//使った弾数分、装填する。
				m_usedBullet = *maxLoading - *loading;
				*loading += m_usedBullet;
				*ammo -= m_usedBullet;
			}
			//フラグを戻す。
			m_reloadFlug = false;
			m_gunGen->SetReloadFlug(false);
			//タイマーをリセット。
			m_reloadTimer = 0;
		}
	}
	if (m_gunGen->GetPutAwayFlug() != false) {
		//銃をしまっている最中。
		//アニメーションを設定。
		m_animationFlug = enAnimationCrip_putAway;
		//タイマーを加算。
		m_putAwayTimer++;
		if (m_putAwayTimer >= m_putOutAndPutAwayTime) {
			//銃をしまうアニメーションが終わった。
			//銃をしまっている最中のフラグをfalseにする。
			m_gunGen->SetPutAwayFlug(false);
			//銃を出すフラグを立てる。
			m_gunGen->SetPutOutFlug(true);
		}
		//if (m_putOutTimer < m_putOutAndPutAwayTime) {
		//	//銃を出している。
		//	m_animationFlug = enAnimationCrip_putOut;
		//	//タイマーを加算。
		//	m_putOutTimer++;
		//	if (m_putOutTimer >= m_putOutAndPutAwayTime) {
		//		//銃を出し終えた。
		//		//銃を出している最中のフラグをfalseにする。
		//		m_gunGen->SetPutOutFlug(false);
		//	}
		//}
	}
}
void IGunObject::GunPostRender(int* reloadTime, int* ammo, int* loading, int* maxLoading)
{
	if (m_reloadFlug != false) {
		//リロードした。
		if (m_reloadTimer < *reloadTime) {
			//リロード中。
			//m_reloadGageScale.xを少しづつ大ききする。
			m_reloadGageScale.x += 0.5f / *reloadTime;
			m_sprite.Update(
				m_reloadGagePos,
				CQuaternion::Identity(),
				m_reloadGageScale,
				{ 0.0f, 0.0f }
			);
			//描画。
			m_sprite.Draw();
		}
	}
	else {
		//リロードしていない場合、m_reloadGageScale.x を0にする。
		m_reloadGageScale.x = 0.0f;
	}

	if (ammo < 0) {
		//弾数が無くなると、文字の色を赤くする。
		m_fontRed = 1.0f;
		m_fontGreen = 0.0f;
		m_fontBlue = 0.0f;
	}
	else {
		//文字の色を白にする。
		m_fontRed = 1.0f;
		m_fontGreen = 1.0f;
		m_fontBlue = 1.0f;
	}

	//文字描画。
	wchar_t text[256];
	swprintf_s(text, L"%d  /  %d ", *loading, *ammo);
	m_font.Draw(
		text,
		m_fontPos,
		{ m_fontRed, m_fontGreen, m_fontBlue, 1.0f }, 
		m_fontScale
	);
}
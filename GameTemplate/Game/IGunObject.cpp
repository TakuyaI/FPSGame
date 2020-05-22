#include "stdafx.h"
//#include "IGunObject.h"
#include "GunGenerator.h"
#include "GameManager.h"
#include "EnemyGenerator.h"
#include "Player.h"
#include "Enemy.h"
#include "GameCamera.h"
#include "Bullet.h"

IGunObject::IGunObject()
{
	m_gameCam = g_goMgr.FindGameObject<GameCamera>(gamecamera);
	m_gunGen = g_goMgr.FindGameObject<GunGenerator>(gungenerator);
	m_enemyGen = g_goMgr.FindGameObject<EnemyGenerator>(enemygenerator);
	m_player = g_goMgr.FindGameObject<Player>(player);

	m_sprite.Init(L"Resource/sprite/gage.dds", 100.0f, 70.0f);
	//サンプルのエフェクトをロードする。
	m_sampleEffect = Effekseer::Effect::Create(
		g_goMgr.GetEffekseerManager(),
		(const EFK_CHAR*)L"Assets/effect/happou.efk"
	);
	m_gunShot.Init(L"Assets/sound/raifulS.wav");
	
	m_ammo = m_gunGen->GetGunAmmo();
	m_loading = m_gunGen->GetGunLoading();

}

IGunObject::~IGunObject(/*m_blaze m_bulletIntervalTime m_bulletMoveSpeed m_reaction m_ammo m_reloadTime*/)
{
	g_goMgr.GetEffekseerManager()->StopEffect(m_playEffectHandle);
}

void IGunObject::GunUpdate(CVector3* position, CQuaternion* rotation, CVector3* scale, int* ammo, int* loading, int* maxLoading, int* bulletIntervalTime, float* bulletMoveSpeed, float* reaction, int* reloadTime, CSoundSource& gunshot)
{
	//カメラのターゲットを代入。
	CVector3 pos = m_gameCam->GetToTargetPos();
	pos.y = 0.0f;

	m_angle = CMath::RadToDeg(atan2(pos.x, pos.z));// acos(pos.Dot(CVector3::Front())));

	pos = m_gameCam->GetToTargetPos();
	float y = pos.y;
	pos.y = 0.0f;
	float x = pos.Length();
	m_angle2 = CMath::RadToDeg(atan2(-y, x));

	CQuaternion YRot;
	YRot.SetRotationDeg(CVector3::AxisY(), m_angle);
	CQuaternion XRot;
	XRot.SetRotationDeg(CVector3::AxisX(), m_angle2);
	CQuaternion a;
	a.Multiply(YRot, XRot);
	*rotation = a;

	*position = m_gameCam->GetPosition();
	if (m_gameCam->LockOnTargetFlug() != false) {
		m_gunLocalPosition = { 0.0f, -10.0f, 10.0f };
	}
	else {
		m_gunLocalPosition = { 15.0f, -8.0f, 10.0f };
	}
	CQuaternion PosRot;
	m_Pos = m_gunLocalPosition;
	PosRot.SetRotationDeg(CVector3::AxisY(), m_angle);
	PosRot.Multiply(m_gunLocalPosition);
	
	*position += m_gunLocalPosition;

	//弾を発射。
	if (m_reloadFlug != true && m_enemyGen->GetAttackFlug() != true && m_player->GetDeathFlug() != true) {
		//リロード中は発射できないかつ、敵が攻撃していないかつ、Playerが死んでいない。
		//発射。
		if (g_pad->IsPress(enButtonRB1)) {
			//RB1を押した。
			if (*loading > 0) {
				//弾数が残っている。
				m_bulletIntervalTimer++;
				if (m_bulletIntervalTimer >= *bulletIntervalTime) {
					//一定間隔で弾を発射する。
					m_shootingBulletFlug = true;
					m_gunGen->SetShootingBulletFlug(true);
					m_bullet = g_goMgr.NewGameObject<Bullet>(bullet);
					m_bullet->SetPosition(*position);
					CVector3 v = m_gameCam->GetTargetPos() - *position;
					v.Normalize();
					m_bulletPos = v * *bulletMoveSpeed;
					m_bullet->SetMoveSpeed(m_bulletPos);
					*position += v * *reaction;
					--*loading;
					m_bulletIntervalTimer = 0;
					gunshot.Stop();
					gunshot.Play(false);
					
					//再生中のエフェクトを止める。
					g_goMgr.GetEffekseerManager()->StopEffect(m_playEffectHandle);
					//再生。
					CVector3 effectPos = *position;
					pos = m_gameCam->GetToTargetPos();
					pos.Normalize();
					effectPos += pos * 100.0f;

					m_playEffectHandle = g_goMgr.GetEffekseerManager()->Play(
						m_sampleEffect,
						effectPos.x,
						effectPos.y,
						effectPos.z
					);
					
				}
			}
		}
		else {
			m_shootingBulletFlug = false;
			m_gunGen->SetShootingBulletFlug(false);
		}
	}


	//リロード。
	if (g_pad->IsTrigger(enButtonX)) {
		//Xボタンを押した。
		if (*maxLoading > *loading) {
			m_reloadFlug = true;
			m_gunGen->SetReloadFlug(true);
		}
	}

	if (m_reloadFlug != false) {
		m_reloadTimer++;
		if (m_reloadTimer > *reloadTime) {

			//装填されている弾が最大でない。
			if (*maxLoading - *loading > *ammo) {
				//残り弾数が最大装填弾数より少ない。
				//残りの弾数を装填する。
				*loading += *ammo;
				*ammo = 0;
				m_reloadFlug = false;
				m_gunGen->SetReloadFlug(false);
				m_reloadTimer = 0;
			}
			else {

				//使った弾数分、装填する。
				m_usedBullet = *maxLoading - *loading;
				*loading += m_usedBullet;
				*ammo -= m_usedBullet;
				m_reloadFlug = false;
				m_gunGen->SetReloadFlug(false);
				m_reloadTimer = 0;
			}
		}
	}

	//m_model.UpdateWorldMatrix(position, rotation, scale);

}



void IGunObject::Update()
{
}

void IGunObject::GunPostRender(int* reloadTime, int* ammo, int* loading, int* maxLoading)
{
	if (m_reloadFlug != false) {
		if (m_reloadTimer < *reloadTime) {
			pos.x = -24.0f;
			pos.y = -30.0f;
			scale.x += 0.5f / *reloadTime;
			m_sprite.Update(
				pos,
				CQuaternion::Identity(),
				scale,
				{ 0.0f, 0.0f }
			);
			m_sprite.Draw();
		}
	}
	else {
		scale.x = 0.0f;
	}

	if (ammo <= 0) {
		m_red = 1.0f;
		m_green = 0.0f;
		m_blue = 0.0f;
	}
	else if (*maxLoading / 2 >= *ammo) {
		m_red = 1.0f;
		m_green = 1.0f;
		m_blue = 0.0f;
	}
	else {
		m_red = 1.0f;
		m_green = 1.0f;
		m_blue = 1.0f;
	}


	wchar_t text[256];
	swprintf_s(text, L"%d  /  %d ", *loading, *ammo);
	m_font.Draw(text, { 100.0f, 600.0f }, { m_red, m_green, m_blue, 1.0f });
}
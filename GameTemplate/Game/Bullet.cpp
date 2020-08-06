#include "stdafx.h"
#include "Bullet.h"
#include "Enemy.h"
#include "DogEnemy.h"
#include "Game.h"
#include "GameCamera.h"
#include "GunGenerator.h"
//銃の攻撃力。
struct BulletInformation {
	const int RIFLE_BULLET_POWER = 10; //ライフル。
	const int SHOTGUN_BULLET_POWER = 30;//ショットガン。
	const int SNIPER_BULLET_POWER = 60;//スナイパー。
};
Bullet::Bullet()
{
	//GunGeneratorのインスタンスを探す。
	m_gunGen = g_goMgr.FindGameObject<GunGenerator>(gungenerator);
	//Gameのインスタンスを探す。
	m_game = g_goMgr.FindGameObject<Game>(game);
	GunNumber gunNum;
	BulletInformation bulletInf;
	if (m_gunGen->GetGunNum() == gunNum.RIFLE_NUMBER) {
		//銃の番号がライフル。
		//モデルの初期化。
		m_model.Init(L"Assets/modelData/bullet_test.cmo");
		//銃の攻撃力を設定。
		m_bulletPower = bulletInf.RIFLE_BULLET_POWER;
		m_rifle = g_goMgr.FindGameObject<Rifle>(rifle);
		//回転を設定。
		m_rotation = m_rifle->GetRotation();
		//弾の当たり判定を設定。
		m_hitJudgmentRange = m_rifle->GetHitJudgmentRange();
	}
	else if (m_gunGen->GetGunNum() == gunNum.SHOTGUN_NUMBER) {
		//銃の番号がショットガン。
		//モデルの初期化。
		m_model.Init(L"Assets/modelData/shotgun_bullet.cmo");
		//銃の攻撃力を設定。
		m_bulletPower = bulletInf.SHOTGUN_BULLET_POWER;
		m_shotgun = g_goMgr.FindGameObject<Shotgun>(shotgun);
		//回転を設定。
		m_rotation = m_shotgun->GetRotation();
		//弾の当たり判定を設定。
		m_hitJudgmentRange = m_shotgun->GetHitJudgmentRange();

	}
	else if (m_gunGen->GetGunNum() == gunNum.SNIPER_NUMBER) {
		//銃の番号がスナイパー。。
		//モデルの初期化。
		m_model.Init(L"Assets/modelData/sniper_bullet.cmo");
		//銃の攻撃力を設定。
		m_bulletPower = bulletInf.SNIPER_BULLET_POWER;
		m_sniper = g_goMgr.FindGameObject<Sniper>(sniper);
		//回転を設定。
		m_rotation = m_sniper->GetRotation();
		//弾の当たり判定を設定。
		m_hitJudgmentRange = m_sniper->GetHitJudgmentRange();
	}
}


Bullet::~Bullet()
{
}
void Bullet::InitGhost()
{
	//ボックス形状のゴーストを作成する。
	m_GhostObject.CreateBox(
		m_position,	             //座標。
		CQuaternion::Identity(), //回転クォータニオン。
		m_hitJudgmentRange	     //ボックスのサイズ。
	);
}
bool Bullet::Start()
{
	//ゴースト初期化。
	InitGhost();
	//キャラコン初期化。
	m_charaCon.Init(50.0f, 50.0f, m_position);
	return true;
}
void Bullet::CollisionBulletToEnemy()
{
	g_goMgr.QueryGameObject<DogEnemy>(dogenemy, [&](DogEnemy * dogenemy)->bool
	{
		CharacterController& m_chara = *dogenemy->CharaCon();
		bool isContact = false;
		g_physics.ContactTest(m_chara, [&](const btCollisionObject& contactObject) {
			if (m_GhostObject.IsSelf(contactObject) == true) {
				//m_ghostObjectとぶつかった
				int enemyhp = dogenemy->GetEnemyHp();
				//弾の威力に応じたダメージを敵に与える。
				dogenemy->SetEnemyHp(enemyhp - m_bulletPower);
				if (enemyhp <= 0) {
					//敵のHPが0になった。
					//敵を削除。
					dogenemy->SetDeathFlug(true);
				}
				//敵のダメージフラグを設定する。
				dogenemy->SetReceiveDamageFlug(true);
				//敵のエフェクトのベクトルを設定する。
				dogenemy->SetEffectVec(m_moveSpeed);
				//敵に弾の座標を送る。
				dogenemy->SetBulletPos(m_position);
				isContact = true;
			}
		});
		if (isContact) {
			//弾のインスタンスを削除。
			g_goMgr.DeleteGameObject(this);
		}
		return true;
	});
}
void Bullet::CollisionBulletToDogEnemy()
{
	g_goMgr.QueryGameObject<Enemy>(enemy, [&](Enemy * enemy)->bool
		{
			CharacterController& m_chara = *enemy->CharaCon();
			bool isContact = false;
			g_physics.ContactTest(m_chara, [&](const btCollisionObject& contactObject) {
				if (m_GhostObject.IsSelf(contactObject) == true) {
					//m_ghostObjectとぶつかった
					int enemyhp = enemy->GetEnemyHp();
					//弾の威力に応じたダメージを敵に与える。
					enemy->SetEnemyHp(enemyhp - m_bulletPower);
					if (enemyhp <= 0) {
						//敵のHPが0になった。
						//敵を削除。
						enemy->SetDeathFlug(true);
					}
					//敵のダメージフラグを設定する。
					enemy->SetReceiveDamageFlug(true);
					//敵のエフェクトのベクトルを設定する。
					enemy->SetEffectVec(m_moveSpeed);
					//敵に弾の座標を送る。
					enemy->SetBulletPos(m_position);
					isContact = true;
				}
				});
			if (isContact) {
				//弾のインスタンスを削除。
				g_goMgr.DeleteGameObject(this);
			}
			return true;
	});
}
void Bullet::Update()
{
	//タイマーを加算していく。
	//m_lifeTimer++;
	if (
		m_game->GetEndFlug() != false || //ゲームが終了した。
		m_lifeTimer >= m_lifeTime            //タイマーが一定時間たった。
		) {
		//弾を削除。
		g_goMgr.DeleteGameObject(this);
	}
	//弾丸と敵の当たり判定を実行。
	CollisionBulletToEnemy();
	CollisionBulletToDogEnemy();
	//座標を設定。
	m_position = m_charaCon.Execute(1.0f,1, m_moveSpeed);
	//ゴーストの座標を設定。
	m_GhostObject.SetPosition(m_position);
	//ゴーストの回転を設定。
	m_GhostObject.SetRotation(m_rotation);
	m_model.UpdateWorldMatrix(m_position, m_rotation, CVector3::One());
}
void Bullet::Render()
{
	//描画。
	m_model.Draw(
		enRenderMode_Normal,
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}
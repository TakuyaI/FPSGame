#include "stdafx.h"
#include "Bullet.h"
//#include "GameManager.h"
#include "Enemy.h"
#include "DogEnemy.h"
#include "Game.h"
#include "GameCamera.h"
#include "GunGenerator.h"
#include "EnemyGenerator.h"
struct BulletInformation {
	const int RIFLE_BULLET_POWER = 10;
	const int SHOTGUN_BULLET_POWER = 7;
	const int SNIPER_BULLET_POWER = 20;
};
Bullet::Bullet()
{

	m_enemyGen = g_goMgr.FindGameObject<EnemyGenerator>(enemygenerator);
	m_gunGen = g_goMgr.FindGameObject<GunGenerator>(gungenerator);
	m_game = g_goMgr.FindGameObject<Game>(game);
	GunNumber gunNum;
	BulletInformation bulletInf;
	if (m_gunGen->GetNextNum() == gunNum.RIFLE_NUMBER) {
		m_model.Init(L"Assets/modelData/bullet_test.cmo");
		m_bulletPower = bulletInf.RIFLE_BULLET_POWER;
		m_rifle = g_goMgr.FindGameObject<Rifle>(rifle);
		m_rotation = m_rifle->GetRotation();
		m_hitJudgmentRange = m_rifle->GetHitJudgmentRange();
	}
	else if (m_gunGen->GetNextNum() == gunNum.SHOTGUN_NUMBER) {
		m_model.Init(L"Assets/modelData/shotgun_bullet.cmo");
		m_bulletPower = bulletInf.SHOTGUN_BULLET_POWER;
		m_shotgun = g_goMgr.FindGameObject<Shotgun>(shotgun);
		m_rotation = m_shotgun->GetRotation();
		m_hitJudgmentRange = m_shotgun->GetHitJudgmentRange();

	}
	else if (m_gunGen->GetNextNum() == gunNum.SNIPER_NUMBER) {
		m_model.Init(L"Assets/modelData/sniper_bullet.cmo");
		m_bulletPower = bulletInf.SNIPER_BULLET_POWER;
		m_sniper = g_goMgr.FindGameObject<Sniper>(sniper);
		m_rotation = m_sniper->GetRotation();
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
		m_position,	//第一引数は座標。
		CQuaternion::Identity(),		//第二引数は回転クォータニオン。
		m_hitJudgmentRange	//第三引数はボックスのサイズ。
	);
}
bool Bullet::Start()
{
	InitGhost();
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
					dogenemy->SetEffectVec(m_moveSpeed);
					dogenemy->SetBulletPos(m_position);
				}
				dogenemy->SetReceiveDamageFlug(true);
				isContact = true;
			}
		});
		if (isContact) {
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
					enemy->SetReceiveDamageFlug(true);
					enemy->SetEffectVec(m_moveSpeed);
					enemy->SetBulletPos(m_position);
					isContact = true;
				}
				});
			if (isContact) {
				g_goMgr.DeleteGameObject(this);
			}
			return true;
	});
}
void Bullet::Update()
{
	if (m_game->GetEndFlug() != false) {
		g_goMgr.DeleteGameObject(this);
	}
	//弾丸と敵の当たり判定を実行。
	CollisionBulletToEnemy();
	CollisionBulletToDogEnemy();

	m_backGro = g_goMgr.FindGameObject<BackGround>(background);
	
	
	m_position = m_charaCon.Execute(1.0f,1, m_moveSpeed);

	m_GhostObject.SetPosition(m_position);
	m_GhostObject.SetRotation(m_rotation);
	m_model.UpdateWorldMatrix(m_position, m_rotation, CVector3::One());
}
void Bullet::SetRegistShadowCaster()
{
	g_goMgr.GetShadowMap()->RegistShadowCaster(&m_model);
}
void Bullet::Render()
{
	m_model.Draw(
		enRenderMode_Normal,
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}
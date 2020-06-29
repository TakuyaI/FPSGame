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
	const float RIFLE_BULLET_ACCURACY = 100.0f;
	const float SHOTGUN_BULLET_ACCURACY = 200.0f;
	const float SNIPER_BULLET_ACCURACY = 50.0f;
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
		m_bulletAccuracy = bulletInf.RIFLE_BULLET_ACCURACY;
		m_rifle = g_goMgr.FindGameObject<Rifle>(rifle);
		m_rotation = m_rifle->GetRotation();
	}
	else if (m_gunGen->GetNextNum() == gunNum.SHOTGUN_NUMBER) {
		m_model.Init(L"Assets/modelData/shotgun_bullet.cmo");
		m_bulletPower = bulletInf.SHOTGUN_BULLET_POWER;
		m_bulletAccuracy = bulletInf.SHOTGUN_BULLET_ACCURACY;
		m_shotgun = g_goMgr.FindGameObject<Shotgun>(shotgun);
		m_rotation = m_shotgun->GetRotation();

	}
	else if (m_gunGen->GetNextNum() == gunNum.SNIPER_NUMBER) {
		m_model.Init(L"Assets/modelData/sniper_bullet.cmo");
		m_bulletPower = bulletInf.SNIPER_BULLET_POWER;
		m_bulletAccuracy = bulletInf.SNIPER_BULLET_ACCURACY;
		m_sniper = g_goMgr.FindGameObject<Sniper>(sniper);
		m_rotation = m_sniper->GetRotation();

	}
}


Bullet::~Bullet()
{
}
void Bullet::InitGhost()
{
	//�{�b�N�X�`��̃S�[�X�g���쐬����B
	m_GhostObject.CreateBox(
		m_position,	//�������͍��W�B
		CQuaternion::Identity(),		//�������͉�]�N�H�[�^�j�I���B
		{ 50.0f, 50.0f, 500.0f }	//��O�����̓{�b�N�X�̃T�C�Y�B
	);
}
bool Bullet::Start()
{
	InitGhost();
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
				//m_ghostObject�ƂԂ�����
				int enemyhp = dogenemy->GetEnemyHp();
				//�e�̈З͂ɉ������_���[�W��G�ɗ^����B
				dogenemy->SetEnemyHp(enemyhp - m_bulletPower);
				if (enemyhp <= 0) {
					//�G��HP��0�ɂȂ����B
					//�G���폜�B
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
					//m_ghostObject�ƂԂ�����
					int enemyhp = enemy->GetEnemyHp();
					//�e�̈З͂ɉ������_���[�W��G�ɗ^����B
					enemy->SetEnemyHp(enemyhp - m_bulletPower);
					if (enemyhp <= 0) {
						//�G��HP��0�ɂȂ����B
						//�G���폜�B
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
	//�e�ۂƓG�̓����蔻������s�B
	CollisionBulletToEnemy();
	CollisionBulletToDogEnemy();
	
	m_timer++;
	m_position += m_moveSpeed;
	if (m_timer >= 5) {
		g_goMgr.DeleteGameObject(this);
	}
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
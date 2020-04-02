#include "stdafx.h"
#include "Bullet.h"
#include "GameManager.h"
#include "Enemy.h"
#include "Game.h"
#include "GameCamera.h"
#include "GunGenerator.h"
#include "EnemyGenerator.h"
#include "Item.h"
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
	m_gun = g_goMgr.FindGameObject<Gun>(gun);
	GunNumber gunNum;
	BulletInformation bulletInf;
	if (m_gunGen->GetNextNum() == gunNum.RIFLE_NUMBER) {
		m_model.Init(L"Assets/modelData/bullet_test.cmo");
		m_bulletPower = bulletInf.RIFLE_BULLET_POWER;
		m_bulletAccuracy = bulletInf.RIFLE_BULLET_ACCURACY;
	}
	else if (m_gunGen->GetNextNum() == gunNum.SHOTGUN_NUMBER) {
		m_model.Init(L"Assets/modelData/shotgun_bullet.cmo");
		m_bulletPower = bulletInf.SHOTGUN_BULLET_POWER;
		m_bulletAccuracy = bulletInf.SHOTGUN_BULLET_ACCURACY;
	}
	else if (m_gunGen->GetNextNum() == gunNum.SNIPER_NUMBER) {
		m_model.Init(L"Assets/modelData/sniper_bullet.cmo");
		m_bulletPower = bulletInf.SNIPER_BULLET_POWER;
		m_bulletAccuracy = bulletInf.SNIPER_BULLET_ACCURACY;
	}
	InitGhost();
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
void Bullet::Update()
{
	if (m_game->GetEndFlug() != false) {
		g_goMgr.DeleteGameObject(this);
	}
	if (m_enemyGen->GetEnemyOccurrenceFlug() != false) {
		//�G���o�����Ă���B
		//�e�ƈ�ԋ߂��G�B
		m_enemy = m_enemyGen->GetClosestEnemyToBullet(m_position);
		CharacterController& m_chara = *m_enemy->CharaCon();
		CVector3 enemyPos = m_enemy->GetPosition();
		enemyPos.y += 100.0f;
		//�e����G�Ɍ������ĐL�т�x�N�g���B
		CVector3 v = enemyPos - m_position;
		//if (v.Length() <= m_bulletAccuracy) {
		//	
		//	//�e�ƓG�̋��������l�ȉ��ɂȂ����B
		//	int enemyhp = m_enemy->GetEnemyHp();
		//	//�e�̈З͂ɉ������_���[�W��G�ɗ^����B
		//	m_enemy->SetEnemyHp(enemyhp - m_bulletPower);
		//	if (enemyhp <= 0) {
		//		//�G��HP��0�ɂȂ����B
		//		//�G���폜�B
		//		m_enemy->SetDeathFlug(true);
		//		//�c��̐����}�C�i�X����B
		//		m_knockDownEnemyNum = m_game->GetKnockDownEnemyNum();
		//		m_game->SetKnockDownEnemyNum(--m_knockDownEnemyNum);
		//		int enemyNum = m_enemyGen->GetEnemyNumber();
		//		m_enemyGen->SetEnemyNumber(--enemyNum);
		//		int enemyArrayNum = m_enemyGen->GetEnemyArrayNum();
		//		m_enemyGen->SetEnemyArrayNum(--enemyArrayNum);
		//		m_enemyGen->DeleteEnemy();
		//	}
		//	m_enemy->SetReceiveDamageFlug(true);
		//	g_goMgr.DeleteGameObject(this);
		//}
		bool isContact = false;
		g_physics.ContactTest(m_chara, [&](const btCollisionObject& contactObject) {
			if (m_GhostObject.IsSelf(contactObject) == true) {
				//m_ghostObject�ƂԂ�����
				//�e�ƓG�̋��������l�ȉ��ɂȂ����B
				int enemyhp = m_enemy->GetEnemyHp();
				//�e�̈З͂ɉ������_���[�W��G�ɗ^����B
				m_enemy->SetEnemyHp(enemyhp - m_bulletPower);
				if (enemyhp <= 0) {
					//�G��HP��0�ɂȂ����B
					//�G���폜�B
					m_enemy->SetDeathFlug(true);
					//�c��̐����}�C�i�X����B
					m_knockDownEnemyNum = m_game->GetKnockDownEnemyNum();
					m_game->SetKnockDownEnemyNum(--m_knockDownEnemyNum);
					int enemyNum = m_enemyGen->GetEnemyNumber();
					m_enemyGen->SetEnemyNumber(--enemyNum);
					int enemyArrayNum = m_enemyGen->GetEnemyArrayNum();
					m_enemyGen->SetEnemyArrayNum(--enemyArrayNum);
					m_enemyGen->DeleteEnemy();
				}
				m_enemy->SetReceiveDamageFlug(true);
				isContact = true;//g_goMgr.DeleteGameObject(this);
			}
			});
		if (isContact) {
			g_goMgr.DeleteGameObject(this);
		}
	}
	m_timer++;
	m_position += m_moveSpeed;
	if (m_timer >= 5) {
		g_goMgr.DeleteGameObject(this);
	}
	m_GhostObject.SetPosition(m_position);
	m_GhostObject.SetRotation(m_gun->GetRotation());
	m_model.UpdateWorldMatrix(m_position, m_gun->GetRotation(), CVector3::One());

}
void Bullet::Render()
{
	m_model.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}
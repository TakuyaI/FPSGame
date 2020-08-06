#include "stdafx.h"
#include "Bullet.h"
#include "Enemy.h"
#include "DogEnemy.h"
#include "Game.h"
#include "GameCamera.h"
#include "GunGenerator.h"
//�e�̍U���́B
struct BulletInformation {
	const int RIFLE_BULLET_POWER = 10; //���C�t���B
	const int SHOTGUN_BULLET_POWER = 30;//�V���b�g�K���B
	const int SNIPER_BULLET_POWER = 60;//�X�i�C�p�[�B
};
Bullet::Bullet()
{
	//GunGenerator�̃C���X�^���X��T���B
	m_gunGen = g_goMgr.FindGameObject<GunGenerator>(gungenerator);
	//Game�̃C���X�^���X��T���B
	m_game = g_goMgr.FindGameObject<Game>(game);
	GunNumber gunNum;
	BulletInformation bulletInf;
	if (m_gunGen->GetGunNum() == gunNum.RIFLE_NUMBER) {
		//�e�̔ԍ������C�t���B
		//���f���̏������B
		m_model.Init(L"Assets/modelData/bullet_test.cmo");
		//�e�̍U���͂�ݒ�B
		m_bulletPower = bulletInf.RIFLE_BULLET_POWER;
		m_rifle = g_goMgr.FindGameObject<Rifle>(rifle);
		//��]��ݒ�B
		m_rotation = m_rifle->GetRotation();
		//�e�̓����蔻���ݒ�B
		m_hitJudgmentRange = m_rifle->GetHitJudgmentRange();
	}
	else if (m_gunGen->GetGunNum() == gunNum.SHOTGUN_NUMBER) {
		//�e�̔ԍ����V���b�g�K���B
		//���f���̏������B
		m_model.Init(L"Assets/modelData/shotgun_bullet.cmo");
		//�e�̍U���͂�ݒ�B
		m_bulletPower = bulletInf.SHOTGUN_BULLET_POWER;
		m_shotgun = g_goMgr.FindGameObject<Shotgun>(shotgun);
		//��]��ݒ�B
		m_rotation = m_shotgun->GetRotation();
		//�e�̓����蔻���ݒ�B
		m_hitJudgmentRange = m_shotgun->GetHitJudgmentRange();

	}
	else if (m_gunGen->GetGunNum() == gunNum.SNIPER_NUMBER) {
		//�e�̔ԍ����X�i�C�p�[�B�B
		//���f���̏������B
		m_model.Init(L"Assets/modelData/sniper_bullet.cmo");
		//�e�̍U���͂�ݒ�B
		m_bulletPower = bulletInf.SNIPER_BULLET_POWER;
		m_sniper = g_goMgr.FindGameObject<Sniper>(sniper);
		//��]��ݒ�B
		m_rotation = m_sniper->GetRotation();
		//�e�̓����蔻���ݒ�B
		m_hitJudgmentRange = m_sniper->GetHitJudgmentRange();
	}
}


Bullet::~Bullet()
{
}
void Bullet::InitGhost()
{
	//�{�b�N�X�`��̃S�[�X�g���쐬����B
	m_GhostObject.CreateBox(
		m_position,	             //���W�B
		CQuaternion::Identity(), //��]�N�H�[�^�j�I���B
		m_hitJudgmentRange	     //�{�b�N�X�̃T�C�Y�B
	);
}
bool Bullet::Start()
{
	//�S�[�X�g�������B
	InitGhost();
	//�L�����R���������B
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
				//m_ghostObject�ƂԂ�����
				int enemyhp = dogenemy->GetEnemyHp();
				//�e�̈З͂ɉ������_���[�W��G�ɗ^����B
				dogenemy->SetEnemyHp(enemyhp - m_bulletPower);
				if (enemyhp <= 0) {
					//�G��HP��0�ɂȂ����B
					//�G���폜�B
					dogenemy->SetDeathFlug(true);
				}
				//�G�̃_���[�W�t���O��ݒ肷��B
				dogenemy->SetReceiveDamageFlug(true);
				//�G�̃G�t�F�N�g�̃x�N�g����ݒ肷��B
				dogenemy->SetEffectVec(m_moveSpeed);
				//�G�ɒe�̍��W�𑗂�B
				dogenemy->SetBulletPos(m_position);
				isContact = true;
			}
		});
		if (isContact) {
			//�e�̃C���X�^���X���폜�B
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
					//�G�̃_���[�W�t���O��ݒ肷��B
					enemy->SetReceiveDamageFlug(true);
					//�G�̃G�t�F�N�g�̃x�N�g����ݒ肷��B
					enemy->SetEffectVec(m_moveSpeed);
					//�G�ɒe�̍��W�𑗂�B
					enemy->SetBulletPos(m_position);
					isContact = true;
				}
				});
			if (isContact) {
				//�e�̃C���X�^���X���폜�B
				g_goMgr.DeleteGameObject(this);
			}
			return true;
	});
}
void Bullet::Update()
{
	//�^�C�}�[�����Z���Ă����B
	//m_lifeTimer++;
	if (
		m_game->GetEndFlug() != false || //�Q�[�����I�������B
		m_lifeTimer >= m_lifeTime            //�^�C�}�[����莞�Ԃ������B
		) {
		//�e���폜�B
		g_goMgr.DeleteGameObject(this);
	}
	//�e�ۂƓG�̓����蔻������s�B
	CollisionBulletToEnemy();
	CollisionBulletToDogEnemy();
	//���W��ݒ�B
	m_position = m_charaCon.Execute(1.0f,1, m_moveSpeed);
	//�S�[�X�g�̍��W��ݒ�B
	m_GhostObject.SetPosition(m_position);
	//�S�[�X�g�̉�]��ݒ�B
	m_GhostObject.SetRotation(m_rotation);
	m_model.UpdateWorldMatrix(m_position, m_rotation, CVector3::One());
}
void Bullet::Render()
{
	//�`��B
	m_model.Draw(
		enRenderMode_Normal,
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}
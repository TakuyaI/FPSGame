#include "stdafx.h"
#include "Player.h"
#include "GameManager.h"
#include "EnemyGenerator.h"
#include "Enemy.h"

const float PLAYER_CONTROLLER_RADIUS = 30.0f;
const float PLAYER_CONTROLLER_HEIGHT = 200.0f;
void Player::InitGhost()
{
	//�S�[�X�g�̃��C���[�t���[���\����L���ɂ���B
	//PhysicsWorld().SetDebugDrawMode(btIDebugDraw::DBG_DrawWireframe);
	//�{�b�N�X�`��̃S�[�X�g���쐬����B
	m_ghost.CreateBox(
		m_position,	//�������͍��W�B
		CQuaternion::Identity(),		//�������͉�]�N�H�[�^�j�I���B
		{ 500.0f, 500.0f, 500.0f }	//��O�����̓{�b�N�X�̃T�C�Y�B
	);
}

Player::Player()
{
	m_greenSprite.Init(L"Resource/sprite/oamidori.dds", 200.0f, 15.0f);
	m_redSprite.Init(L"Resource/sprite/aka.dds", 200.0f, 15.0f);
	m_hpBlackSprite.Init(L"Resource/sprite/kuro.dds", 200.0f, 17.0f);
	
	m_position.y = 100.0f;

	//cmo�t�@�C���̓ǂݍ��݁B
	m_model.Init(L"Assets/modelData/unityChan.cmo");
	m_charaCon.Init(
		PLAYER_CONTROLLER_RADIUS,
		PLAYER_CONTROLLER_HEIGHT,
		m_position
	);
	InitGhost();
}


Player::~Player()
{
}

void Player::Update()
{
	m_gameCamera = g_goMgr.FindGameObject<GameCamera>(gamecamera);
	//���_���璍���_�Ɍ������ĐL�т�x�N�g�������߂�B
	CVector3 cameraDir = m_gameCamera->GetTarget() -
		                 m_gameCamera->GetPosition();
	cameraDir.y = 0.0f;
	//���K���B
	cameraDir.Normalize();

	CVector3 cameraDirX;
	cameraDirX.Cross(
		cameraDir,
		CVector3::AxisY()
	);

	if (g_pad->IsPress(enButtonB)) {
		//B�{�^���������Ń_�b�V������B
		if (m_jumpFlag != true) {
			//�W�����v���̓_�b�V���ł��Ȃ��B
			m_playerSpeed = 40.0f;
			m_dashFlug = true;
		}
	}
	else {
		//��������߂�B
		m_playerSpeed = 20.0f;
		m_dashFlug = false;
	}
	m_moveSpeed.x = 0.0f;
	m_moveSpeed.z = 0.0f;
	m_moveSpeed += cameraDirX * g_pad->GetLStickXF()* -m_playerSpeed;
	m_moveSpeed += cameraDir * g_pad->GetLStickYF()* m_playerSpeed;

	if (g_pad->IsTrigger(enButtonA)) {
		if (m_jumpFlag != true) {
			//m_jumpFlag��0�Ȃ�W�����v�ł���B
			m_moveSpeed.y = 20.0f;
			//m_jumpFlag��1�������āA
			//�󒆂ŃW�����v�ł��Ȃ��悤�ɂ���B
			m_jumpFlag = true;
		}
	}
	m_moveSpeed.y -= 1.0f;
	
	m_position.y += m_moveSpeed.y;
	if (m_position.y <= -5.0f) {
		//Player�̍��W��0�ȉ��ɂȂ�����A
		//�d�͂�0�ɂ���B
		m_moveSpeed.y = -5.0f;
		if (m_jumpFlag != false) {
			m_jumpFlag = false;
		}
	}

	m_enemyGen = g_goMgr.FindGameObject<EnemyGenerator>(enemygenerator);
	if (m_enemyGen->GetEnemyOccurrenceFlug() != false) {
		//Enemy���o�������B
		m_enemy = g_goMgr.FindGameObject<Enemy>(enemy);
		if (m_enemyGen->GetAttackFlug() != false) {
			//Enemy���U�����Ă����B
			//���܂�Ă��邩��APlayer�͓����Ȃ��B
			m_moveSpeed = CVector3::Zero();
			if (g_pad->IsTrigger(enButtonUp) ||
				g_pad->IsTrigger(enButtonDown) ||
				g_pad->IsTrigger(enButtonLeft) ||
				g_pad->IsTrigger(enButtonRight)) {
				a++;
				if (a >= 10) {
					//Y�{�^����10�񉟂����B
					m_pushAwayFlug = true;
					a = 0;
				}
			}
		}
	}
	flug = false;
	//�L�����N�^�[�ƃS�[�X�g�̂����蔻����s���B
	g_physics.ContactTest(m_charaCon, [&](const btCollisionObject& contactObject) {
		if (m_ghost.IsSelf(contactObject) == true) {
			//m_ghostObject�ƂԂ�����
			flug = true;
		}
		});

	if (m_deathFlug != false) {
		m_moveSpeed = CVector3::Zero();
	}

	m_position = m_charaCon.Execute(1.0f, m_moveSpeed);

	//���[���h�s��̍X�V�B
	m_model.UpdateWorldMatrix(m_position, CQuaternion::Identity(), CVector3::One() * 1.0f);
	
}
void Player::Render()
{
	/*m_model.Draw(
	g_camera3D.GetViewMatrix(),
	g_camera3D.GetProjectionMatrix()
	);*/
}

void Player::PostRender()
{
	{//HP�o�[�B
		m_enemyGen = g_goMgr.FindGameObject<EnemyGenerator>(enemygenerator);
		if (m_greenScale.x <= 0.0f) {
			m_deathFlug = true;
		}
		if (m_enemyGen->GetEnemyOccurrenceFlug() != false) {
			//�G���o�����B
			if (m_damageFlug != false) {
				m_flug = true;
			
				m_greenScale.x -= m_damage;
				m_redDamage += m_damage;
				m_redDamage /= 2.0f;
				m_damage = 0.0f;
				m_damageFlug = false;
			}
			if (m_flug != false) {
				float aa = 0.01;
				m_redScale.x -= aa;
				m_redDamage -= aa;
				if (m_redDamage <= 0.0f) {
					m_flug = false;
				}
			}
		}

		if (m_greenScale.x < m_redScale.x) {
			m_recoveryTimer++;
			if (m_recoveryTimer >= 60) {
				m_greenScale.x += 0.005f;
				m_recoveryTimer = 0;
			}
		}

		//1�Ԍ��̍��Q�[�W�B
		m_hpBlackSprite.Update(
			m_blackGaugePos,
			CQuaternion::Identity(),
			m_blackScale,
			CVector2::Zero()
		);
		//�^�񒆂̐ԃQ�[�W�B
		m_redSprite.Update(
			m_gaugePos,
			CQuaternion::Identity(),
			m_redScale,
			CVector2::Zero()
		);
		//1�ԑO�̗΃Q�[�W
		m_greenSprite.Update(
			m_gaugePos,
			CQuaternion::Identity(),
			m_greenScale,
			CVector2::Zero()
		);

		m_hpBlackSprite.Draw();
		m_redSprite.Draw();
		m_greenSprite.Draw();

	}
	if (flug != false) {
		wchar_t text[256];
		swprintf_s(text, L"%d ", ds);
		m_font.Draw(text, { 0.0f,0.0f }, { 1.0f, 0.0f, 0.0f, 1.0f });
	}
}
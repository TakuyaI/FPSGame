#include "stdafx.h"
#include "Player.h"

const float PLAYER_CONTROLLER_RADIUS = 30.0f;//�v���C���[�̃R���C�_�[�̔��a�B
const float PLAYER_CONTROLLER_HEIGHT = 200.0f;//�v���C���[�̃R���C�_�[�̍����B
const CVector2 GREEN_SPRITE_SIZE = { 200.0f, 15.0f };//HP�o�[�̃X�v���C�g�̃T�C�Y�B
const CVector2 BLACK_SPRITE_SIZE = { 200.0f, 17.0f };//HP�o�[�̌��̃o�[�̃X�v���C�g�̃T�C�Y�B

Player::Player()
{
	//�_���[�W���󂯂��Ƃ��ɕ\�������X�v���C�g�����[�h�B
	m_damageSprite.Init(L"Resource/sprite/damage.dds", FRAME_BUFFER_W, FRAME_BUFFER_H);
	//�_���[�W���󂯂Ă��Ȃ��Ƃ��͕\�����Ȃ��悤�ɂ������̂ŁA
	//���l��0�ɂ��Ă����B
	m_damageSprite.DeltaAlpha(-1.0f);
	//HP�o�[�Ƃ��̌��̃o�[�����[�h�B
	m_greenSprite.Init(L"Resource/sprite/oamidori.dds", GREEN_SPRITE_SIZE.x, GREEN_SPRITE_SIZE.y);
	m_hpBlackSprite.Init(L"Resource/sprite/kuro.dds", BLACK_SPRITE_SIZE.x, BLACK_SPRITE_SIZE.y);
}


Player::~Player()
{
}
bool Player::Start()
{
	//���f�������[�h�B
	m_model.Init(L"Assets/modelData/player.cmo");
	//�L�����R�����������B
	m_charaCon.Init(
		PLAYER_CONTROLLER_RADIUS,
		PLAYER_CONTROLLER_HEIGHT,
		m_position
	);
	return true;
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

	if (g_pad->IsPress(enButtonLB3)) {
		//B�{�^���������Ń_�b�V������B
			m_playerSpeed = 40.0f;
	}
	else {
		//��������߂�B
		m_playerSpeed = 20.0f;
	}
	m_moveSpeed = CVector3::Zero();
	m_moveSpeed += cameraDirX * g_pad->GetLStickXF()* -m_playerSpeed;
	m_moveSpeed += cameraDir * g_pad->GetLStickYF()* m_playerSpeed;

	//�d�͂��󂯂�B
	m_moveSpeed.y -= 1.0f;
	if (m_position.y <= -5.0f) {
		//Player�̍��W��0�ȉ��ɂȂ�����A
		//�d�͂�0�ɂ���B
		m_moveSpeed.y = -5.0f;
	}

	if (m_stopFlug != false) {
		//Enemy���U�����Ă����B
		//���܂�Ă��邩��APlayer�͓����Ȃ��B
		m_moveSpeed = CVector3::Zero();
		float stickX = fabsf(g_pad->GetLStickXF());
		float stickY = fabsf(g_pad->GetLStickYF());
		if (m_moveStickFlug != true) {
			if (stickX >= 0.5f) {
				//�X�e�B�b�N�����E�ɓ��������B
				m_pushAwayNum += stickX;
				m_moveStickFlug = true;
			}
		}
		else {
			if (stickY >= 0.5f) {
				//�X�e�B�b�N���㉺�ɓ��������B
				m_pushAwayNum += stickY;
				m_moveStickFlug = false;
			}
		}
		if (m_pushAwayNum >= 10.0f) {
				//m_pushAwayNum��10�ȏ�ɂȂ����B
				m_pushAwayFlug = true;
				m_stopFlug = false;
				m_pushAwayNum = 0.0f;
		}
	}
	if (m_deathFlug != false) {
		//���S�����瓮���Ȃ��悤�ɂ���B
		m_moveSpeed = CVector3::Zero();
	}
	//�v���C���[�̍��W��ݒ�B
	m_position = m_charaCon.Execute(1.0f,0, m_moveSpeed);

	//���[���h�s��̍X�V�B
	m_model.UpdateWorldMatrix(m_position, m_rotation, CVector3::One() * 0.5f);
	//GameManager�Ƀv���C���[�̍��W�𑗂�B
	g_goMgr.SetPlayerPos(m_position);
	//�v���C���[���Ƃ炷�|�C���g���C�g�̍��W�𑗂�B
	g_goMgr.SetPointLightPos(m_position, 0);
}
void Player::SetRegistShadowCaster()
{
	//�V���h�E�L���X�^�[�ɃZ�b�g�B
	g_goMgr.GetShadowMap()->RegistShadowCaster(&m_model);
}
void Player::Render()
{
	//�`��B
	m_model.Draw(
	enRenderMode_Normal,
	g_camera3D.GetViewMatrix(),
	g_camera3D.GetProjectionMatrix()
	);
}

void Player::PostRender()
{
	{//HP�o�[�B
		if (m_greenScale.x <= 0.0f) {
			//HP��0�ɂȂ����̂Ŏ��S�B
			m_deathFlug = true;
		}
		if (m_damageFlug != false) {
			//�_���[�W���󂯂��B
			m_hpChanges -= m_damage;
			m_damageFlug = false;
		}
		m_greenScale.x += m_hpChanges;
		
		//���̍��Q�[�W�B
		m_hpBlackSprite.Update(
			m_blackGaugePos,
			CQuaternion::Identity(),
			m_blackScale,
			CVector2::Zero()
		);
		//HP���I�[�o�[���Ȃ��悤�ɂ���B
		if (m_greenScale.x >= 1.0f) {
			m_greenScale.x = 1.0f;
		}
		//�O�̗΃Q�[�W
		m_greenSprite.Update(
			m_gaugePos,
			CQuaternion::Identity(),
			m_greenScale,
			CVector2::Zero()
		);
		//�`��B
		m_hpBlackSprite.Draw();
		m_greenSprite.Draw();
		//�_���[�W���󂯂��烿�l���v���X�A�񕜂�����}�C�i�X����K�v������B
		//�Ȃ̂ŁA���l��ψʂ�����֐��ɓ����m_hpChanges�ɑ΂��A�|1����Z����B
		m_hpChanges *= -1.0f;
		m_damageSprite.DeltaAlpha(m_hpChanges);
		//���Z�b�g�B
		m_hpChanges = 0.0f;
		//�`��B
		m_damageSprite.Draw();
	}
}
#include "stdafx.h"
#include "GunGenerator.h"
#include "Rifle.h"
#include "Shotgun.h"
#include "Sniper.h"

const CVector2 SCOPE_SPRITE_SIZE = { 256.0f, 144.0f };
GunGenerator::GunGenerator()
{
	//�e�̏Ə��̉摜�����[�h�B
	m_sprite.Init(L"Resource/sprite/zyuzi.dds", SCOPE_SPRITE_SIZE.x, SCOPE_SPRITE_SIZE.y);
}
GunGenerator::~GunGenerator()
{
	//�e�̃C���X�^���X���폜�B
	g_goMgr.DeleteGameObject(m_gun);
}

int GunGenerator::GetGunAmmo()
{
	GunNumber gunNumber;
	if (m_gunNum == gunNumber.RIFLE_NUMBER) {
		//�e�̔ԍ������C�t���B
		return m_rifleAmmo;
	}
	else if (m_gunNum == gunNumber.SHOTGUN_NUMBER) {
		//�e�̔ԍ����V���b�g�K���B
		return m_shotgunAmmo;
	}
	else if (m_gunNum == gunNumber.SNIPER_NUMBER) {
		//�e�̔ԍ����X�i�C�p�[�B
		return m_sniperAmmo;
	}
}
void GunGenerator::SetGunAmmo(int ammo)
{
	GunNumber gunNumber;
	if (m_beforeGunNum == gunNumber.RIFLE_NUMBER) {
		//�O�̏e�̔ԍ������C�t���B
		m_rifleAmmo = ammo;
	}
	else if (m_beforeGunNum == gunNumber.SHOTGUN_NUMBER) {
		//�O�̏e�̔ԍ����V���b�g�K���B
		m_shotgunAmmo = ammo;
	}
	else if (m_beforeGunNum == gunNumber.SNIPER_NUMBER) {
		//�O�̏e�̔ԍ����X�i�C�p�[�B
		m_sniperAmmo = ammo;
	}
}
int GunGenerator::GetGunLoading()
{
	GunNumber gunNumber;
	if (m_gunNum == gunNumber.RIFLE_NUMBER) {
		//�e�̔ԍ������C�t���B
		return m_rifulLoading;
	}
	else if (m_gunNum == gunNumber.SHOTGUN_NUMBER) {
		//�e�̔ԍ����V���b�g�K���B
		return m_shotgunLoading;
	}
	else if (m_gunNum == gunNumber.SNIPER_NUMBER) {
		//�e�̔ԍ����X�i�C�p�[�B
		return m_sniperLoading;
	}
}
void GunGenerator::SetGunLoading(int loading)
{
	GunNumber gunNumber;
	if (m_beforeGunNum == gunNumber.RIFLE_NUMBER) {
		//�O�̏e�̔ԍ������C�t���B
		m_rifulLoading = loading;
	}
	else if (m_beforeGunNum == gunNumber.SHOTGUN_NUMBER) {
		//�O�̏e�̔ԍ����V���b�g�K���B
		m_shotgunLoading = loading;
	}
	else if (m_beforeGunNum == gunNumber.SNIPER_NUMBER) {
		//�O�̏e�̔ԍ����X�i�C�p�[�B
		m_sniperLoading = loading;
	}
}
bool GunGenerator::Start()
{
	//���C�t���̃C���X�^���X�𐶐��B
	m_gun = g_goMgr.NewGameObject<Rifle>(rifle);
	return true;
}
void GunGenerator::Update()
{
	if (g_pad->IsTrigger(enButtonY)) {
		//Y�{�^���ŏe��؂�ւ���B
		if (
			g_goMgr.GetShotFlug() != true && //�e�𔭎˂��Ă��Ȃ��B
			m_aimFlug != true &&             //�G�C�����Ă��Ȃ��B
			m_reloadFlug != true &&          //�����[�h���Ă��Ȃ��B
			m_PutAwayFlug != true &&         //�e�����܂��Ă���Œ��łȂ��B
			m_PutOutFlug != true             //�e���o���Ă���Œ��łȂ��B
			) {
			//�e�����܂��Ă���t���O�𗧂Ă�B
			m_PutAwayFlug = true;
			m_switchFlug = true;
		}
	}

	if (
		m_switchFlug != false &&   //�e�̐؂�ւ��t���O���������B
		m_PutOutFlug != false      //�e�����܂��I�����B
		) {
		//������O�̏e�̔ԍ���⊮���Ă����B
		m_beforeGunNum = m_gunNum;
		m_gunNum++;
		GunNumber gunNumber;
		if (m_gunNum >= gunNumber.END_NUMBER) {
			//m_nextnum���Ō�̔ԍ��ɗ�����A
			//�ŏ��̔ԍ��ɖ߂��B
			m_gunNum = gunNumber.RIFLE_NUMBER;
		}
		//�e�̃C���X�^���X���폜�B
		g_goMgr.DeleteGameObject(m_gun);
		if (m_gunNum == gunNumber.RIFLE_NUMBER) {
			//���C�t���B
			m_gun = g_goMgr.NewGameObject<Rifle>(rifle);
		}
		else if (m_gunNum == gunNumber.SHOTGUN_NUMBER) {
			//�V���b�g�K���B
			m_gun = g_goMgr.NewGameObject<Shotgun>(shotgun);
		}
		else if (m_gunNum == gunNumber.SNIPER_NUMBER) {
			//�X�i�C�p�[�B
			m_gun = g_goMgr.NewGameObject<Sniper>(sniper);
		}

		m_switchFlug = false;
	 }
}
void GunGenerator::PostRender()
{
	//2D�`��B
	m_sprite.Draw();
}

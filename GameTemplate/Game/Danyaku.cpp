#include "stdafx.h"
#include "Danyaku.h"
#include "Rifle.h"
#include "Shotgun.h"
#include "Sniper.h"
Danyaku::Danyaku()
{
}
Danyaku::~Danyaku()
{
}
void Danyaku::ItemEffects()
{
	//GunGenerator�̃C���X�^���X��T���B
	m_gunGen = g_goMgr.FindGameObject<GunGenerator>(gungenerator);
	GunNumber gunNum;
	int gunAmmo = 0;
	if (m_gunGen->GetGunNum() == gunNum.RIFLE_NUMBER) {
		//���C�t���B
		m_rifle = g_goMgr.FindGameObject<Rifle>(rifle);
		//���̒e����������B
		gunAmmo = m_rifle->GetAmmo();
		//�e�������Z�B
		gunAmmo += m_addBullet;
		//���Z�����e����ݒ肷��B
		m_rifle->SetGunAmmo(gunAmmo);
	}
	else if (m_gunGen->GetGunNum() == gunNum.SHOTGUN_NUMBER) {
		//�V���b�g�K���B
		m_shotGun = g_goMgr.FindGameObject<Shotgun>(shotgun);
		//���̒e����������B
		gunAmmo = m_shotGun->GetAmmo();
		//�e�������Z�B
		gunAmmo += m_addBullet;
		//���Z�����e����ݒ肷��B
		m_shotGun->SetGunAmmo(gunAmmo);
	}
	else if (m_gunGen->GetGunNum() == gunNum.SNIPER_NUMBER) {
		//�X�i�C�p�[�B
		m_sniper = g_goMgr.FindGameObject<Sniper>(sniper);
		//���̒e����������B
		gunAmmo = m_sniper->GetAmmo();
		//�e�������Z�B
		gunAmmo += m_addBullet;
		//���Z�����e����ݒ肷��B
		m_sniper->SetGunAmmo(gunAmmo);
	}
}
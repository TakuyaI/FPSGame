#pragma once
class Sprite;
class Rifle;
class Shotgun;
class Sniper;
class IGunObject;
#include "Sprite.h"
#include "IGameObject.h"
#include "Game.h"
#include "IGunObject.h"
/// <summary>
/// �e�̔ԍ�
/// </summary>
struct GunNumber
{
	const enum {
		RIFLE_NUMBER,    //���C�t���̔ԍ��B
		SHOTGUN_NUMBER,  //�V���b�g�K���̔ԍ��B
		SNIPER_NUMBER,   //�X�i�C�p�[�̔ԍ��B
		END_NUMBER       //�Ō�̔ԍ��B
	};
};
class GunGenerator : public IGameObject
{
public:
	/// <summary>
	/// �R���X�g���N�^�B
	/// </summary>
	GunGenerator();
	/// <summary>
	/// �f�X�g���N�^�B
	/// </summary>
	~GunGenerator();
	/// <summary>
	/// �e�̒e����Ԃ��B
	/// </summary>
	/// <returns></returns>
	int GetGunAmmo();
	/// <summary>
	/// �e�̒e����ݒ�B
	/// </summary>
	/// <param name="ammo">�e���B</param>
	void SetGunAmmo(int ammo);
	/// <summary>
	/// �e�̑��U�e����Ԃ��B
	/// </summary>
	/// <returns></returns>
	int GetGunLoading();
	/// <summary>
	/// �e�̑��U�e����ݒ�B 
	/// </summary>
	/// <param name="loading">���U�e���B</param>
	void SetGunLoading(int loading);
	/// <summary>
	/// �e�̔ԍ���Ԃ��B
	/// </summary>
	/// <returns></returns>
	int GetGunNum()
	{
		return m_gunNum;
	}
	/// <summary>
	/// �����[�h�������ǂ����̃t���O��ݒ肷��B
	/// </summary>
	/// <param name="flug">�t���O�B</param>
	void SetReloadFlug(bool flug)
	{
		m_reloadFlug = flug;
	}
	/// <summary>
	/// �e�������Ă��邩�ǂ����̃t���O��ݒ肷��B
	/// </summary>
	/// <param name="flug">�t���O�B</param>
	void SetShootingBulletFlug(bool flug)
	{
		m_shootingBulletFlug = flug;
	}
	/// <summary>
	/// �G�C�������ǂ����̃t���O��ݒ肷��B
	/// </summary>
	/// <param name="flug">�t���O�B</param>
	void SetmAimFlug(bool flug)
	{
		m_aimFlug = flug;
	}
	/// <summary>
	/// �G�C�������ǂ����̃t���O��Ԃ��B
	/// </summary>
	/// <returns></returns>
	bool GetAimFlug()
	{
		return m_aimFlug;
	}
	/// <summary>
	/// �X�^�[�g�֐��B
	/// </summary>
	/// <returns></returns>
	bool Start();
	/// <summary>
	/// �X�V�֐��B
	/// </summary>
	void Update();
	/// <summary>
	/// 2D�`��B
	/// </summary>
	void PostRender();
private:
	IGunObject* m_gun;                    //IGunObject�̃C���X�^���X�B
	Game * m_game;                        //Game�̃C���X�^���X�B
	int m_gunNum = 0;                     //�e�̔ԍ��B
	int m_beforeGunNum = 0;               //�O�̏e�̔ԍ��B
	int  m_rifleAmmo = 200;               //���C�t���̒e���B
	int  m_shotgunAmmo = 30;              //�V���b�g�K���̒e���B
	int  m_sniperAmmo = 20;               //�X�i�C�p�[�̒e���B
	int m_rifulLoading = 50;              //���C�t���̑��U�e���B
	int m_shotgunLoading = 2;            //�V���b�g�K���̑��U�e���B  
	int m_sniperLoading = 4;              //�X�i�C�p�[�̑��U�e���B
	bool m_reloadFlug = false;            //�����[�h�������ǂ����B
	bool m_shootingBulletFlug = false;    //�e�������Ă��邩�ǂ����B
	bool m_aimFlug = false;               //�G�C�������ǂ����B
	Sprite m_sprite;                      //
};


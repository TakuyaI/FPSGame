#pragma once
class Gun;
class GameCamera;
#include "IGameObject.h"
/// <summary>
/// �e�̔ԍ�
/// </summary>
struct GunNumber
{
	const enum {
		RIFLE_NUMBER,
		SHOTGUN_NUMBER,
		SNIPER_NUMBER,
		END_NUMBER
	};
};

class GunGenerator : public IGameObject
{
public:
	GunGenerator();
	~GunGenerator();
	/// <summary>
	/// �e�̒e���B
	/// </summary>
	/// <returns></returns>
	int GetGunAmmo();
	/// <summary>
	/// �e�̘A�˒e���B
	/// </summary>
	/// <returns></returns>
	int GetGunBlaze();
	void SetNextNum(int num)
	{
		m_nextnum = num;
	}
	int GetNextNum()
	{
		return m_nextnum;
	}
	void Update();

	Gun* m_gun;
	GameCamera* m_gameCam;
	int m_nextnum = 0;
	bool a = false;
	int  m_rifleAmmo = 200;             //���C�t���̒e���B
	int  m_shotgunAmmo = 60;           //�V���b�g�K���̒e���B
	int  m_sniperAmmo = 20;             //�X�i�C�p�[�̒e���B
	int m_rifulBlaze = 50;              //���C�t���̘A�˒e���B
	int m_shotgunBlaze = 10;            //�V���b�g�K���̘A�˒e���B  
	int m_sniperBlaze = 4;              //�X�i�C�p�[�̘A�˒e���B
};


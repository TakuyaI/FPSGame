#pragma once
#include "ItemObject.h"
#include "GunGenerator.h"


class Danyaku : public IItemObject
{
public:
	/// <summary>
	/// �R���X�g���N�^�B
	/// </summary>
	Danyaku();
	/// <summary>
	/// �f�X�g���N�^�B
	/// </summary>
	~Danyaku();
	/// <summary>
	/// �A�C�e�����ʁB
	/// </summary>
	void ItemEffects();
private:
	GunGenerator * m_gunGen;                            //GunGenerator�̃C���X�^���X�B
	Rifle* m_rifle;                                    //Rifle�̃C���X�^���X�B
	Shotgun* m_shotGun;                                //Shotgun�̃C���X�^���X�B
	Sniper* m_sniper;                                  //Sniper�̃C���X�^���X�B
	const int m_addBullet = 20;                        //���Z����e���B
};


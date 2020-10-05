#pragma once
#include "IItemObject.h"
#include "ItemObject.h"
#include "Player.h"
class Kaihuku : public IItemObject
{
public:
	/// <summary>
	/// �R���X�g���N�^�B
	/// </summary>
	Kaihuku();
	/// <summary>
	/// �f�X�g���N�^�B
	/// </summary>
	~Kaihuku();
	/// <summary>
	/// �A�C�e�����ʁB
	/// </summary>
	void ItemEffects();
private:
	Player* m_player;                 //�v���C���[�̃C���X�^���X�B
	const float m_kaihukuryou = 0.2f; //�񕜗ʁB�v���C���[��HP��1��100%�Ƃ����Ƃ��̐��l�B
};


#pragma once
class ItemGenerator;
#include "Player.h"
#include "Game.h"
#include "ItemGenerator.h"
class ItemObject : public IGameObject
{
public:
	/// <summary>
	/// �R���X�g���N�^�B
	/// </summary>
	ItemObject();
	/// <summary>
	/// �f�X�g���N�^�B
	/// </summary>
	~ItemObject();
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
	/// 3D�`��B
	/// </summary>
	void Render();
	/// <summary>
	/// ���W��ݒ肷��B
	/// </summary>
	/// <param name="pos">���W�B</param>
	void SetPosition(CVector3 pos)
	{
		m_position = pos;
	}
	/// <summary>
	/// ���W��Ԃ��B
	/// </summary>
	/// <returns></returns>
	CVector3 GetPosition()
	{
		return m_position;
	}
private:
	Player* m_player;                         //�v���C���[�̃C���X�^���X�B
	Game* m_game;                             //Game�̃C���X�^���X�B
	ItemGenerator* m_itemGen;                 //ItemGenerator�̃C���X�^���X�B
	SkinModel m_model;                        //�X�L�����f���B
	//�A�C�e���̔ԍ��B
	const enum {
		danyaku, //�e��B
		kaihuku, //�񕜖�B
		itemnum  //�A�C�e���̎�ށB
	};
	CVector3 m_position = CVector3::Zero();   //���W�B
	int m_itemNumber = 0;                     //�A�C�e���̔ԍ��B
	float m_getItemRange = 200.0f;            //�A�C�e�����Q�b�g�ł���͈́B
	
};


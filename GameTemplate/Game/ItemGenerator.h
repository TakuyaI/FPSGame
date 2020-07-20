#pragma once
class Danyaku;
class Kaihuku;
#include "IGameObject.h"
#include "Sprite.h"
#include "IItemObject.h"
#include "Danyaku.h"
#include "Kaihuku.h"
#include "FontRender.h"

class ItemGenerator : public IGameObject
{
public:
	/// <summary>
	/// �R���X�g���N�^�B
	/// </summary>
	ItemGenerator();
	/// <summary>
	/// �f�X�g���N�^�B
	/// </summary>
	~ItemGenerator();
	/// <summary>
	/// �X�V�֐��B
	/// </summary>
	void Update();
	/// <summary>
	/// 2D�`��B
	/// </summary>
	void PostRender();
	/// <summary>
	/// �A�C�e�����l���������ǂ����B
	/// </summary>
	/// <param name="flug">�t���O</param>
	/// <param name="item">�A�C�e��</param>
	void GetItem(bool* flug, IItemObject* item);
	/// <summary>
	/// �\������A�C�e����I�Ԋ֐��B
	/// </summary>
	void SelectItem();
	/// <summary>
	/// �A�C�e�����g�����ǂ����B
	/// </summary>
	void UseItem();
	/// <summary>
	/// �񕜖���擾�������ǂ����̃t���O��ݒ肷��B
	/// </summary>
	/// <param name="flug">�t���O</param>
	void SetKaihukuyakuFkug(bool flug)
	{
		m_getKaihukuyakuFlug = flug;
	}
	/// <summary>
	/// �e����擾�������ǂ����̃t���O��ݒ肷��B
	/// </summary>
	/// <param name="flug">�t���O</param>
	void SetDanyakuFkug(bool flug)
	{
		m_getDanyakuFlug = flug;
	}
	
private:
	Danyaku* m_danyaku;                                           //�e��̃C���X�^���X�B
	Kaihuku* m_kaihuku;                                           //�񕜖�̃C���X�^���X�B
	static const int m_maxHaveNum = 30;                           //�����ł���A�C�e���̍ő吔�B
	IItemObject* m_getItemList[m_maxHaveNum] = { nullptr };       //IItemObject�̔z��B
	int m_stateNumber = 0;                                        //�\�������A�C�e���̔ԍ��B
	int m_stateNum = 0;                                           //�\�������A�C�e���̌��B
	Sprite m_itemTex;                                             //�A�C�e���̈�ԉ��̃e�N�X�`���B
	Sprite m_danyakuTex;                                          //�e��̃e�N�X�`���B
	Sprite m_kaihukuyakuTex;                                      //�񕜖�̃e�N�X�`���B
	CVector3 m_position = { 0.0f, -250.0f, 0.0f };                //�e�N�X�`���̍��W�B
	bool m_getKaihukuyakuFlug = false;                            //�񕜖���擾�������ǂ����B
	bool m_getDanyakuFlug = false;                                //�e����擾�������ǂ����B
	bool m_pushLB2Flug = false;                                   //LB2�{�^���������Ă��邩�ǂ����B
	bool m_pushRB2Flug = false;                                   //RB2�{�^���������Ă��邩�ǂ����B
	FontRender m_itemNumFont;                                     //�A�C�e���̌���\�����镶���B
	DirectX::XMFLOAT2 m_fontPos = { 628.0f, 653.0f };             //�����̍��W�B
	DirectX::FXMVECTOR m_fontColor = { 1.0f, 1.0f, 1.0f, 1.0f };  //�����̐F�B
	float m_fontSize = 0.7f;                                      //�����̃T�C�Y�B
};


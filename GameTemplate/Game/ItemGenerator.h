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
	void GetItem(bool* flug, IItemObject* item, wchar_t* name);
	/// <summary>
	/// �\������A�C�e����I�Ԋ֐��B
	/// </summary>
	void SelectItem();
	/// <summary>
	/// �A�C�e�����g�����ǂ����B
	/// </summary>
	void UseItem();
	/// <summary>
	/// �A�C�e����\������֐��B
	/// </summary>
	/// <param name="sprite">�\������A�C�e���̃X�v���C�g�B</param>
	/// <param name="item">�\������A�C�e���̃C���X�^���X�B</param>
	void FontItem(Sprite& sprite, IItemObject* item);
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
	Danyaku * m_danyaku;                                           //�e��̃C���X�^���X�B
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
	CVector2 m_itemNumFontPos = { 628.0f, 653.0f };               //�����̍��W�B
	CVector4 m_fontColor = { 1.0f, 1.0f, 1.0f, 1.0f };            //�����̐F�B
	float m_fontSize = 0.7f;                                      //�����̃T�C�Y�B
	static const int m_maxFontItemNum = 10;                       //�A�C�e���Q�b�g�̃t�H���g��\���ł���ő�l�B
	FontRender m_getFontItem[m_maxFontItemNum];                   //�A�C�e���Q�b�g�̃t�H���g�B
	CVector2 m_initFontPos = { -200.0f, 500.0f };                 //�A�C�e���Q�b�g�̃t�H���g�̏����l�B
	CVector2 m_fontPos[m_maxFontItemNum];                         //�A�C�e���Q�b�g�̃t�H���g�̍��W�B
	int m_DisplayingNum = 0;                                      //�A�C�e���Q�b�g�̃t�H���g��\�����Ă��鐔�B
	int m_timerY[m_maxFontItemNum] = { 0 };                       //�A�C�e���Q�b�g�̃t�H���g��Y�����ֈړ�����Ƃ��Ɏg���^�C�}�[�B
	int m_timerX[m_maxFontItemNum] = { 0 };                       //�A�C�e���Q�b�g�̃t�H���g��X�����ֈړ�����Ƃ��Ɏg���^�C�}�[�B
	wchar_t* m_itemName[m_maxFontItemNum];                        //�Q�b�g�����A�C�e���̖��O�B
	CVector4 m_getItemaFontColor = { 1.0f, 1.0f, 1.0f , 1.0f };   //�A�C�e���Q�b�g�̃t�H���g�̐F�B
	float m_getItemaFontScale = 0.5f;                             //�A�C�e���Q�b�g�̃t�H���g�̃T�C�Y�B
};


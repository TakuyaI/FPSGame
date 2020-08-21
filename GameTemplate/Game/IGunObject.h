#pragma once
class GameCamera;
class Bullet;
class GunGenerator;
class Sprite;
class Player;
class Enemy;
#include "IGunObject.h"
#include "IGameObject.h"
#include "GunGenerator.h"
#include "Sprite.h"
#include "FontRender.h"
class IGunObject : public IGameObject
{
public:
	/// <summary>
	/// �R���X�g���N�^�B
	/// </summary>
	IGunObject();
	/// <summary>
	/// �f�X�g���N�^�B
	/// </summary>
	~IGunObject();
	/// <summary>
	/// �e�̍X�V
	/// </summary>
	/// <param name="position">���W</param>
	/// <param name="rotation">��]</param>
	/// <param name="ammo">�e��</param>
	/// <param name="loading">���U�e��</param>
	/// <param name="maxLoading">�ő呕�U�e��</param>
	/// <param name="bulletIntervalTime">�e�̃C���^�[�o��</param>
	/// <param name="bulletMoveSpeed">�e�̑��x</param>
	/// <param name="reaction">���C���̔���</param>
	/// <param name="reloadTime">�����[�h�ɂ����鎞��</param>
	/// <param name="aimingPos">�G�C�����Ă���Ƃ��̏e�̃��[�J�����W</param>
	/// <param name="notAimPos">//�G�C�����Ă��Ȃ��Ƃ��̏e�̃��[�J�����W</param>
	void GunUpdate(
		CVector3* position, CQuaternion* rotation,
		int* ammo, int* loading, int* maxLoading, int* bulletIntervalTime,
		float* bulletMoveSpeed, float* reaction, int* reloadTime,
		CVector3* aimingPos, CVector3* notAimPos
		);
	/// <summary>
	///�@�|�X�g�����_�[�B
	/// </summary>
	/// <param name="reloadTime">�����[�h���ԁB</param>
	/// <param name="ammo">�e���B</param>
	/// <param name="loading">���U�e���B</param>
	/// <param name="maxLoading">�ő呕�U�e���B</param>
	void GunPostRender(int* reloadTime, int* ammo, int* loading, int* maxLoading);
	/// <summary>
	/// �e�̉�]�B
	/// </summary>
	/// <param name="rotation">��]�B</param>
	void GunRotation(CQuaternion* rotation);
private:
	/// <summary>
	/// �e�����������ɌĂ΂��֐��B
	/// </summary>
	virtual void OnShot(CVector3* position, CQuaternion* rotation) {}
	/// <summary>
	/// �G�C�~���O�B
	/// </summary>
	virtual void Aim(CVector3* position, CQuaternion* rotation, CVector3* aimingPos, CVector3* notAimaos){}

protected:
	Effekseer::Handle m_playEffectHandle = -1;
	GameCamera* m_gameCam;                              //GameCamera�̃C���X�^���X�B
	GunGenerator* m_gunGen;                             //GunGenerator�̃C���X�^���X�B
	float m_rotSpeed = 3.0f;                            //�J�����̉�]�X�s�[�h�B
	int m_bulletIntervalTimer = 0;                      //�e�����܂ł̃C���^�[�o���̃^�C�}�[�B
	const float DIVIDE_NUM = 4.0f;                      //m_aimMoveSpeed�����鐔�l�B���������m_aimMoveSpeed��m_gunLocalPosition�ɑ����Ă����񐔁B
	CVector3 m_gunLocalPosition = CVector3::Zero();     //�J���������_�Ƃ����e�̃��[�J�����W�B
	CVector3 m_aimMoveSpeed = CVector3::Zero();         //�G�C������Ƃ��̃X�s�[�h�B
	CVector3 m_initBulletPos = CVector3::Zero();        //�e�����������̒e�̍ŏ��̍��W�B
	int m_count = 0;                                    //�G�C���ɏ�����������邽�߂̃J�E���g�B
	const enum {
		enAnimationCrip_nothing,   //�������Ȃ��B
		enAnimationCrip_reload,    //�����[�h�B
		enAnimationCrip_num        //�A�j���[�V�����N���b�v�̐��B
	};
	int m_animationFlug = 0;                            //�A�j���[�V���������߂�t���O�B
private:
	Player* m_player;                                   //�v���C���[�̃C���X�^���X�B
	Bullet* m_bullet;                                   //�e�̃C���X�^���X�B
	FontRender m_font;                                  //���U�e���ƒe����\�����Ă��镶���B
	CVector3 m_bulletPos = CVector3::Zero();            //�e�̍��W�B
	float m_angle = 0.0f;                               //���̉�]�p�x�B
	float m_angle2 = 0.0f;                              //�c�̉�]�p�x�B
	int m_usedBullet = 0;                               //�g���I�����e�B
	int m_reloadTimer = 0;                              //�����[�h�^�C�}�[�B
	bool m_reloadFlug = false;                          //�����[�h���Ă��邩�ǂ����B
	Sprite m_sprite;                                    //�����[�h�Q�[�W�̃X�v���C�g�B
	CVector3 m_reloadGagePos = {-24.0f, -30.0f, 0.0f};  //�����[�h�Q�[�W�̃X�v���C�g�̍��W�B
	CVector3 m_reloadGageScale = { 0.6f, 0.1f, 1.0f };  //�����[�h�Q�[�W�̃X�v���C�g�̑傫���B
	DirectX::XMFLOAT2 m_fontPos = { 100.0f, 600.0f };   //�����̍��W�B
	float m_fontRed = 0.0f;                             //�����̐Ԃ̐����B
	float m_fontGreen = 0.0f;                           //�����̗΂̐����B
	float m_fontBlue = 0.0f;                            //�����̐̐����B
	float m_fontScale = 1.0f;                           //�����̑傫���B
	bool m_recoiledFlug = false;                        //�������󂯂����ǂ����B
};


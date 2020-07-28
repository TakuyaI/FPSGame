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
	IGunObject();
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
	GameCamera* m_gameCam;
	GunGenerator* m_gunGen;

	float m_rotSpeed = 3.0f;
	int m_bulletIntervalTimer = 0;
	const float DIVIDE_NUM = 4.0f; //m_aimMoveSpeed�����鐔�l�B
	CVector3 m_gunLocalPosition = CVector3::Zero();
	CVector3 m_aimMoveSpeed = CVector3::Zero();
	int m_count = 0;

private:
	Player* m_player;
	Enemy* m_enemy;
	Bullet* m_bullet;
	FontRender m_font;

	CVector3 m_bulletPos = CVector3::Zero();
	float m_angle = 0.0f;
	float m_angle2 = 0.0f;
	int m_usedBullet = 0; //�g���I�����e�B
	int m_reloadTimer = 0;  //�����[�h�^�C�}�[�B
	bool m_reloadFlug = false; //�����[�h���Ă��邩�ǂ����B

	Sprite m_sprite;
	CVector3 m_reloadGagePos = {-24.0f, -30.0f, 0.0f};
	CVector3 scale = { 0.6f, 0.1f, 1.0f };

	float m_red = 0.0f;
	float m_green = 0.0f;
	float m_blue = 0.0f;

	bool m_recoiledFlug = false;//�������󂯂����ǂ����B
};


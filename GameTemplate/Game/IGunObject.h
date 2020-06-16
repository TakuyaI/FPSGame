#pragma once
class GameCamera;
class Bullet;
class GunGenerator;
class EnemyGenerator;
class Sprite;
class Player;
class Enemy;
#include "IGunObject.h"
#include "IGameObject.h"
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
	/// <param name="scale">�T�C�Y</param>
	/// <param name="ammo">�e��</param>
	/// <param name="loading">���U�e��</param>
	/// <param name="maxLoading">�ő呕�U�e��</param>
	/// <param name="bulletIntervalTime">�e�̃C���^�[�o��</param>
	/// <param name="bulletMoveSpeed">�e�̑��x</param>
	/// <param name="reaction">���C���̔���</param>
	/// <param name="reloadTime">�����[�h�ɂ����鎞��</param>
	void GunUpdate(CVector3* position, CQuaternion* rotation, CVector3* scale, int* ammo, int* loading, int* maxLoading, int* bulletIntervalTime, float* bulletMoveSpeed, float* reaction, int* reloadTime, CSoundSource& gunshot);
	/// <summary>
	///�@�|�X�g�����_�[�B
	/// </summary>
	/// <param name="reloadTime">�����[�h���ԁB</param>
	/// <param name="ammo">�e���B</param>
	/// <param name="loading">���U�e���B</param>
	/// <param name="maxLoading">�ő呕�U�e���B</param>
	void GunPostRender(int* reloadTime, int* ammo, int* loading, int* maxLoading);
	void Update();

	/*CVector3 Getpostion()
	{
		return m_position;
	}*/
	void SetNum(int num)
	{
		m_setNum = num;
	}
	int GetNum()
	{
		return m_setNum;
	}
	void SetShootingBulletFlug(bool shootingbullet)
	{
		m_shootingBulletFlug = shootingbullet;
	}
	bool GetShootingBulletFlug()
	{
		return m_shootingBulletFlug;
	}
	/*CQuaternion* GetRotation()
	{
		return &m_rotation;
	}*/
	int GetAmmo()
	{
		return m_ammo;
	}
	int GetLoading()
	{
		return m_loading;
	}
	bool GetReloadFlug()
	{
		return m_reloadFlug;
	}
private:
	/// <summary>
	/// �e�����������ɌĂ΂��֐��B
	/// </summary>
	virtual void OnShot(CVector3* position, CQuaternion* rotation) {}
protected:
	Effekseer::Handle m_playEffectHandle = -1;
	GameCamera* m_gameCam;
	//Effekseer::Effect* m_sampleEffect = nullptr;
private:
	//SkinModel m_model;
	CSoundSource m_gunShot; //�e���̉��B
	Player* m_player;
	Enemy* m_enemy;
	
	Bullet* m_bullet;
	GunGenerator* m_gunGen;
	EnemyGenerator* m_enemyGen;
	FontRender m_font;

	CVector3 m_position = CVector3::Zero();
	CVector3 m_Pos = { 15.0f, -8.0f, 10.0f };
	CVector3 m_gunLocalPosition = { 15.0f, -8.0f, 10.0f };
	CVector3 m_bulletPos = CVector3::Zero();
	CQuaternion m_rotation = CQuaternion::Identity();
	float m_angle = 0.0f;
	float m_angle2 = 0.0f;
	int m_bulletIntervalTimer = 0;
	int m_bulletIntervalTime;
	float m_bulletMoveSpeed;
	int m_setNum = 0;
	int m_ammo = 0; //�e���B
	int m_loading = 0;//���U�e���B
	int m_usedBullet = 0; //�g���I�����e�B
	int m_maxLoading = 0;//�ő呕�U�e���B
	float m_reaction = 0.0f;   //�e�̔����B
	int m_reloadTimer = 0;  //�����[�h�^�C�}�[�B
	int m_reloadTime = 0;  //�����[�h�^�C���B
	bool m_reloadFlug = false; //�����[�h���Ă��邩�ǂ����B
	bool m_shootingBulletFlug = false; //�e�������Ă��邩�ǂ����B

	
	
	CVector3 m_effectPos = CVector3::Zero();

	Sprite m_sprite;
	CVector3 pos = CVector3::Zero();
	CVector3 scale = { 0.6f, 0.1f, 1.0f };

	float m_red = 0.0f;
	float m_green = 0.0f;
	float m_blue = 0.0f;

	float sss = 0.0f;

};


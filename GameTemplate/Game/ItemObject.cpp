#include "stdafx.h"
#include "ItemObject.h"


ItemObject::ItemObject()
{
	//ItemGenerator�̃C���X�^���X��T���B	
	m_itemGen = g_goMgr.FindGameObject<ItemGenerator>(itemgenerator);
	//Player�̃C���X�^���X��T���B
	m_player = g_goMgr.FindGameObject<Player>(player);
	//Game�̃C���X�^���X��T���B
	m_game = g_goMgr.FindGameObject<Game>(game);
	//�A�C�e���̔ԍ��������_���ŏo���B
	int itemNum = itemnum;
	m_itemNumber = g_goMgr.Rand(--itemNum);
	if (m_itemNumber == danyaku) {
		//�e��B
		m_model.Init(L"Assets/modelData/item01.cmo");
	}
	else if (m_itemNumber == kaihuku) {
		//�񕜖�B
		m_model.Init(L"Assets/modelData/item01.cmo");
	}
}


ItemObject::~ItemObject()
{
}
bool ItemObject::Start()
{
	
	return true;
}
void ItemObject::Update()
{
	if (m_game->GetEndFlug() != false) {
		//�Q�[�����I��������C���X�^���X���폜����B
		g_goMgr.DeleteGameObject(this);
	}
	//�A�C�e������v���C���[�Ɍ������ĐL�т�x�N�g�������߂�B
	CVector3 toPlayerV = m_player->GetPosition() - m_position;
	if (toPlayerV.Length() <= m_getItemRange) {
		//�A�C�e�����擾�͈͂ɓ������B
		//ItemGenerator�̃C���X�^���X��T���B
		ItemGenerator* itemGen = g_goMgr.FindGameObject<ItemGenerator>(itemgenerator);
		if (m_itemNumber == danyaku) {
			//�e��̎擾�t���O��ݒ肷��B
			itemGen->SetDanyakuFkug(true);
		}
		else if (m_itemNumber == kaihuku) {
			//�񕜖�̎擾�t���O��ݒ肷��B
			itemGen->SetKaihukuyakuFkug(true);
		}
		//�C���X�^���X�̍폜�B
		g_goMgr.DeleteGameObject(this);
	}
	m_model.UpdateWorldMatrix(m_position, CQuaternion::Identity(), CVector3::One());
}

void ItemObject::Render()
{
	//�`��B
	m_model.Draw(
		enRenderMode_Normal,
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}

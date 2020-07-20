#include "stdafx.h"
#include "ItemObject.h"


ItemObject::ItemObject()
{
	//ItemGeneratorのインスタンスを探す。	
	m_itemGen = g_goMgr.FindGameObject<ItemGenerator>(itemgenerator);
	//Playerのインスタンスを探す。
	m_player = g_goMgr.FindGameObject<Player>(player);
	//Gameのインスタンスを探す。
	m_game = g_goMgr.FindGameObject<Game>(game);
	//アイテムの番号をランダムで出す。
	int itemNum = itemnum;
	m_itemNumber = g_goMgr.Rand(--itemNum);
	if (m_itemNumber == danyaku) {
		//弾薬。
		m_model.Init(L"Assets/modelData/item01.cmo");
	}
	else if (m_itemNumber == kaihuku) {
		//回復薬。
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
		//ゲームが終了したらインスタンスを削除する。
		g_goMgr.DeleteGameObject(this);
	}
	//アイテムからプレイヤーに向かって伸びるベクトルを求める。
	CVector3 toPlayerV = m_player->GetPosition() - m_position;
	if (toPlayerV.Length() <= m_getItemRange) {
		//アイテムが取得範囲に入った。
		//ItemGeneratorのインスタンスを探す。
		ItemGenerator* itemGen = g_goMgr.FindGameObject<ItemGenerator>(itemgenerator);
		if (m_itemNumber == danyaku) {
			//弾薬の取得フラグを設定する。
			itemGen->SetDanyakuFkug(true);
		}
		else if (m_itemNumber == kaihuku) {
			//回復薬の取得フラグを設定する。
			itemGen->SetKaihukuyakuFkug(true);
		}
		//インスタンスの削除。
		g_goMgr.DeleteGameObject(this);
	}
	m_model.UpdateWorldMatrix(m_position, CQuaternion::Identity(), CVector3::One());
}

void ItemObject::Render()
{
	//描画。
	m_model.Draw(
		enRenderMode_Normal,
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}

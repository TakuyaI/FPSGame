#include "stdafx.h"
#include "Kaihuku.h"


Kaihuku::Kaihuku()
{
}


Kaihuku::~Kaihuku()
{
}
void Kaihuku::ItemEffects()
{
	m_player = g_goMgr.FindGameObject<Player>(player);
	//HP���񕜁B
	m_player->SetHpChanges(m_kaihukuryou);
}
#include "stdafx.h"
#include "Kaihuku.h"


Kaihuku::Kaihuku()
{
}


Kaihuku::~Kaihuku()
{
}
bool Kaihuku::Start()
{
	return true;
}
void Kaihuku::Update()
{
	ItemUpdate(&m_position, &m_number);
}
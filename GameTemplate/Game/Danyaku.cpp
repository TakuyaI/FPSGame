#include "stdafx.h"
#include "Danyaku.h"


Danyaku::Danyaku()
{
}


Danyaku::~Danyaku()
{
}

bool Danyaku::Start()
{
	return true;
}

void Danyaku::Update()
{
	ItemUpdate(&m_position, &m_number);
}
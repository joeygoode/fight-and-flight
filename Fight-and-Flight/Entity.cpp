#include "Entity.h"


CEntity::CEntity(void)
{
}


CEntity::~CEntity(void)
{
}

void CEntity::SetName(string name)
{
	m_name = name;
}

string CEntity::GetName(void) const
{
	return m_name;
}

void CEntity::Clear(void)
{
	m_name.clear();
}
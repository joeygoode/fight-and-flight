#include "Entity.h"


CEntity::CEntity(void)
{
}


CEntity::~CEntity(void)
{
}

void CEntity::SetName(const string& name)
{
	m_name = name;
}

const string& CEntity::GetName(void) const
{
	return m_name;
}

void CEntity::Clear(void)
{
	m_name.clear();
}

void CEntity::SetHitpoints(int i)
{
	m_hitpoints = i;
}
void CEntity::HurtMe(int i)
{
	if (i < 0)
		m_hitpoints = 0;
	else
		m_hitpoints -= i;
}

int CEntity::GetHitpoints(void) const
{
	return m_hitpoints;
}

void CEntity::SetFaction(const string& faction)
{
	m_faction = faction;
}

const string& CEntity::GetFaction(void) const
{
	return m_faction;
}
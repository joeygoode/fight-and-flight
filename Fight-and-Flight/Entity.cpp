#include "Entity.h"


CEntity::CEntity(void)
{
	m_damage = 0;
	m_AddtlData = 0;
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
		m_damage += i;
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

void CEntity::UpdateHP(void)
{
	if (m_hitpoints < 0)
		m_damage = 0;
	else if (m_hitpoints - m_damage < 0)
		m_hitpoints = 0;
	else
		m_hitpoints -= m_damage;
	m_damage = 0;
}
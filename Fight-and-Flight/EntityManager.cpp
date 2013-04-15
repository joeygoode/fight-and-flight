#include "EntityManager.h"
#include "Entity.h"
#include "EntityRenderer.h"

CEntityManager* CEntityManager::s_Singleton = NULL;

CEntityManager* CEntityManager::Get(void)
{
	if (!s_Singleton)
		s_Singleton = new CEntityManager();
	return s_Singleton;
}

void CEntityManager::Clear(void)
{
	if (s_Singleton)
		delete s_Singleton;
	s_Singleton = NULL;
}

CEntityManager::CEntityManager(void)
{
	m_MaxEntities = 150;
	m_HighestAssigned = 0;
	m_pEntities = new vector<CEntity>();
	m_pRenderers = new vector<CEntityRenderer>();
	m_pEntities->resize(m_MaxEntities);
	m_pRenderers->resize(m_MaxEntities);
}


CEntityManager::~CEntityManager(void)
{
	delete m_pEntities;
	delete m_pRenderers;
}

bool CEntityManager::AllocateEntity(ENTITY_DESC desc)
{
	int top = (m_HighestAssigned == m_MaxEntities) ? m_MaxEntities : m_HighestAssigned + 1;
	for(int i = 0; i<top; i++)
	{
		if ((*m_pEntities)[i].GetName().empty())
		{
			(*m_pEntities)[i].SetName(desc.name);
			(*m_pRenderers)[i].SetMeshID(desc.mesh_id);
			++m_HighestAssigned;
			return true;
		}
	}
	return false;
}

void CEntityManager::DrawAllEntities(void) const
{
	for(int i = 0; i < m_HighestAssigned; i++)
	{
		if (!(*m_pEntities)[i].GetName().empty())
			(*m_pRenderers)[i].Draw();
	}
}
#include "EntityManager.h"
#include "Entity.h"
#include "EntityRenderer.h"


CEntityManager::CEntityManager(void)
{
	m_MaxEntities = 100;
	m_HighestAssigned = 0;
	m_pEntities = new vector<CEntity>();
	m_pRenderers = new vector<CEntityRenderer>();
	m_pEntities->resize(100);
	m_pRenderers->resize(100);

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
			(*m_pRenderers)[i].Clear();
			(*m_pRenderers)[i].SetMeshID(desc.mesh_id);
			return true;
		}
	}
	return false;
}
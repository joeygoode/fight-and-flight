#include <queue>
using std::queue;

#include "EntityManager.h"
#include "Entity.h"
#include "EntityRenderer.h"
#include "EntityTransform.h"
#include "Effect.h"
#include "Matrix.h"

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
	m_MaxEntities = 200;
	m_HighestAssigned = 0;
	m_pEntities = new vector<CEntity>(m_MaxEntities);
	m_pRenderers = new vector<CEntityRenderer>(m_MaxEntities);
	m_pTransforms = new vector<CEntityTransform>(m_MaxEntities);
}


CEntityManager::~CEntityManager(void)
{
	delete m_pEntities;
	delete m_pRenderers;
	delete m_pTransforms;
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
			(*m_pTransforms)[i].SetPosition(desc.position);
			(*m_pTransforms)[i].SetOrientation(desc.orientation);
			(*m_pTransforms)[i].SetScale(desc.scale);
			++m_HighestAssigned;
			return true;
		}
	}
	return false;
}

void CEntityManager::DrawAllEntities(CEffect* pEffect) const
{
	for(int i = 0; i < m_HighestAssigned; i++)
	{
		if (!(*m_pEntities)[i].GetName().empty())
			pEffect->SetVariableByName("World",(*m_pTransforms)[i].GetMatrix());
		//draw cube
		for( UINT p = 0; p < pEffect->GetTechDesc().Passes; p++ )
		{
			//apply technique
			pEffect->GetTechnique()->GetPassByIndex( p )->Apply( 0 );
			(*m_pRenderers)[i].Draw();
		}
	}
}

bool CEntityManager::KillByName(const string& name)
{
	for (int i = 0; i < m_MaxEntities; i++)
	{
		if (name == (*m_pEntities)[i].GetName())
		{
			(*m_pEntities)[i].Clear();
			return true;
		}
	}
	return false;
}

int CEntityManager::Compact(void)
{
	queue<int> unused = queue<int>();
	for (int i = 0; i < m_MaxEntities; i++)
	{
		if ((*m_pEntities)[i].GetName().empty())
		{
			unused.push(i);
		}
		else if (!unused.empty())
		{
			std::swap((*m_pEntities)[i],(*m_pEntities)[unused.front()]);
			std::swap((*m_pRenderers)[i],(*m_pRenderers)[unused.front()]);
			std::swap((*m_pTransforms)[i],(*m_pTransforms)[unused.front()]);
			unused.pop();
		}
	}
	return unused.size();
}
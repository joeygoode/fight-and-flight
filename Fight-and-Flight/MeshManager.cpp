#include "MeshManager.h"
#include "Mesh.h"
#include <algorithm>
using std::find_if;
using std::none_of;
#include <queue>
using std::queue;

CMeshManager* CMeshManager::s_Singleton = NULL;

CMeshManager* CMeshManager::Get(void)
{
	if (!s_Singleton)
		s_Singleton = new CMeshManager();
	return s_Singleton;
}

void CMeshManager::Clear(void)
{
	if (s_Singleton)
		delete s_Singleton;
	s_Singleton = NULL;
}

CMeshManager::CMeshManager()
{
	m_MaxMeshes = 10;
	m_HighestAssigned = 0;
	m_Meshes = vector<CMesh>(m_MaxMeshes);
}


CMeshManager::~CMeshManager(void)
{
}

bool CMeshManager::AllocateMesh(	_In_ const vector<vertex>& vertices,
									_In_ const vector<UINT>& indices,
									_In_ int NumFaces,
									_In_ const string& MeshID)
{
	int top = (m_HighestAssigned == m_MaxMeshes) ? m_MaxMeshes : m_HighestAssigned + 1;
	for(int i = 0; i<top; i++)
	{
		if (m_Meshes[i].GetID().empty())
		{
			CDirectXManager::Get()->CreateMesh(vertices,indices,NumFaces,MeshID,m_Meshes[i]);
			return true;
		}
	}
	return false;
}

void CMeshManager::DrawMeshByID(const string& ID) const
{
	const CMesh* temp = &*find_if(	m_Meshes.begin(),
									m_Meshes.end(),
									[ID](const CMesh& mesh) throw() -> bool
	{
		if (mesh.GetID() == ID)
			return true;
		else
			return false;
	});
	temp->Draw();
}

void CMeshManager::FreeUnusedByID(const vector<string>& IDs)
{
	for (int i = 0; i < m_MaxMeshes; i++)
	{
		if (none_of(	IDs.begin(),
						IDs.end(),
						[this, i] (const string& ID) throw() -> bool
		{
			if (ID == this->m_Meshes[i].GetID())
				return true;
			else
				return false;
		}))
		{
			m_Meshes[i].Clear();
		}
	}
}

int CMeshManager::Compact(void)
{
	queue<int> unused = queue<int>();
	for (int i = 0; i < m_MaxMeshes; i++)
	{
		if (m_Meshes[i].GetID().empty())
		{
			unused.push(i);
		}
		else if (!unused.empty())
		{
			std::swap(m_Meshes[i],m_Meshes[unused.front()]);
			unused.pop();
		}
	}
	return unused.size();
}
#include "MeshManager.h"
#include "Mesh.h"
#include <algorithm>
using std::find_if;

CMeshManager::CMeshManager(CDirectXManager* pDirectXManager)
{
	m_MaxMeshes = 10;
	m_HighestAssigned = 0;
	m_Meshes = vector<CMesh>(m_MaxMeshes);
	m_pDirectXManager = pDirectXManager;
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
			m_pDirectXManager->CreateMesh(vertices,indices,NumFaces,MeshID,m_Meshes[i]);
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
#pragma once
#include <vector>
using std::vector;
#include "DirectXManager.h"

class CMesh;

class CMeshManager
{
	int m_MaxMeshes;
	int m_HighestAssigned;
	vector<CMesh> m_Meshes;
	CDirectXManager* m_pDirectXManager;

public:
	CMeshManager(CDirectXManager* pDirectXManager);
	~CMeshManager(void);
	bool AllocateMesh(	_In_ const vector<vertex>& vertices,
						_In_ const vector<UINT>& indices,
						_In_ int NumFaces,
						_In_ const string& MeshID);
	void DrawMeshByID( _In_ const string& MeshID) const;
};


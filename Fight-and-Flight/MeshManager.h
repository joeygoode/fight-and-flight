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
	static CMeshManager* s_Singleton;
public:
	static CMeshManager* Get(void);
	static void Clear(void);
	bool AllocateMesh(	_In_ const string& filename);
	bool AllocateMesh(	_In_ const vector<vertex>& vertices,
						_In_ const vector<UINT>& indices,
						_In_ int NumFaces,
						_In_ const string& MeshID);
	void DrawMeshByID( _In_ const string& MeshID) const;
	// These two methods haven't been really tested yet.  If a bug
	// shows up, it could be here.  
	void FreeUnusedByID( _In_ const vector<string>& IDsToKeep);
	int	 Compact(void);
private:
	CMeshManager(void);
	~CMeshManager(void);
};


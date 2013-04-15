#pragma once
#include <string>
using std::string;

#include "GFXAPIBase.h"

class CMesh : public CGFXAPIBase
{
	friend class CMeshManager;
	string m_ID;
public:
	// Create a new mesh.  For some reason, xmemory0 needs this to be public.
	// I think it has to do wih me forcing a vector to fill with meshes.
	// I'll try to find a workaround.
	CMesh(void);
	// Destroy the mesh and release it.
	~CMesh(void);
	// Draw the mesh
	void Draw(void) const;
	const string& GetID(void) const;
	void Clear(void);
// Use the following methods if we're using DirectX10
#if (GRAPHICSAPI == DIRECTX10)
	friend class CDirectXManager;
private:
	// The wrapped DX10 Mesh
	ID3DX10Mesh* m_pDXMesh;
#endif
};


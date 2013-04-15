#pragma once
#include <string>
using std::string;

#include "GFXAPIBase.h"

class CMesh : public CGFXAPIBase
{
	friend class CGFXAPIBase;
	string m_ID;
public:
	CMesh(void);
	// Destroy the mesh and release it.
	~CMesh(void);
	// Draw the mesh
	void Draw(void) const;
	const string& GetID(void) const;
// Use the following methods if we're using DirectX10
#if (GRAPHICSAPI == DIRECTX10)
	friend class CDirectXManager;
private:
	// Put a DX Mesh inside this CMesh.
	CMesh(ID3DX10Mesh* pDXMesh,string ID);
	// The wrapped DX10 Mesh
	ID3DX10Mesh* m_pDXMesh;
#endif
};


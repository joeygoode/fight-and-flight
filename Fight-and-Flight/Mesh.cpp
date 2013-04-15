#include "Mesh.h"

//-----------------------------------------------------------------------------
// Name: GetID
// Type: Getter
// Vis: Public
// Desc: Get the unique ID for this Mesh
//-----------------------------------------------------------------------------
const string& CMesh::GetID(void) const
{
	return m_ID;
}

#if (GRAPHICSAPI == DIRECTX10)
CMesh::CMesh(void)
{
	m_pDXMesh = NULL;
}

//-----------------------------------------------------------------------------
// Name: ~CMesh
// Type: Destructor
// Vis: Public
// Desc: Destroy the CMesh and release it's wrapped mesh.
//-----------------------------------------------------------------------------
CMesh::~CMesh(void)
{
	if (m_pDXMesh)
	m_pDXMesh->Release();
}

//-----------------------------------------------------------------------------
// Name: CMesh
// Type: Constructor
// Vis: Private
// Desc: Construct a new CMesh using a DXMesh as a base, with the given ID.
//		 IDs should be UNIQUE!  Best case use the filename!
//-----------------------------------------------------------------------------
CMesh::CMesh(ID3DX10Mesh* pDXMesh, string ID)
{
	m_pDXMesh = pDXMesh;
	m_ID = ID;
}

//-----------------------------------------------------------------------------
// Name: Draw
// Type: Method
// Vis: Public
// Desc: Draw the mesh to the screen.
//-----------------------------------------------------------------------------
void CMesh::Draw(void) const
{
	m_pDXMesh->DrawSubset(0);
}
#endif
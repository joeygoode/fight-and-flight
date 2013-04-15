#include "Mesh.h"

//-----------------------------------------------------------------------------
// Name: GetID
// Type: Getter
// Vis: Public
// Output:
//	- retval: The unique ID for this Mesh
//-----------------------------------------------------------------------------
const string& CMesh::GetID(void) const
{
	return m_ID;
}

#if (GRAPHICSAPI == DIRECTX10)
//-----------------------------------------------------------------------------
// Name: CMesh
// Type: Constructor
// Vis: Public
// Desc: Create a new mesh.
//-----------------------------------------------------------------------------
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
// Name: Draw
// Type: Method
// Vis: Public
// Desc: Draw the mesh to the screen.
//-----------------------------------------------------------------------------
void CMesh::Draw(void) const
{
	m_pDXMesh->DrawSubset(0);
}

//-----------------------------------------------------------------------------
// Name: Clear
// Type: Method
// Vis: Public
// Desc: Release the held mesh, if present, and reset all data so that it can
// be reallocated.
//-----------------------------------------------------------------------------
void CMesh::Clear(void)
{
	if (m_pDXMesh)
		m_pDXMesh->Release();
	m_ID.clear();
}
#endif
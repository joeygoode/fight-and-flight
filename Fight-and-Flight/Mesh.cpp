#include "Mesh.h"





CMesh::~CMesh(void)
{
	m_pDXMesh->Release();
}
#if (GRAPHICSAPI == DIRECTX10)
CMesh::CMesh(ID3DX10Mesh* pDXMesh)
{
	m_pDXMesh = pDXMesh;
}

void CMesh::Draw(void)
{
	m_pDXMesh->DrawSubset(0);
}
#endif
#pragma once
#if (GRAPHICSAPI == DIRECTX10)
#include "DirectXManager.h"
#endif

class CMesh
{
public:
	~CMesh(void);
	void Draw(void);

#if (GRAPHICSAPI == DIRECTX10)
public:
	CMesh(ID3DX10Mesh* pDXMesh);
private:
	ID3DX10Mesh* m_pDXMesh;
#endif
};


#pragma once
#if (GRAPHICSAPI == DIRECTX10)
#include <D3DX10.h>
#endif

class CVector3
{
public:
	CVector3(float x, float y, float z);
	~CVector3(void);
	float GetX(void) const;
	float GetY(void) const;
	float GetZ(void) const;
#if (GRAPHICSAPI == DIRECTX10)
public:
	CVector3(D3DXVECTOR3 DXVector);
	D3DXVECTOR3 GetD3DXVECTOR3(void);
private:
	D3DXVECTOR3 m_DXVector;
#endif
};


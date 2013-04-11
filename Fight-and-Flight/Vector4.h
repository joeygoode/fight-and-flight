#pragma once
#if (GRAPHCSAPI == DIRECTX10)
#include <D3DX10.h>
#endif
class CVector4
{
public:
	CVector4(float w, float x, float y, float z);
	~CVector4(void);
	float GetW(void) const;
	float GetX(void) const;
	float GetY(void) const;
	float GetZ(void) const;
#if (GRAPHICSAPI == DIRECTX10)
public:
	CVector4(D3DXVECTOR4 DXVector);
	D3DXVECTOR4 GetD3DXVECTOR4(void) const;
private:
	D3DXVECTOR4 m_DXVector;
#endif
};



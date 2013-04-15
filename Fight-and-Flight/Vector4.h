#pragma once
#include "GFXAPIBase.h"
class CVector4 : CGFXAPIBase
{
	friend class CEffectVariable;
public:
	// Construct a new vector 4 from given inputs
	CVector4(float w, float x, float y, float z);
	// Destroy this vector4
	~CVector4(void);
	// Get the W component
	float GetW(void) const;
	// Get the X component
	float GetX(void) const;
	// Get the Y component
	float GetY(void) const;
	// Get the Z component
	float GetZ(void) const;

//If we're using DirectX, use these methods.
#if (GRAPHICSAPI == DIRECTX10)
private:
	// Wrap the input vector
	CVector4(D3DXVECTOR4 DXVector);
	// Get the wrapped vector
	D3DXVECTOR4 GetD3DXVECTOR4(void) const;
	// The wrapped vector
	D3DXVECTOR4 m_DXVector;
#endif
};



#pragma once
#include "GFXAPIBase.h"

class CVector3 : CGFXAPIBase
{
	friend class CMatrix;
public:
	CVector3 operator+=(const CVector3& that);
	CVector3 operator*=(float f);
	CVector3 operator*(float f);
	CVector3 operator%(float f);
	// Construct a new 3D vector (all data is 0)
	CVector3(void);
	// Construct a new 3D vector
	CVector3(float x, float y, float z);
	// Destroy this 3D vector
	~CVector3(void);
	// Get the x component of this 3D vector
	float GetX(void) const;
	// Get the y component of this 3D vector
	float GetY(void) const;
	// Get the z component of this 3D vector
	float GetZ(void) const;
	// Set the x component of this vector
	void SetX(float x);
	// Set the y component of this vector
	void SetY(float y);
	// Set the z component of this vector
	void SetZ(float z);
	// Set the data of this vector equal to the input vector
	void Set(const CVector3& that);
// Use these functions if we're using DirectX 10
#if (GRAPHICSAPI == DIRECTX10)
private:
	// Wrap a D3DXVECTOR3
	CVector3(D3DXVECTOR3 DXVector);
	// Get the D3DXVECTOR3 out of this Vector
	D3DXVECTOR3 GetD3DXVECTOR3(void) const;
	// The wrapped D3DXVECTOR3 struct
	D3DXVECTOR3 m_DXVector;
#endif
};


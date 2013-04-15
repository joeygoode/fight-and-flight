#include "Vector4.h"

//-----------------------------------------------------------------------------
// Name: CVector4
// Type: Constructor
// Vis: Public
// Desc: Create a new 4D Vector with the given inputs.
// Inputs:
//	- w: The w componet of the new vector.
//	- x: The x componet of the new vector.
//	- y: The y componet of the new vector.
//	- z: The z componet of the new vector.
//-----------------------------------------------------------------------------
CVector4::CVector4(float w, float x, float y, float z)
{
#if (GRAPHICSAPI == DIRECTX10)
	m_DXVector = D3DXVECTOR4(w,x,y,z);
#endif
}

//-----------------------------------------------------------------------------
// Name: ~CVector4
// Type: Constructor
// Vis: Public
// Desc: Destroy this 4D Vector.
//-----------------------------------------------------------------------------
CVector4::~CVector4(void)
{
}
//-----------------------------------------------------------------------------
// Name: GetW
// Type: Getter
// Vis: Public
// Outputs:
//	- retval : w component of the wrapped D3DXVECTOR3
//-----------------------------------------------------------------------------
float CVector4::GetW(void) const
{
#if (GRAPHICSAPI == DIRECTX10)
	return m_DXVector.w;
#endif
}

//-----------------------------------------------------------------------------
// Name: GetX
// Type: Getter
// Vis: Public
// Outputs:
//	- retval : x component of the wrapped D3DXVECTOR3
//-----------------------------------------------------------------------------
float CVector4::GetX(void) const
{
#if (GRAPHICSAPI == DIRECTX10)
	return m_DXVector.x;
#endif
}
//-----------------------------------------------------------------------------
// Name: GetY
// Type: Getter
// Vis: Public
// Outputs:
//	- retval : y component of the wrapped D3DXVECTOR3
//-----------------------------------------------------------------------------
float CVector4::GetY(void) const
{
#if (GRAPHICSAPI == DIRECTX10)
	return m_DXVector.y;
#endif
}
//-----------------------------------------------------------------------------
// Name: GetZ
// Type: Getter
// Vis: Public
// Outputs:
//	- retval : z component of the wrapped D3DXVECTOR3
//-----------------------------------------------------------------------------
float CVector4::GetZ(void) const
{
#if (GRAPHICSAPI == DIRECTX10)
	return m_DXVector.z;
#endif
}


#if (GRAPHICSAPI == DIRECTX10)
//-----------------------------------------------------------------------------
// Name: CVector4
// Type: Constructor
// Vis: Private
// Desc: Create a new Vector4 by wrapping the given vector
// Inputs:
//	- DXVector: the vector to be wrapped.
//-----------------------------------------------------------------------------
CVector4::CVector4(D3DXVECTOR4 DXVector)
{
	m_DXVector = DXVector;
}

//-----------------------------------------------------------------------------
// Name: GetD3DXVECTOR4
// Type: Getter
// Vis: Private
// Inputs:
//	- retval: the wrapped D3DXVECTOR4
//-----------------------------------------------------------------------------
D3DXVECTOR4 CVector4::GetD3DXVECTOR4(void) const
{
	return m_DXVector;
}
#endif

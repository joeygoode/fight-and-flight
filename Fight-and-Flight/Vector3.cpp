#include "Vector3.h"


//-----------------------------------------------------------------------------
// Name: CVector3
// Type: Constructor
// Vis: Public
// Desc: Creates a new vector with the given values.
// Inputs:
//	- x: The x component of the new vector
//	- y: The y component of the new vector
//	- z: The z component of the new vector
//-----------------------------------------------------------------------------
CVector3::CVector3(float x, float y, float z)
{
#if (GRAPHICSAPI == DIRECTX10)
	m_DXVector = D3DXVECTOR3(x,y,z);
#endif
}

//-----------------------------------------------------------------------------
// Name: ~CVector3
// Type: Destructor
// Vis: Public
// Desc: Destroys this vector.
//-----------------------------------------------------------------------------
CVector3::~CVector3(void)
{
}

//-----------------------------------------------------------------------------
// Name: GetX
// Type: Getter
// Vis: Public
// Outputs:
//	- retval : x component of the wrapped D3DXVECTOR3
//-----------------------------------------------------------------------------
float CVector3::GetX(void) const
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
float CVector3::GetY(void) const
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
float CVector3::GetZ(void) const
{
#if (GRAPHICSAPI == DIRECTX10)
	return m_DXVector.z;
#endif
}

//-----------------------------------------------------------------------------
// Name: CVector3
// Type: Constructor
// Vis: Private
// Desc: Wraps the given vector
// Inputs:
//	- DXVector: the vector to wrap
//-----------------------------------------------------------------------------
#if (GRAPHICSAPI == DIRECTX10)
CVector3::CVector3(D3DXVECTOR3 DXVector)
{
	m_DXVector = DXVector;
}
//-----------------------------------------------------------------------------
// Name: GetD3DXVECTOR3
// Type: Getter
// Vis: Private
// Outputs:
//	- retval: The wrapped vector
//-----------------------------------------------------------------------------
D3DXVECTOR3 CVector3::GetD3DXVECTOR3(void) const
{
	return m_DXVector;
}
#endif

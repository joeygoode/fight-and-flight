#include "Vector3.h"


CVector3::CVector3(float x, float y, float z)
{
#if (GRAPHICSAPI == DIRECTX10)
	m_DXVector = D3DXVECTOR3(x,y,z);
#endif
}


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

#if (GRAPHICSAPI == DIRECTX10)
CVector3::CVector3(D3DXVECTOR3 DXVector)
{
	m_DXVector = DXVector;
}
D3DXVECTOR3 CVector3::GetD3DXVECTOR3(void) const
{
	return m_DXVector;
}
#endif

#include "Vector3.h"


//-----------------------------------------------------------------------------
// Name: CVector3
// Type: Constructor
// Vis: Public
// Desc: Creates a new vector with all values set to 0;
//-----------------------------------------------------------------------------
CVector3::CVector3(void)
{
#if (GRAPHICSAPI == DIRECTX10)
	m_DXVector = D3DXVECTOR3(0,0,0);
#endif
}

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
// Name: SetX
// Type: Setter
// Vis: Public
// Inputs:
//	- x : the new x value.
//-----------------------------------------------------------------------------
void CVector3::SetX(float x)
{
#if (GRAPHICSAPI == DIRECTX10)
	m_DXVector.x = x;
#endif
}

//-----------------------------------------------------------------------------
// Name: SetY
// Type: Setter
// Vis: Public
// Inputs:
//	- y : the new y value.
//-----------------------------------------------------------------------------
void CVector3::SetY(float y)
{
#if (GRAPHICSAPI == DIRECTX10)
	m_DXVector.y = y;
#endif
}

//-----------------------------------------------------------------------------
// Name: SetZ
// Type: Setter
// Vis: Public
// Inputs:
//	- z : the new z value.
//-----------------------------------------------------------------------------
void CVector3::SetZ(float z)
{
#if (GRAPHICSAPI == DIRECTX10)
	m_DXVector.z = z;
#endif
}

//-----------------------------------------------------------------------------
// Name: Set
// Type: Setter
// Vis: Public
// Inputs:
//	- vec : the vector whose data to assign to this.
//-----------------------------------------------------------------------------
void CVector3::Set(const CVector3& vec)
{
#if (GRAPHICSAPI == DIRECTX10)
	m_DXVector = vec.m_DXVector;
#endif
}

#if (GRAPHICSAPI == DIRECTX10)
//-----------------------------------------------------------------------------
// Name: CVector3
// Type: Constructor
// Vis: Private
// Desc: Wraps the given vector
// Inputs:
//	- DXVector: the vector to wrap
//-----------------------------------------------------------------------------
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

CVector3 CVector3::operator+=(const CVector3& that)
{
	m_DXVector += that.m_DXVector;
	return *this;
}

CVector3 CVector3::operator*=(float f)
{
	m_DXVector *= f;
	return *this;
}

CVector3 CVector3::operator*(float f)
{
	return CVector3(m_DXVector * f);
}

CVector3 CVector3::operator%(float f)
{
	int div = (int) m_DXVector.x / f;
	m_DXVector.x -= div * f;
	div = (int) m_DXVector.y / f;
	m_DXVector.y -= div * f;
	div = (int) m_DXVector.z / f;
	m_DXVector.z -= div * f;
	return *this;
}

#endif

#include "Matrix.h"
#include "Vector3.h"

//-----------------------------------------------------------------------------
// Name: ~CMatrix
// Type: Destructor
// Vis: Public
// Desc: Destroy this CMatrix
//-----------------------------------------------------------------------------
CMatrix::~CMatrix(void)
{
}

// Use these versions of functions if we're using DirectX 10
#if (GRAPHICSAPI == DIRECTX10)
//-----------------------------------------------------------------------------
// Name: CMatrix
// Type: Constructor
// Vis: Public
// Desc: Create a new CMatrix and make it the identity matrix.
//-----------------------------------------------------------------------------
CMatrix::CMatrix(void)
{
	D3DXMatrixIdentity(&m_DXMatrix);
}
//-----------------------------------------------------------------------------
// Name: CMatrix
// Type: Constructor
// Vis: Private
// Desc: Construct a new CMatrix and make it equal to the given matrix.
// Inputs:
//	- DXMatrix:  A D3DXMATRIX to wrap.
//-----------------------------------------------------------------------------
CMatrix::CMatrix(D3DXMATRIX DXMatrix)
{
	m_DXMatrix = DXMatrix;
}

//-----------------------------------------------------------------------------
// Name: GetD3DXMATRIX
// Type: Getter
// Vis: Private
// Desc: Get the wrapped D3DXMATRIX
// Inputs:
//	- DXMatrix:  A D3DXMATRIX to wrap.
// Outputs:
//	- retval: The wrapped D3DXMATRIX
//-----------------------------------------------------------------------------
D3DXMATRIX CMatrix::GetD3DXMATRIX(void) const
{
	return m_DXMatrix;
}

//-----------------------------------------------------------------------------
// Name: operator*=
// Type: Method
// Vis: Public
// Desc: Multiply the two matricies and set the result equal to the left hand
//		 side
// Inputs:
//	- that:  the CMatrix to multiply by.
// Outputs:
//	- retval: this CMatrix, for operator chaining.
//-----------------------------------------------------------------------------
CMatrix CMatrix::operator*=(const CMatrix& that)
{
	m_DXMatrix *= that.GetD3DXMATRIX();
	return *this;
}
//-----------------------------------------------------------------------------
// Name: operator*
// Type: Method
// Vis: Public
// Desc: Multiply the two matricies and put the result in a new matrix.
// Inputs:
//	- that: A CMatrix to multiply by.
// Outputs:
//	- retval: the new CMatrix, for operaor chaining.
//-----------------------------------------------------------------------------
CMatrix CMatrix::operator*(const CMatrix& that)
{
	return CMatrix(m_DXMatrix * that.GetD3DXMATRIX());

}
//-----------------------------------------------------------------------------
// Name: CMatrix
// Type: Builder
// Vis: Public
// Desc: Reset the input matrix
//-----------------------------------------------------------------------------
void CMatrix::SetIdentityMatrix(void)
{
	D3DXMatrixIdentity(&m_DXMatrix);
}

//-----------------------------------------------------------------------------
// Name: CreateMatrixLookAtLH
// Type: Builder
// Vis: Public
// Desc: Makes this a LH Look At matrix 
// Inputs:
//	- Eye: Position vector
//	- At: Toward vector
//	- Up: Up vector (usually can be (0,1,0)
//-----------------------------------------------------------------------------
void CMatrix::SetMatrixLookAtLH(	_In_ const CVector3& Eye,
									_In_ const CVector3& At,
									_In_ const CVector3& Up)
{
	D3DXMatrixLookAtLH(&m_DXMatrix, &Eye.GetD3DXVECTOR3(), &At.GetD3DXVECTOR3(), &Up.GetD3DXVECTOR3());
}

//-----------------------------------------------------------------------------
// Name: CreateMatrixPerspectiveFovLH
// Type: Builder
// Vis: Public
// Desc: Makes this a LH perspective projection matrix
// Inputs:
//	- vFov: vertical field of view
//	- aspectRatio: aspect ratio of the vew plane
//	- zNearPlane: z distance to the near plane
//	- zFarPlane: z distance to the far plane
//-----------------------------------------------------------------------------
void CMatrix::SetMatrixPerspectiveFovLH(	_In_ float vFov,
											_In_ float aspectRatio,
											_In_ float zNearPlane,
											_In_ float zFarPlane)
{
	D3DXMatrixPerspectiveFovLH(&m_DXMatrix, vFov, aspectRatio, zNearPlane, zFarPlane);
}

//-----------------------------------------------------------------------------
// Name: CreateMatrixRotationY
// Type: Factory
// Vis: Public
// Desc: Makes this a matrix that rotates around Y by angle
// Inputs:
//	- angle: the angle to rotate around the Y axis
//-----------------------------------------------------------------------------
void CMatrix::SetMatrixRotationY(_In_ float angle)
{
	D3DXMatrixRotationY(&m_DXMatrix, angle);
}
//-----------------------------------------------------------------------------
// Name: CreateMatrixTranslation
// Type: Builder
// Vis: Public
// Desc: Makes this a translation matrix
// Inputs:
//	- x: distance in x to translate
//	- y: distance in y to translate
//	- z: distance in z to translate
//-----------------------------------------------------------------------------
void CMatrix::SetMatrixTranslation(	_In_ float x,
									_In_ float y,
									_In_ float z)
{
	D3DXMatrixTranslation(&m_DXMatrix, x, y, z);
}

void CMatrix::SetTransformationMatrix(_In_ const CVector3& scale,
									  _In_ const CVector3& translation)
{
	D3DXMatrixTransformation(&m_DXMatrix,NULL,NULL,&scale.GetD3DXVECTOR3(),NULL,NULL,&translation.GetD3DXVECTOR3());
}
#endif
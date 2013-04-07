#include "Matrix.h"
#include "Vector3.h"


CMatrix::~CMatrix(void)
{
}

#if (GRAPHICSAPI == DIRECTX10)
CMatrix::CMatrix(void)
{
	m_DXMatrix = D3DXMATRIX();
}
CMatrix::CMatrix(D3DXMATRIX DXMatrix)
{
	m_DXMatrix = DXMatrix;
}

D3DXMATRIX* CMatrix::GetD3DXMATRIX(void)
{
	return &m_DXMatrix;
}

CMatrix CMatrix::operator*=(CMatrix that)
{
	m_DXMatrix *= *that.GetD3DXMATRIX();
	return *this;
}

CMatrix CMatrix::operator*(CMatrix that)
{
	return CMatrix(m_DXMatrix * *that.GetD3DXMATRIX());
}

void CMatrix::CreateIdentityMatrix( _Out_ CMatrix& pOut)
{
	D3DXMATRIX DXMatrix;
	D3DXMatrixIdentity(&DXMatrix);
	pOut.m_DXMatrix = DXMatrix;
}

//-----------------------------------------------------------------------------
// Name: CreateMatrixLookAtLH
// Type: Factory
// Vis: Public
// Desc: Creates a Look At matrix through the DirectX Math Library.
// Inputs:
//	- pEye: Position vector
//	- pAt: Toward vector
//	- pUp: Up vector (usually can be (0,1,0)
// Outputs:
//	- pOut: A CMatrix to store the new matrix in
//-----------------------------------------------------------------------------
void CMatrix::CreateMatrixLookAtLH(	_In_ CVector3* pEye,
									_In_ CVector3* pAt,
									_In_ CVector3* pUp,
									_Out_ CMatrix& pOut)
{
	D3DXMATRIX DXMatrix;
	D3DXVECTOR3 eye = D3DXVECTOR3(pEye->GetD3DXVECTOR3());
	D3DXVECTOR3 at = D3DXVECTOR3(pAt->GetD3DXVECTOR3());
	D3DXVECTOR3 up = D3DXVECTOR3(pUp->GetD3DXVECTOR3());
	D3DXMatrixLookAtLH(&DXMatrix, &eye, &at, &up);
	pOut.m_DXMatrix = DXMatrix;
}

//-----------------------------------------------------------------------------
// Name: CreateMatrixPerspectiveFovLH
// Type: Factory
// Vis: Public
// Desc: Creates a perspective projection matrix through the DirectX Math 
//		 Library.
// Inputs:
//	- vFov: vertical field of view
//	- aspectRatio: aspect ratio of the vew plane
//	- zNearPlane: z distance to the near plane
//	- zFarPlane: z distance to the far plane
// Outputs:
//	- pOut: A CMatrix to store the new matrix in
//-----------------------------------------------------------------------------
void CMatrix::CreateMatrixPerspectiveFovLH(	_In_ float vFov,
											_In_ float aspectRatio,
											_In_ float zNearPlane,
											_In_ float zFarPlane,
											_Out_ CMatrix& pOut)
{
	D3DXMATRIX DXMatrix;
	D3DXMatrixPerspectiveFovLH(&DXMatrix, vFov, aspectRatio, zNearPlane, zFarPlane);
	pOut.m_DXMatrix = DXMatrix;
}

//-----------------------------------------------------------------------------
// Name: CreateMatrixRotationY
// Type: Factory
// Vis: Public
// Desc: Creates matrix that rotates around Y through the DirectX Math Library.
// Inputs:
//	- angle: the angle to rotate around the Y axis
// Outputs:
//	- pOut: A CMatrix to store the new matrix in
//-----------------------------------------------------------------------------
void CMatrix::CreateMatrixRotationY(_In_ float angle,
									_Out_ CMatrix& pOut)
{
	D3DXMATRIX DXMatrix;
	D3DXMatrixRotationY(&DXMatrix, angle);
	pOut.m_DXMatrix = DXMatrix;
}
//-----------------------------------------------------------------------------
// Name: CreateMatrixTranslation
// Type: Factory
// Vis: Public
// Desc: Creates a translation matrix through the DirectX Math Library.
// Inputs:
//	- x: distance in x to translate
//	- y: distance in y to translate
//	- z: distance in z to translate
// Outputs:
//	- pOut: A CMatrix to store the new matrix in
//-----------------------------------------------------------------------------
void CMatrix::CreateMatrixTranslation(	_In_ float x,
										_In_ float y,
										_In_ float z,
										_Out_ CMatrix& pOut)
{
	D3DXMATRIX DXMatrix;
	D3DXMatrixTranslation(&DXMatrix, x, y, z);
	pOut.m_DXMatrix = DXMatrix;
}

#endif
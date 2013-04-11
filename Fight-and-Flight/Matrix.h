#pragma once
#include "Vector3.h"
#if (GRAPHICSAPI == DIRECTX10)
#include <D3DX10.h>
#endif

class CMatrix
{
public:
	CMatrix(void);
	~CMatrix(void);
	static void CreateIdentityMatrix(CMatrix& pOut);
	static void CreateMatrixLookAtLH(	_In_ CVector3* pEye,
										_In_ CVector3* pAt,
										_In_ CVector3* pUp,
										_Out_ CMatrix& pOut);
	static void CreateMatrixPerspectiveFovLH(	_In_ float vFov,
												_In_ float aspectRatio,
												_In_ float zNearPlane,
												_In_ float zFarPlane,
												_Out_ CMatrix& pOut);
	static void CreateMatrixRotationY(	_In_ float angle,
										_Out_ CMatrix& pOut);
	static void CreateMatrixTranslation(	_In_ float x,
											_In_ float y,
											_In_ float z,
											_Out_ CMatrix& pOut);
	CMatrix operator*=(const CMatrix& that);
	CMatrix operator*(const CMatrix& that);
#if (GRAPHICSAPI == DIRECTX10)
public:
	D3DXMATRIX GetD3DXMATRIX(void) const;
	CMatrix(D3DXMATRIX DXMatrix);
private:
	D3DXMATRIX m_DXMatrix;
#endif
};


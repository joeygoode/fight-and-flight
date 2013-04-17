#pragma once
#include "GFXAPIBase.h"

class CMatrix : CGFXAPIBase
{
	friend class CEffectVariable;
public:
	//Constructs a new matrix defaults to the identity matrix.
	CMatrix(void);
	//Destroys a matrix
	~CMatrix(void);
	// Sets the input matrix equal to the identity matrix
	void SetIdentityMatrix();
	// Stores a PerspectiveFoVLH matrix in the given matrix
	void SetMatrixPerspectiveFovLH(	_In_ float vFov,
									_In_ float aspectRatio,
									_In_ float zNearPlane,
									_In_ float zFarPlane);
	// Stores a Y rotation matrix in the given matrix.
	void SetMatrixRotationY(_In_ float angle);
	// Stores a translation matrix in the given matrix.
	void SetMatrixTranslation(	_In_ float x,
								_In_ float y,
								_In_ float z);
	// Stores a LookAtLH matrix in the given matrix.
	void SetMatrixLookAtLH( const CVector3& Eye,
							const CVector3& At,
							const CVector3& Up);
	// Stores a transformation matrix in the given matrix.
	void SetTransformationMatrix(	const CVector3& scale,
									const CQuaternion& orientation,
									const CVector3& translation);
	// *= operator overload.  Defaults to the wrapped implemations *= overload.
	CMatrix operator*=(const CMatrix& that);
	// * operator overload. Defaults to the wrapped implemations * overload.
	CMatrix operator*(const CMatrix& that);
// Use these functions if we're using DirectX 10
#if (GRAPHICSAPI == DIRECTX10)
	friend class CDirectXManager;
private:
	// Gets a D3DXMATRIX out of the given Matrix
	D3DXMATRIX GetD3DXMATRIX(void) const;
	// Creates a new CMatrix from the given D3DXMATRIX
	CMatrix(D3DXMATRIX DXMatrix);
	// The wrapped D3DXMATRIX
	D3DXMATRIX m_DXMatrix;
#endif
};


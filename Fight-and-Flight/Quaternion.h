#pragma once
#include "GFXAPIBase.h"
class CQuaternion : CGFXAPIBase
{
	friend class CMatrix;
public:
	CQuaternion(void);
	~CQuaternion(void);
	CQuaternion SetPitchYawRoll(CVector3 vec);
	CQuaternion operator*=(const CQuaternion& that);
	CQuaternion operator*(const CQuaternion& that);
#if (GRAPHICSAPI == DIRECTX10)
private:
	CQuaternion(D3DXQUATERNION DXquaternion);
	D3DXQUATERNION GetD3DXQUATERNION(void) const;
	D3DXQUATERNION m_DXQuaternion;
#endif
};

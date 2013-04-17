#include "Quaternion.h"
#include "Vector3.h"


CQuaternion::CQuaternion(void)
{
#if (GRAPHICSAPI == DIRECTX10)
	m_DXQuaternion = D3DXQUATERNION(0,0,0,0);
#endif
}


CQuaternion::~CQuaternion(void)
{
}

CQuaternion CQuaternion::SetPitchYawRoll(CVector3 vec)
{
#if (GRAPHICSAPI == DIRECTX10)
	D3DXQuaternionRotationYawPitchRoll(&m_DXQuaternion, vec.GetY(), vec.GetX(), vec.GetZ());
#endif
	return *this;
}
#if (GRAPHICSAPI == DIRECTX10)
CQuaternion CQuaternion::operator*=(const CQuaternion& that)
{
	m_DXQuaternion *= that.m_DXQuaternion;
	return *this;
}

CQuaternion CQuaternion::operator*(const CQuaternion& that)
{
	return m_DXQuaternion * m_DXQuaternion;
}

CQuaternion::CQuaternion(D3DXQUATERNION DXQuaternion)
{
	m_DXQuaternion = DXQuaternion;
}
D3DXQUATERNION CQuaternion::GetD3DXQUATERNION(void) const
{
	return m_DXQuaternion;
}
#endif
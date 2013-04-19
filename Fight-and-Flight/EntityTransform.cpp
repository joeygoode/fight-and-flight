#include "EntityTransform.h"
#include "Matrix.h"

CEntityTransform::CEntityTransform(void)
{
}


CEntityTransform::~CEntityTransform(void)
{
}

const CVector3& CEntityTransform::GetPosition(void) const
{
	return m_Position;
}

const CQuaternion& CEntityTransform::GetOrientation(void) const
{
	return m_Orientation;
}

const CVector3& CEntityTransform::GetScale(void) const
{
	return m_Scale;
}

void CEntityTransform::Translate(float x, float y, float z)
{
	m_Position += CVector3(x,y,z);
}

void CEntityTransform::Translate(const CVector3& vec)
{
	m_Position += vec;
}

void CEntityTransform::Rotate(float x, float y, float z)
{
	m_Orientation *= CQuaternion().SetPitchYawRoll(CVector3(x,y,z));
}

void CEntityTransform::Rotate(const CVector3& vec)
{
	m_Orientation *= CQuaternion().SetPitchYawRoll(vec);
}

void CEntityTransform::Scale(float x, float y, float z)
{
	m_Scale.SetX(m_Scale.GetX() * x);
	m_Scale.SetY(m_Scale.GetY() * y);
	m_Scale.SetZ(m_Scale.GetZ() * z);
}

void CEntityTransform::Scale(const CVector3& vec)
{
	m_Scale.SetX(m_Scale.GetX() * vec.GetX());
	m_Scale.SetY(m_Scale.GetY() * vec.GetY());
	m_Scale.SetZ(m_Scale.GetZ() * vec.GetZ());
}

void CEntityTransform::SetPosition(float x, float y, float z)
{
	m_Position.SetX(x);
	m_Position.SetY(y);
	m_Position.SetZ(z);
}

void CEntityTransform::SetPosition(const CVector3& vec)
{
	m_Position.Set(vec);
}

void CEntityTransform::SetOrienation(float x, float y, float z)
{
	m_Orientation.SetPitchYawRoll(CVector3(x,y,z));
}

void CEntityTransform::SetOrientation(const CVector3& vec)
{
	m_Orientation.SetPitchYawRoll(vec);
}

void CEntityTransform::SetScale(float x, float y, float z)
{
	m_Scale.SetX(x);
	m_Scale.SetY(y);
	m_Scale.SetZ(z);
}

void CEntityTransform::SetScale(const CVector3& vec)
{
	m_Scale.Set(vec);
}

CMatrix CEntityTransform::GetMatrix(void) const
{
	CMatrix matrix = CMatrix();
	matrix.SetTransformationMatrix(m_Scale,m_Orientation,m_Position);
	return matrix;
}
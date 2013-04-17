#include "EntityPhysics.h"
#include "EntityTransform.h"


CEntityPhysics::CEntityPhysics(void)
{
}


CEntityPhysics::~CEntityPhysics(void)
{
}

void CEntityPhysics::Update(float ElapsedTime, CEntityTransform* transform)
{
	transform->Translate(m_Velocity * ElapsedTime);
	transform->Rotate(m_RotationalVelocity * ElapsedTime);
}

void CEntityPhysics::SetVelocity(const CVector3& vec)
{
	m_Velocity.Set(vec);
}

void CEntityPhysics::SetVelocity(float x, float y, float z)
{
	m_Velocity.Set(CVector3(x,y,z));
}

void CEntityPhysics::SetRotationalVelocity(const CVector3& vec)
{
	m_RotationalVelocity.Set(vec);
}

void CEntityPhysics::SetRotationalVelocity(float x, float y, float z)
{
	m_RotationalVelocity.Set(CVector3(x,y,z));
}
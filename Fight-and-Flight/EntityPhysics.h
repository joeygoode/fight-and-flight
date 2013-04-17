#pragma once
#include "Vector3.h"

class CEntityTransform;

class CEntityPhysics
{
	CVector3 m_Velocity;
	CVector3 m_RotationalVelocity;
public:
	CEntityPhysics(void);
	~CEntityPhysics(void);
	void Update(float ElapsedTime, CEntityTransform* transform);
	void SetVelocity(const CVector3& vec);
	void SetVelocity(float x, float y, float z);
	void SetRotationalVelocity(const CVector3& vec);
	void SetRotationalVelocity(float x, float y, float z);
};


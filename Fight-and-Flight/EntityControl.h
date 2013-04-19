#pragma once

class CEntityPhysics;
class CEntityTransform;
class CEntity;

class CEntityControl
{
	bool m_PlayerControl;
	float m_LastShot;
public:
	CEntityControl(void);
	~CEntityControl(void);
	void Update(float TotalTime, CEntityPhysics* pPhysics, CEntityTransform* pTransform, CEntity* pEntity);
	void SetControl(bool control);
};


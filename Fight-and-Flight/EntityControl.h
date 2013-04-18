#pragma once

class CEntityPhysics;
class CEntityTransform;

class CEntityControl
{
	bool m_playercontrol;
public:
	CEntityControl(void);
	~CEntityControl(void);
	void Update(CEntityPhysics* pPhysics, CEntityTransform* pTransform);
	void SetControl(bool control);
};


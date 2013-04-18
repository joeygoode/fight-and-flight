#pragma once

class CEntityPhysics;
class CEntityTransform;

class CEntityControl
{
public:
	CEntityControl(void);
	~CEntityControl(void);
	void Update(CEntityPhysics* pPhysics, CEntityTransform* pTransform);
};


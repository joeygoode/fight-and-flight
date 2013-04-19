#include "EntityControl.h"
#include "EntityPhysics.h"
#include "EntityTransform.h"
#include "Entity.h"
#include "KeyboardControl.h"
#include "EntityManager.h"
#include "Game.h"

CEntityControl::CEntityControl(void)
{
}


CEntityControl::~CEntityControl(void)
{
}

void CEntityControl::Update(float TotalTime, CEntityPhysics* pPhysics, CEntityTransform* pTransform, CEntity* pEntity)
{
	if (m_PlayerControl)
	{
		INPUT_COMMAND com = CKeyboardControl::Get()->GetInput();
		CVector3 currentpos = pTransform->GetPosition();
		if (com == MOVE_LEFT && currentpos.GetX() > -9.6f)
			pTransform->Translate(-0.1f,0.0f,0.0f);
		if (com == MOVE_RIGHT && currentpos.GetX() < 9.6f)
			pTransform->Translate(0.1f,0.0f,0.0f);
		if (com == FIRE && TotalTime - m_LastShot > 1)
		{
			ENTITY_DESC desc;
			CEntityManager::Get()->GetEntityDescFromFile("bullet.xml",desc);
			desc.position = pTransform->GetPosition();
			desc.faction = pEntity->GetFaction();
			if(CEntityManager::Get()->AllocateEntityDynamic(desc))
				m_LastShot = TotalTime;
		}
	}
}
void CEntityControl::SetControl(bool control)
{
	m_PlayerControl = control;
}
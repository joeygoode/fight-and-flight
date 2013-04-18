#include "EntityControl.h"
#include "EntityPhysics.h"
#include "EntityTransform.h"
#include "KeyboardControl.h"

CEntityControl::CEntityControl(void)
{
}


CEntityControl::~CEntityControl(void)
{
}

void CEntityControl::Update(CEntityPhysics* pPhysics, CEntityTransform* pTransform)
{
	if (m_playercontrol)
	{
		INPUT_COMMAND com = CKeyboardControl::Get()->GetInput();
		CVector3 currentpos = pTransform->GetPosition();
		if (com == MOVE_LEFT && currentpos.GetX() > -9.6f)
			pTransform->Translate(-0.1f,0.0f,0.0f);
		if (com == MOVE_RIGHT && currentpos.GetX() < 9.6f)
			pTransform->Translate(0.1f,0.0f,0.0f);
	}
}
void CEntityControl::SetControl(bool control)
{
	m_playercontrol = control;
}
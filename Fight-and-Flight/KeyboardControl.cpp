#include "KeyboardControl.h"
#include <Windows.h>

CKeyboardControl* CKeyboardControl::s_Singleton = 0;

CKeyboardControl* CKeyboardControl::Get(void)
{
	if (!s_Singleton)
		s_Singleton = new CKeyboardControl();
	return s_Singleton;
}

void CKeyboardControl::Clear(void)
{
	if (s_Singleton)
		delete s_Singleton;
	s_Singleton = 0;
}

CKeyboardControl::CKeyboardControl(void)
{
}


CKeyboardControl::~CKeyboardControl(void)
{
}

INPUT_COMMAND CKeyboardControl::GetInput(void)
{
	if (GetAsyncKeyState(VK_LEFT))
		return MOVE_LEFT;
	else if (GetAsyncKeyState(VK_RIGHT))
		return MOVE_RIGHT;
	else if (GetAsyncKeyState(VK_SPACE))
		return FIRE;
	return NONE;
}
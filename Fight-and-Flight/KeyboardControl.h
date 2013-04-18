#pragma once

enum INPUT_COMMAND
{
	NONE,
	MOVE_RIGHT,
	MOVE_LEFT,
	FIRE
};

class CKeyboardControl
{
	static CKeyboardControl* s_Singleton;
public:
	static CKeyboardControl* Get(void);
	static void Clear(void);
	INPUT_COMMAND GetInput(void);
private:
	CKeyboardControl(void);
	~CKeyboardControl(void);
};


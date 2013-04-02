#pragma once
#include "mover.h"
class CControllerMover :
	public CMover
{
public:
	CControllerMover(int* width, int* height, D3DXVECTOR2* position, float* rotation, D3DXVECTOR2* scale, int* framenum);
	~CControllerMover(void);
	void			Advance();
	bool			IsTimeToKill();
private:
	int* m_FrameNum;
};


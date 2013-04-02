#pragma once
#include "mover.h"
class CDynamicMover :
	public CMover
{
public:
	CDynamicMover(int* width, int* height, D3DXVECTOR2* position, float* rotation, D3DXVECTOR2* scale, D3DXVECTOR2 velocity, float rotationalvelocity);
	~CDynamicMover(void);
	void			Advance();
	bool			IsTimeToKill();
	D3DXVECTOR2		GetNextPosition() const;
private:
	D3DXVECTOR2*	m_Velocity;
	float			m_RotationalVelocity;
};


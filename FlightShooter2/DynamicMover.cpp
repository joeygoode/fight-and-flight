#include "DynamicMover.h"


CDynamicMover::CDynamicMover(int* width, int* height, D3DXVECTOR2* position, float* rotation, D3DXVECTOR2* scale, D3DXVECTOR2 velocity, float rotationalvelocity)
	:CMover(width, height, position, rotation, scale)
{
	m_Velocity = new D3DXVECTOR2(velocity.x, velocity.y);
	m_RotationalVelocity = rotationalvelocity;
}


CDynamicMover::~CDynamicMover(void)
{
	delete m_Velocity;
}

void			CDynamicMover::Advance()
{
	*m_Position = *m_NextPosition;
	D3DXVec2Add(m_NextPosition,m_NextPosition,m_Velocity);
	*m_Rotation += m_RotationalVelocity;
	if (*m_Rotation > 360)
		*m_Rotation -= 360;
	else if (*m_Rotation < 0)
		*m_Rotation += 360;
}
bool			CDynamicMover::IsTimeToKill()
{
	bool offtop = m_Position->y + *m_Height < 0;
	bool offleft = m_Position->x + *m_Width < 0;
	bool offbottom = m_Position->y - *m_Height > SCREENH;
	bool offright = m_Position->x - *m_Width > SCREENW;
	return offtop || offleft || offbottom || offright;
}
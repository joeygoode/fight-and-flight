#include "Mover.h"


KEYFRAME::KEYFRAME(D3DXVECTOR2 pos, float rot, int frames, KEYFRAME* nextp)
{
	position		= pos;
	rotation		= rot;
	framesuntilnext = frames;
	next			= nextp;
}

CMover::CMover(int* width,int* height,D3DXVECTOR2* position,float* rotation,D3DXVECTOR2* scale)
	: CComponent(width, height, position, rotation, scale)
{
	m_NextPosition = new D3DXVECTOR2(position->x, position->y);
}


CMover::~CMover(void)
{

}

D3DXVECTOR2 CMover::GetNextPosition() const
{
	return *m_NextPosition;
}
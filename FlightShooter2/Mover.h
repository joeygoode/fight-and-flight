#pragma once
#include "Component.h"
#include <vector>

typedef struct KEYFRAME KEYFRAME;

struct KEYFRAME
{
	D3DXVECTOR2 position;
	float		rotation;
	int			framesuntilnext;
	KEYFRAME*	next;

	KEYFRAME() {};
	KEYFRAME(D3DXVECTOR2 position, float rotation, int framesuntilnext, KEYFRAME* next);
};

class CMover
	: public CComponent
{
public:
	CMover(int* width, int* height, D3DXVECTOR2* position, float* rotation, D3DXVECTOR2* scale);
	~CMover(void);
	virtual void			Advance() = 0;
	virtual bool			IsTimeToKill() = 0;
	D3DXVECTOR2				GetNextPosition() const;
protected:
	D3DXVECTOR2*			m_NextPosition;
};



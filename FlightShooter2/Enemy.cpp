#include "Enemy.h"



CEnemy::CEnemy(int width, int height, vector<KEYFRAME*> keyframes,
			   vector<D3DXVECTOR2> hitboxes, bool animseqishoriz, int numroworcol,
				D3DXVECTOR2 scale, int horizoffset, int vertoffset,
			   int delim, int framenum, int value)
	: CEntity(width, height, keyframes, hitboxes, animseqishoriz, numroworcol, 
	scale, horizoffset, vertoffset, delim, framenum, forward_list<CEntity>())
{
	m_Value = value;
}


CEnemy::~CEnemy(void)
{
}

int CEnemy::GetValue()
{
	return m_Value;
}
#pragma once
#include "Entity.h"

class CEnemy :
	public CEntity
{
public:
	//Destructor for Enemies
	~CEnemy(void);
	int GetValue();
protected:
	//Constructor for Enemies
	CEnemy(int width, int height, vector<KEYFRAME*> keyframes,
			   vector<D3DXVECTOR2> hitboxes, bool animseqishoriz, int numroworcol,
				D3DXVECTOR2 scale, int horizoffset, int vertoffset,
			   int delim, int framenum, int value);
	int m_Value;
};

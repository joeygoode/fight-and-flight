#pragma once
#include "MyDirectX.h"
#include "Entity.h"

class CPlayerProjectile
	: public CEntity
{
public:
	~CPlayerProjectile();
protected:
	//Constructor for projectiles
	CPlayerProjectile(int width, int height, D3DXVECTOR2 position, D3DXVECTOR2 velocity,
			   vector<D3DXVECTOR2> hitboxes, bool animseqishoriz, int numroworcol, float rotation, float rotationalvelocity,
				D3DXVECTOR2 scale, int horizoffset, int vertoffset,
			   int delim, int framenum);
};

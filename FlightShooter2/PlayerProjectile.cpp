#include "PlayerProjectile.h"


CPlayerProjectile::CPlayerProjectile(int width, int height, D3DXVECTOR2 position, D3DXVECTOR2 velocity,
			   vector<D3DXVECTOR2> hitboxes, bool animseqishoriz, int numroworcol, float rotation, float rotationalvelocity,
				D3DXVECTOR2 scale, int horizoffset, int vertoffset,
			   int delim, int framenum)
	: CEntity(width, height, position, velocity, hitboxes, animseqishoriz, numroworcol, 
	rotation, rotationalvelocity, scale, horizoffset, vertoffset, delim, framenum, forward_list<CEntity>())
{
}

CPlayerProjectile::~CPlayerProjectile()
{
}
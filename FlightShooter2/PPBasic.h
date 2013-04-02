#pragma once
#include "PlayerProjectile.h"

class CPPBasic :
	public CPlayerProjectile
{
public:
	CPPBasic(D3DXVECTOR2 position);
	~CPPBasic();
	static vector<D3DXVECTOR2> GenerateHitboxVector();
};

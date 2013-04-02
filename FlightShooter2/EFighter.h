#pragma once
#include "Enemy.h"

class CEFighter :
	public CEnemy
{
public:
	//Constructor for enemy fighters
	CEFighter(vector<KEYFRAME*> keyframes);
	//Destructor for enemy fighters
	~CEFighter(void);
	static vector<D3DXVECTOR2>	GenerateHitboxVector();
	static void					LoadData();
};

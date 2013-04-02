#pragma once
#include "MyDirectX.h"
#include "Entity.h"
class CPlayer
	:public CEntity
{
public:
	//Constructor for Players
	CPlayer();
	//Destructors for Players
	~CPlayer();
	// Reset the player's position
	void					ResetPlayer();
	void					DrawExtras();
	void					GiveMoney(int money);
private:
	static vector<D3DXVECTOR2> GenerateHitboxVector();
	int m_Cash;
	LPD3DXFONT m_OverlayFont;
};

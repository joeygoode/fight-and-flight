#pragma once
#include "MyDirectX.h"
#include <list>

class CPlayerProjectile;
class CEnemy;
class CPlayer;

class CLevel
{
public:
	// Construct a level from a list of enemies
	CLevel(list<CEnemy*> enemies);
	// Destroy a level
	~CLevel();
	// Is the level complete
	bool				IsComplete();
	// Update the level
	void				Update(CPlayer* player);
	// Draw the level
	void				Draw(LPDIRECT3DTEXTURE9 spritesheet);
	void				LoadData();
private:
	// List of enemies
	list<CEnemy*> m_Enemies;
	// List of projectiles fired by the player
	list<CPlayerProjectile*> m_PlayerProjectiles;
	// Background
	LPDIRECT3DSURFACE9 m_background;
	// Frames since last shot
	int m_Frames;
};

#pragma once
#include "MyDirectX.h"
#include <vector>

class CPlayer;
class CLevel;

class CWorld
{
public:
	//Constructor for the game world
	CWorld();
	//Destructor for the game world
	~CWorld();
	//Load data like textures (so we can check if it fails)
	void LoadData();
	//Update the world
	void Update();
	//Draw the world
	void Draw();
private:
	//The player
	CPlayer* m_Player;
	//the current level
	int m_CurrentLevel;
	//a vector of all the levels
	vector<CLevel*> m_Levels;
	// a pointer to the sprite sheet (will be NULL until load data is called)
	LPDIRECT3DTEXTURE9 m_SpriteSheet;
	// is the game over (currently always returns false)
	void GameOver();
};

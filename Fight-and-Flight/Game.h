#pragma once
#include "DirectXManager.h"
using namespace std;

class CMesh;

class CGame
{
public:

	static bool CreateGame(_In_ HWND* hWnd, _Out_ CGame* &Game);
	// Destroys the game (and releases all components)
	~CGame(void);
	// Loop through this method to play the game
	bool UpdateAndRender(void);
private:
	CGame(void);
	// dx manager
	CDirectXManager* m_pDirectX;
	// mesh
	CMesh* m_pMesh;
	CEffect* m_pEffect;
};


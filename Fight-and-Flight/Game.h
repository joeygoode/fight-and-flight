#pragma once
#include "GFXAPIBase.h"
using namespace std;

#include "FontObj.h"
#include "Matrix.h"

class CMeshManager;

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
	CMeshManager* m_pMeshManager;
	CEffect* m_pEffect;
	CFontObj DebugFont;
	CMatrix	ViewMatrix;
	CMatrix	ProjectionMatrix;
	CMatrix	WorldMatrix;
};


#pragma once
#include "GFXAPIBase.h"
using namespace std;

#include "FontObj.h"
#include "Matrix.h"

class CMeshManager;

class CGame
{
	CEffect* m_pEffect;
	CFontObj DebugFont;
	CMatrix	ViewMatrix;
	CMatrix	ProjectionMatrix;
	CMatrix	WorldMatrix;
	int		m_CurrentTime;
	int		m_PreviousTime;
	int		m_TotalTime;
public:

	static bool CreateGame(_In_ HWND* hWnd, _Out_ CGame* &Game);
	// Destroys the game (and releases all components)
	~CGame(void);
	// Loop through this method to play the game
	bool UpdateAndRender(void);
private:
	CGame(void);

};


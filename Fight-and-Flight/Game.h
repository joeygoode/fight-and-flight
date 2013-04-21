#pragma once
#include "GFXAPIBase.h"
using namespace std;

#include "FontObj.h"
#include "Matrix.h"
#include "Effect.h"

class CMeshManager;


class CGame
{
	CFontObj DebugFont;
	CMatrix	ViewMatrix;
	CMatrix	ProjectionMatrix;
	int oldeffectnumber;
	volatile int	m_CurrentTime;
	volatile int	m_PreviousTime;
	volatile int	m_TotalTime;
public:

	static bool CreateGame(_In_ HWND* hWnd, _Out_ CGame* &Game);
	// Destroys the game (and releases all components)
	~CGame(void);
	// Loop through this method to play the game
	bool UpdateAndRender(void);
private:
	CGame(void);

};


#include "Game.h"
#include "Mesh.h"

//-----------------------------------------------------------------------------
// Name: CGame
// Type: Constructor
// Vis: Private
// Desc: Creates a new instance of a CGame class and initializes its variables.
//-----------------------------------------------------------------------------
CGame::CGame(void)
{
	m_pDirectX = NULL;
	m_pMesh = NULL;
}

//-----------------------------------------------------------------------------
// Name: ~CGame
// Type: Destructor
// Vis: Public
// Desc: Destroys this instance of the CGame class and frees memory.
//-----------------------------------------------------------------------------
CGame::~CGame(void)
{
	delete m_pDirectX;
	delete m_pMesh;
}
	
//-------------------------------------------------------------------------
// Name: CreateGame
// Type: Factory (Static)
// Vis: Public
// Desc: Creates a new instance of the CGame class and initializes it.
// Inputs: 
//	- hWnd: A pointer to the window being used by this application.
// Outputs:
//	- pGame: A pointer to newly created CGame instance.
//  - return: False if the call failed.
//-------------------------------------------------------------------------
bool CGame::CreateGame(_In_ HWND* hWnd, _Out_ CGame* &pGame)
{
	pGame = new CGame();
	pGame->m_pDirectX = new CDirectXManager();
	if (!pGame->m_pDirectX->initialize(hWnd))
		return false;
	vector<vertex> vertices = vector<vertex>();
	vertices.push_back(vertex( D3DXVECTOR3(-1,1,-1), D3DXVECTOR4(1,0,0,1)));	//front top left
	vertices.push_back(vertex( D3DXVECTOR3(1,1,-1), D3DXVECTOR4(0,1,0,1)));		//front top right
	vertices.push_back(vertex( D3DXVECTOR3(-1,-1,-1), D3DXVECTOR4(0,0,1,1)));	//front bottom left
	vertices.push_back(vertex( D3DXVECTOR3(1,-1,-1), D3DXVECTOR4(1,1,0,1)));	//front bottom right

	vertices.push_back(vertex( D3DXVECTOR3(-1,1,1), D3DXVECTOR4(1,0,0,1)));		//back top left
	vertices.push_back(vertex( D3DXVECTOR3(1,1,1), D3DXVECTOR4(0,1,0,1)));		//back top right
	vertices.push_back(vertex( D3DXVECTOR3(-1,-1,1), D3DXVECTOR4(0,0,1,1)));	//back bottom left
	vertices.push_back(vertex( D3DXVECTOR3(1,-1,1), D3DXVECTOR4(1,1,0,1)));		//back bottom right

	//create indexes for a cube 
	unsigned int i[36] = {	2,0,3,3,1,0,							
							3,1,7,7,5,1,							
							6,4,2,2,0,4,							
							7,5,6,6,4,5,							
							0,4,1,1,5,4,							
							6,2,7,7,3,2 };	
	vector<UINT> indices = vector<UINT>();
	indices.assign(i,i+36);
	if (!pGame->m_pDirectX->CreateMesh(vertices,indices,6,pGame->m_pMesh))
		return false;

}
	
//-----------------------------------------------------------------------------
// Name: UpdateAndRender
// Type: Method
// Vis: Public
// Desc: Loop on this method to run the game.
//-----------------------------------------------------------------------------
bool CGame::UpdateAndRender(void)
{
	m_pDirectX->BeginScene();
	m_pDirectX->renderScene(m_pMesh);
	m_pDirectX->EndScene();
	return true;
}
#include "Game.h"
#include "Mesh.h"
#include "Effect.h"
#include <sstream>
#include <Windows.h>
using namespace std;

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
	m_pEffect = NULL;
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
	delete m_pEffect;
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

	vector<string> names = vector<string>(3);
	names[0] = "World";
	names[1] = "Projection";
	names[2] = "View";
	vector<string> types = vector<string>(3);
	for (int i = 0; i < 3; i++)
		types[i] = "matrix";

	if(!pGame->m_pDirectX->CreateShader("basicEffect.fx", names, types, pGame->m_pEffect))
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

	pGame->pDebugFont = pGame->m_pDirectX->MakeFont("Arial", 14);
	return true;
}
	
//-----------------------------------------------------------------------------
// Name: UpdateAndRender
// Type: Method
// Vis: Public
// Desc: Loop on this method to run the game.
//-----------------------------------------------------------------------------
bool CGame::UpdateAndRender(void)
{
	int time = timeGetTime();
	m_pDirectX->BeginScene();
		//rotate object - rotation should be timer based but i'm lazy
	
	
	CMatrix temp = CMatrix();
	static float r = 0;	
	r += 0.0001f;

	CVector3 rcOrigin(-14, 0, 0);

	//draw lots of cubes
	for ( int cols = 0; cols < 10; cols++ )
	{
		for ( int rows = 0; rows < 15; rows ++ )
		{
			//position cube
			CMatrix::CreateMatrixRotationY(r,m_pDirectX->WorldMatrix);
			CMatrix::CreateMatrixTranslation(rcOrigin.GetX() + 4 * cols, 0, rcOrigin.GetZ() + 4 * rows,  temp);
			m_pDirectX->WorldMatrix *= temp;
			m_pEffect->SetVariableByName("World",m_pDirectX->WorldMatrix);

			//draw cube
			for( UINT p = 0; p < m_pEffect->GetTechDesc().Passes; p++ )
			{
				//apply technique
				m_pEffect->GetTechnique()->GetPassByIndex( p )->Apply( 0 );
				m_pMesh->Draw();
			}
		}
	}
	time = timeGetTime() - time;
	ostringstream convert;
	convert << time;
	m_pDirectX->pSprite->Begin( D3DX10_SPRITE_SAVE_STATE | D3DX10_SPRITE_SORT_DEPTH_BACK_TO_FRONT);
	m_pDirectX->FontPrint(pDebugFont,20,20,convert.str(),D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	m_pDirectX->pSprite->Flush();
	m_pDirectX->pSprite->End();
	m_pDirectX->ResetStates();
	m_pDirectX->EndScene();
	return true;
}
#include <sstream>
#include <Windows.h>
#include <iostream>
using namespace std;

#include "Game.h"
#include "Mesh.h"
#include "Effect.h"
#include "Color.h"
#include "Vector3.h"
#include "MeshManager.h"
#include "EntityManager.h"

//-----------------------------------------------------------------------------
// Name: CGame
// Type: Constructor
// Vis: Private
// Desc: Creates a new instance of a CGame class and initializes its variables.
//-----------------------------------------------------------------------------
CGame::CGame(void)
{
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
	delete m_pEffect;
	CDirectXManager::Clear();
	CMeshManager::Clear();
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
	CDirectXManager* pDirectX = CDirectXManager::Get();
	if (!pDirectX->initialize(hWnd))
		return false;

	vector<string> names = vector<string>(3);
	names[0] = "World";
	names[1] = "Projection";
	names[2] = "View";
	vector<string> types = vector<string>(3);
	for (int i = 0; i < 3; i++)
		types[i] = "matrix";

	if(!pDirectX->CreateShader("basicEffect.fx", names, types, pGame->m_pEffect))
		return false;

	CVector3 camera[] = {	CVector3(0.0f, 5.0f, -10.0f),
							CVector3(0.0f, 0.0f, 1.0f),
							CVector3(0.0f, 1.0f, 0.0f)	};
	
	pGame->ViewMatrix.SetMatrixLookAtLH(camera[0], camera[1], camera[2]);		
	pGame->ProjectionMatrix.SetMatrixPerspectiveFovLH((float)D3DX_PI * 0.5f, (float)pDirectX->width/(float)pDirectX->height, 0.1f, 100.0f);

	pGame->m_pEffect->SetVariableByName("View", pGame->ViewMatrix);
	pGame->m_pEffect->SetVariableByName("Projection", pGame->ProjectionMatrix);

	vector<vertex> vertices = vector<vertex>();
	vertices.push_back(vertex( D3DXVECTOR3(-1,1,-1), D3DXCOLOR(1,0,0,1)));	//front top left
	vertices.push_back(vertex( D3DXVECTOR3(1,1,-1), D3DXCOLOR(0,1,0,1)));	//front top right
	vertices.push_back(vertex( D3DXVECTOR3(-1,-1,-1), D3DXCOLOR(0,0,1,1)));	//front bottom left
	vertices.push_back(vertex( D3DXVECTOR3(1,-1,-1), D3DXCOLOR(1,1,0,1)));	//front bottom right

	vertices.push_back(vertex( D3DXVECTOR3(-1,1,1), D3DXCOLOR(1,0,0,1)));	//back top left
	vertices.push_back(vertex( D3DXVECTOR3(1,1,1), D3DXCOLOR(0,1,0,1)));	//back top right
	vertices.push_back(vertex( D3DXVECTOR3(-1,-1,1), D3DXCOLOR(0,0,1,1)));	//back bottom left
	vertices.push_back(vertex( D3DXVECTOR3(1,-1,1), D3DXCOLOR(1,1,0,1)));	//back bottom right

	//create indexes for a cube 
	unsigned int i[36] = {	2,0,3,3,1,0,							
							3,1,7,7,5,1,							
							6,4,2,2,0,4,							
							7,5,6,6,4,5,							
							0,4,1,1,5,4,							
							6,2,7,7,3,2 };	
	vector<UINT> indices = vector<UINT>();
	indices.assign(i,i+36);
	if (!CMeshManager::Get()->AllocateMesh(vertices,indices,6,"cube"))
		return false;
	CVector3 rcOrigin = CVector3(-14, 0, 0);

	for ( int cols = 0; cols < 10; cols++ )
	{
		for ( int rows = 0; rows < 15; rows ++ )
		{
			//position cube
			CVector3(rcOrigin.GetX() + 4 * cols, 0, rcOrigin.GetZ() + 4 * rows);
			ENTITY_DESC desc = { "Cube1", "cube", CVector3(rcOrigin.GetX() + 4 * cols, 0, rcOrigin.GetZ() + 4 * rows), CVector3(0,0,0), CVector3(1,1,1), CVector3(0,0,-.5f), CVector3(0, 3.14,0) };
			if (!CEntityManager::Get()->AllocateEntity(desc))
				return false;
		}
	}
	pDirectX->CreateFontObj("Arial", 14,&pGame->DebugFont);
	pGame->m_CurrentTime = timeGetTime();
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
	CDirectXManager* pDirectX = CDirectXManager::Get();
	pDirectX->BeginScene();
	m_PreviousTime = m_CurrentTime;
	m_CurrentTime = timeGetTime();
	//draw cube
	for( UINT p = 0; p < m_pEffect->GetTechDesc().Passes; p++ )
	{
		//apply technique
		m_pEffect->GetTechnique()->GetPassByIndex( p )->Apply( 0 );
		CEntityManager::Get()->ProcessAllEntities((float) (m_CurrentTime - m_PreviousTime) / 1000.0f,m_pEffect);
	}
	ostringstream convert;
	convert << (float) (m_CurrentTime - m_PreviousTime);
	pDirectX->pSprite->Begin( D3DX10_SPRITE_SAVE_STATE | D3DX10_SPRITE_SORT_DEPTH_BACK_TO_FRONT);
	DebugFont.Draw(20,20,convert.str(),CColor(1.0f, 1.0f, 1.0f, 1.0f));
	convert.clear();
	convert << m_CurrentTime;
	DebugFont.Draw(20,40,convert.str(),CColor(1.0f, 1.0f, 1.0f, 1.0f));
	pDirectX->pSprite->Flush();
	pDirectX->pSprite->End();
	pDirectX->EndScene();
	return true;
}
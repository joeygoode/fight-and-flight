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
	m_TotalTime = 0;
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
	CEntityManager::Clear();
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

	vector<string> names = vector<string>(4);
	names[0] = "World";
	names[1] = "Projection";
	names[2] = "View";
	names[3] = "TotalTime";
	vector<string> types = vector<string>(4);
	for (int i = 0; i < 3; i++)
		types[i] = "matrix";
	types[3] = "scalar";

	if(!pDirectX->CreateShader("basicEffect.fx", names, types, pGame->m_pEffect))
		return false;

	CVector3 camera[] = {	CVector3(0.0f, 10.0f, -2.0f),
							CVector3(0.0f, 0.0f, 10.0f),
							CVector3(0.0f, 0.0f, 1.0f)	};
	
	pGame->ViewMatrix.SetMatrixLookAtLH(camera[0], camera[1], camera[2]);		
	pGame->ProjectionMatrix.SetMatrixPerspectiveFovLH((float)D3DX_PI * 0.5f, (float)pDirectX->width/(float)pDirectX->height, 0.1f, 100.0f);
	//pGame->ProjectionMatrix.SetMatrixOrthoLH(40.0,30.0,0.1f, 100.0f);

	pGame->m_pEffect->SetVariableByName("View", pGame->ViewMatrix);
	pGame->m_pEffect->SetVariableByName("Projection", pGame->ProjectionMatrix);

	if (!CMeshManager::Get()->AllocateMesh("cube.xml"))
		return false;
	if (!CMeshManager::Get()->AllocateMesh("triangularpyramid.xml"))
		return false;
	if (!CMeshManager::Get()->AllocateMesh("squarepyramid.xml"))
		return false;
	CVector3 rcOrigin = CVector3(-6, 0, 5.0f);
	ENTITY_DESC desc;
	if (!CEntityManager::Get()->AllocateEntity(CEntityManager::Get()->GetEntityDescFromFile("LSide.xml",desc)))
				return false;
	if (!CEntityManager::Get()->AllocateEntity(CEntityManager::Get()->GetEntityDescFromFile("RSide.xml",desc)))
				return false;
	if (!CEntityManager::Get()->AllocateEntity(CEntityManager::Get()->GetEntityDescFromFile("player.xml", desc)))
				return false;
	for ( int cols = 0; cols < 4; cols++ )
	{
		for ( int rows = 0; rows < 20; rows ++ )
		{
			//position cube
			CVector3(rcOrigin.GetX() + 4 * cols, 0, rcOrigin.GetZ() + 4 * rows);
			ENTITY_DESC desc2;
			CEntityManager::Get()->GetEntityDescFromFile("Enemy.xml", desc2);
			desc2.position += CVector3(rcOrigin.GetX() + 4 * cols, 0, rcOrigin.GetZ() + 4 * rows);;
			if (!CEntityManager::Get()->AllocateEntityDynamic(desc2))
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
	m_TotalTime += (m_CurrentTime - m_PreviousTime);
	m_pEffect->SetVariableByName("TotalTime",(float) m_TotalTime);
	//draw cube
	for( UINT p = 0; p < m_pEffect->GetTechDesc().Passes; p++ )
	{
		//apply technique
		m_pEffect->GetTechnique()->GetPassByIndex( p )->Apply( 0 );
		CEntityManager::Get()->ProcessAllEntities((float) (m_CurrentTime - m_PreviousTime) / 1000.0f, (float) m_TotalTime / 1000.0f, m_pEffect);
	}
	ostringstream convert;
	convert << (float) (m_CurrentTime - m_PreviousTime);
	pDirectX->pSprite->Begin( D3DX10_SPRITE_SAVE_STATE | D3DX10_SPRITE_SORT_DEPTH_BACK_TO_FRONT);
	DebugFont.Draw(20,20,convert.str(),CColor(1.0f, 1.0f, 1.0f, 1.0f));
	pDirectX->pSprite->Flush();
	pDirectX->pSprite->End();
	pDirectX->EndScene();
	return true;
}
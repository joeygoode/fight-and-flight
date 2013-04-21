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
#include "Entity.h"
#include "EffectManager.h"

//-----------------------------------------------------------------------------
// Name: CGame
// Type: Constructor
// Vis: Private
// Desc: Creates a new instance of a CGame class and initializes its variables.
//-----------------------------------------------------------------------------
CGame::CGame(void)
{
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

	if(!CEffectManager::Get()->AllocateEffect("basicEffect.xml"))
		return false;

	CVector3 camera[] = {	CVector3(0.0f, 10.0f, -2.0f),
							CVector3(0.0f, 0.0f, 10.0f),
							CVector3(0.0f, 0.0f, 1.0f)	};
	
	pGame->ViewMatrix.SetMatrixLookAtLH(camera[0], camera[1], camera[2]);		
	pGame->ProjectionMatrix.SetMatrixPerspectiveFovLH((float)D3DX_PI * 0.5f, (float)pDirectX->width/(float)pDirectX->height, 0.1f, 100.0f);
	//pGame->ProjectionMatrix.SetMatrixOrthoLH(40.0,30.0,0.1f, 100.0f);

	CEffectManager::Get()->GetCurrentEffect()->SetVariableByName("View", pGame->ViewMatrix);
	CEffectManager::Get()->GetCurrentEffect()->SetVariableByName("Projection", pGame->ProjectionMatrix);

	pGame->oldeffectnumber = 0;

	if (!CMeshManager::Get()->AllocateMesh("cube.xml"))
		return false;
	if (!CMeshManager::Get()->AllocateMesh("triangularpyramid.xml"))
		return false;
	if (!CMeshManager::Get()->AllocateMesh("squarepyramid.xml"))
		return false;
	if (!CMeshManager::Get()->AllocateMesh("cube2.xml"))
		return false;
	CVector3 rcOrigin = CVector3(-6, 0, 5.0f);
	ENTITY_DESC desc;
	if (!CEntityManager::Get()->AllocateEntity(CEntityManager::Get()->GetEntityDescFromFile("LSide.xml",desc)))
				return false;
	if (!CEntityManager::Get()->AllocateEntity(CEntityManager::Get()->GetEntityDescFromFile("RSide.xml",desc)))
				return false;
	if (!CEntityManager::Get()->AllocateEntity(CEntityManager::Get()->GetEntityDescFromFile("player.xml", desc)))
				return false;
	CEntity* player = NULL;
	CEntityManager::Get()->GetEntityByName("player", player);
	player->m_AddtlData = 0;
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
	int prevTime = m_CurrentTime;
	m_CurrentTime = timeGetTime();
	if (prevTime != m_CurrentTime)
	{
		m_PreviousTime = prevTime;
		m_TotalTime += (m_CurrentTime - m_PreviousTime);
		if (oldeffectnumber == CEffectManager::Get()->GetEffectNumber())
		{
			CEffectManager::Get()->GetCurrentEffect()->SetVariableByName("View", ViewMatrix);
			CEffectManager::Get()->GetCurrentEffect()->SetVariableByName("Projection", ProjectionMatrix);
			oldeffectnumber = CEffectManager::Get()->GetEffectNumber();
		}
		CEffectManager::Get()->GetCurrentEffect()->SetVariableByName("TotalTime",(float) m_TotalTime);
		//draw cube
		int random = rand() % 200;
		if (random == 0)
		{
			ENTITY_DESC desc;
			CEntityManager::Get()->GetEntityDescFromFile("Enemy.xml", desc);
			desc.position.SetX((float) (rand() % 16) - 8); 
			CEntityManager::Get()->AllocateEntityDynamic(desc);
		}
		for( UINT p = 0; p < CEffectManager::Get()->GetCurrentEffect()->GetTechDesc().Passes; p++ )
		{
			//apply technique
			CEffectManager::Get()->GetCurrentEffect()->GetTechnique()->GetPassByIndex( p )->Apply( 0 );
			CEntityManager::Get()->ProcessAllEntities(((float) (m_CurrentTime - m_PreviousTime)) / 1000.0f, (float) m_TotalTime / 1000.0f, CEffectManager::Get()->GetCurrentEffect());
		}
		CEntity* player = NULL;
		if (!CEntityManager::Get()->GetEntityByName("player", player))
		{
			ENTITY_DESC desc;
			CEntityManager::Get()->AllocateEntity(CEntityManager::Get()->GetEntityDescFromFile("player.xml", desc));
			CEntityManager::Get()->GetEntityByName("player", player);
			player->m_AddtlData = 0;
		}
		pDirectX->pSprite->Begin( D3DX10_SPRITE_SAVE_STATE | D3DX10_SPRITE_SORT_DEPTH_BACK_TO_FRONT);
		ostringstream convert;
		convert << "Your Score: " << player->m_AddtlData << endl;
		convert << "High Score: " << CEntityManager::Get()->m_HighScore << endl;
		DebugFont.Draw(650,20,convert.str(),CColor(1.0f, 1.0f, 1.0f, 1.0f));
		ostringstream convert2;
		convert2 << 1.0f / ((float) (m_CurrentTime - m_PreviousTime) / 1000.0f) << endl;
		convert2 << m_CurrentTime << endl;
		convert2 << m_PreviousTime << endl;
		DebugFont.Draw(20,20,convert2.str(),CColor(1.0f, 1.0f, 1.0f, 1.0f));
		pDirectX->pSprite->Flush();
		pDirectX->pSprite->End();
		pDirectX->EndScene();
	}
	return true;
}
#include "MyDirectX.h"
#include "World.h"
#include "Renderer.h"
#include "tinystr.h"
#include "tinyxml.h"

using namespace std;

string APPTITLE = "Flight Shooter";
int SCREENW = 600;
int SCREENH = 1000;

CWorld* GameWorld = NULL;
void ReadWindowSettingsFromXML()
{
	TiXmlDocument doc("InitialWorld.xml");
	doc.LoadFile();
	TiXmlHandle hDoc(&doc);
	TiXmlElement* pElem;
	TiXmlHandle hRoot(0);
	hRoot = hDoc.FirstChildElement("World");
	pElem = hRoot.FirstChildElement("WorldConstants").Element();
	APPTITLE = string(pElem->Attribute("APPTITLE"));
	pElem->Attribute("SCREENW", &SCREENW);
	pElem->Attribute("SCREENH", &SCREENH);
}

bool Game_Init(HWND window)
{

	//Initialize DirectX
	if(!Direct3D_Init(window, SCREENW, SCREENH, false)) return false;
	if(!DirectInput_Init(window)) return false;

	//TODO: Game initialization goes here
	GameWorld = new CWorld();
	GameWorld->LoadData();
	CRenderer::Init_Matrix_Stack();
	return true;
}

void Game_Run(HWND window)
{
	//make sure the Direct3D Device is valid
	if(!d3ddev) return;

	//clear the backbuffer
	d3ddev->ColorFill(backbuffer, NULL, D3DCOLOR_XRGB(8,54,129));

	//render
	if(d3ddev->BeginScene())
	{
		//update the input devices
		DirectInput_Update();

		//Update the game state
		GameWorld->Update();
		spriteobj->Begin(D3DXSPRITE_ALPHABLEND);
		//TODO: Game rendering goes here
		//Use command spriteobj->Draw(LPDIRECT3DTEXTURE9 pTexture, CONST RECT *pSrcRect, CONST D3DXVECTOR3 *pCenter, CONST D3DXVECTOR3 *pPosition, D3DXCOLOR Color)
		//Color should probably be white.
		GameWorld->Draw();
		spriteobj->End();
		d3ddev->EndScene();
		d3ddev->Present(NULL,NULL,NULL, NULL);
	}

	//escape key exits
	if(Key_Down(DIK_ESCAPE)) 
	{
		gameover = true;
	}

	//controller Backbutton also exits
	if (controllers[0].wButtons & XINPUT_GAMEPAD_BACK) gameover = true;
}

void Game_End()
{
	//TODO: Release all surfaces and whatnot here (or in relevant destructors)
	//Shut down DirectX
	DirectInput_Shutdown();
	Direct3D_Shutdown();
}

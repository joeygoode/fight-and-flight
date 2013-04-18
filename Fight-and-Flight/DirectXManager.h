/************************************************************************************
 *	DirectX 10 Manager Class
 *	----------------------------------------
 *	code by : bobby anguelov - banguelov@cs.up.ac.za
 *	downloaded from : takinginitiative.wordpress.org
 *
 *	code is free for use in whatever way you want, however if you work for a game
 *	development firm you are obliged to offer me a job :P (haha i wish)
 ************************************************************************************/

#pragma once

#include <windows.h>
#include <d3d10.h>
#include <d3dx10.h>
#include <vector>
using namespace std;

#include "vertexTypes.h"

class CEffect;
class CMesh;
class CFontObj;

class CDirectXManager
{
	/*******************************************************************
	* Members
	********************************************************************/	
private:

	//window handle shortcut
	HWND*						hWnd;
	
	//device vars
	ID3D10Device*				pD3DDevice;
	IDXGISwapChain*				pSwapChain;
	ID3D10RenderTargetView*		pRenderTargetView;
	ID3D10Texture2D*			pDepthStencil;
	ID3D10DepthStencilView*		pDepthStencilView;	
	D3D10_VIEWPORT				viewPort;
	ID3D10RasterizerState*		pRS;

	//input layout and mesh
	ID3D10InputLayout*			pVertexLayout;

	static CDirectXManager* s_Singleton;


	/*******************************************************************
	* Methods
	********************************************************************/	
public:
	UINT width;
	UINT height;
	ID3DX10Sprite*				pSprite;
	//constructor and destructor

	
	static CDirectXManager* Get();
	static void Clear();

	//initialize directx device
	bool initialize(_In_ HWND*);	

	//scene function
	void BeginScene(void);
	void EndScene(void);
	bool CreateMesh(_In_ const vector<vertex>& vertices,
					_In_ const vector<UINT>& indices,
					_In_ int NumFaces,
					_In_ const string& MeshID,
					_Out_ CMesh& pMesh);
	bool CreateMesh(_In_ const string& filename,
					_Out_ CMesh &pMesh);
	bool CreateShader(	_In_ const string& filename,
						_In_ const vector<string>& names,
						_In_ const vector<string>& types,
						_Out_ CEffect* &pOut);
	bool CreateFontObj(const string& name, int size, CFontObj* out);
	void DrawFont(ID3DX10Font* font, int x, int y, string text, D3DXCOLOR color);
private:
	CDirectXManager();
	~CDirectXManager();
	//initialization methods
	bool createSwapChainAndDevice( UINT width, UINT height );
	void createViewports( UINT width, UINT height );
	void initRasterizerState();
	bool createRenderTargetsAndDepthBuffer( UINT width, UINT height );

	//fatal error handler
	bool fatalError(const LPCSTR msg); 
};

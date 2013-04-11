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

#include "Matrix.h"
#include <vector>
using namespace std;

#include "vertexTypes.h"

class CMesh;
class CEffect;

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
	/*
	//effect variable pointers
	ID3D10EffectMatrixVariable* pViewMatrixEffectVariable;
	ID3D10EffectMatrixVariable* pProjectionMatrixEffectVariable;
	ID3D10EffectMatrixVariable* pWorldMatrixEffectVariable;
	*/
	//projection and view matrices
	
	CMatrix						ViewMatrix;
	CMatrix						ProjectionMatrix;

	/*******************************************************************
	* Methods
	********************************************************************/	
public:
	CMatrix						WorldMatrix;
	ID3DX10Sprite*				pSprite;
	//constructor and destructor
	CDirectXManager();
	~CDirectXManager();

	//initialize directx device
	bool initialize(_In_ HWND*);	

	//scene function
	void BeginScene(void);
	void EndScene(void);
	void renderScene(CMesh* pMesh, CEffect* pEffect);	
	bool CreateMesh(_In_ const vector<vertex>& vertices,
					_In_ const vector<UINT>& indices,
					_In_ int NumFaces,
					_Out_ CMesh* &pMesh);
	bool CreateShader(	_In_ const string& filename,
						_In_ const vector<string>& names,
						_In_ const vector<string>& types,
						_Out_ CEffect* &pOut);
	ID3DX10Font* MakeFont(string name, int size);
	void FontPrint(ID3DX10Font* font, int x, int y, string text, D3DXCOLOR color);
	void ResetStates();
private:

	//initialization methods
	bool createSwapChainAndDevice( UINT width, UINT height );
	void createViewports( UINT width, UINT height );
	void initRasterizerState();
	bool createRenderTargetsAndDepthBuffer( UINT width, UINT height );

	//fatal error handler
	bool fatalError(const LPCSTR msg); 
};

#pragma once
#include <Windows.h>
#include <D3D10.h>
#include <D3DX10.h>

//-----------------------------------------------------------------------------
// This class is basically copy-pasted from 
// http://takinginitiative.net/2008/08/31/directx10-tutorial-1-setting-up-the-d3d10-device/
// with minor changes to match naming conventions.  Seeing as previous code was 
// copy-pasted from harbour, I don't see a problem here.  The RenderScene
// function uses much of my own code because it's the only one not doing 
// initialization stuff.
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// Name: VERTEX
// Type: Structure
// Description: The VERTEX structure is the structure that will be used by all
// .fx files that are vertex shaders in this project.  This class is designed
// to be extensible, and (if I'm right) the .fx files don't need to be update
// to accomodate additional fields IF THE FIELDS ARE ADDED AFTER EXISTING FIELDS
// 
// ADD ALL FIELDS AFTER EXISTING FIELDS!! DO NOT BREAK THIS RULE!!
//-----------------------------------------------------------------------------

struct VERTEX
{
	D3DXVECTOR3 pos;
	D3DXVECTOR4 color;
	D3DXVECTOR2 texCoord;

	VERTEX( D3DXVECTOR3 p, D3DXVECTOR4 c, D3DXVECTOR2 tc )
	{
		pos = p;
		color = c;
		texCoord = tc;
	}
};

//-----------------------------------------------------------------------------
// Name: CDirectXManager
// Type: Class
// Description: The CDirectXManager class contains all Direct3D calls.  All
// calls should be passed through methods in this class where they will be
// converted into Direct3D API calls.  Do not add Direct3D API calls outside
// of this class.  It makes the code inextensible and hard to debug and
// catch errors.  Let's start with the assumtion that when we need to vary
// a call, we'll add a new optional parameter to an existing method first
// before adding new methods.  Ideally, existing methods won't be changed
// because it will require changing everywhere that method is called.
//-----------------------------------------------------------------------------

class CDirectXManager
{
public:
	// Public Constructor (At some point, replace this with a factory method).
	CDirectXManager();
	// Public Destructor
	~CDirectXManager();
	// Initialiation Method (This will be moved into the factory.)
	bool Initialize(HWND*);
	// Render Method: It draws the scene to the screen.
	void RenderScene();	
private:
	// Storage for the window
	HWND*						hWnd;
	// Pointer to the device
	ID3D10Device*				pD3DDevice;
	// Pointer to the swap chain
	IDXGISwapChain*				pSwapChain;
	// Pointer to the render target (contains the backbuffer)
	ID3D10RenderTargetView*		pRenderTargetView;
	// View Port
	D3D10_VIEWPORT				viewPort;
	// Camera Transform Matrix
	D3DXMATRIX                  viewMatrix;
	// Camera Projection Matrix
	D3DXMATRIX                  projectionMatrix;
	// Pointer to the Vertex Buffer
	ID3D10Buffer*				pVertexBuffer;
	// Pointer to the Vertex Layout.  It tells Direct3D 10 what the VERTEX structure looks like.
	ID3D10InputLayout*			pVertexLayout;
	// Pointer to the effect currently being used to define the graphic's pipeline
	ID3D10Effect*				pBasicEffect;
	// Pointer to the effect technique (internal DX variable)
	ID3D10EffectTechnique*		pBasicTechnique;
	// View Matrix variable to pass to the Vertex Shader
	ID3D10EffectMatrixVariable* pViewMatrixEffectVariable;
	// Projection Matrix variable to pass to the vertex shader
	ID3D10EffectMatrixVariable* pProjectionMatrixEffectVariable;
	// World Matrix variable to pass to the vertex shader
	ID3D10EffectMatrixVariable* pWorldMatrixEffectVariable;
	
	// Error method (kills the program and puts up an error message
	bool FatalError(LPCSTR msg); 
};


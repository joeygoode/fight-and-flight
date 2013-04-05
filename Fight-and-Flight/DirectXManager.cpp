#include "DirectXManager.h"
#include <string>
using namespace std;

#include "Mesh.h"
#include "Matrix.h"
#include "Vector3.h"

/*******************************************************************
* Constructor
*******************************************************************/
CDirectXManager::CDirectXManager() :	pD3DDevice(NULL),
										pSwapChain(NULL),
										pRenderTargetView(NULL),							
										pVertexLayout(0),
										pBasicEffect(0),
										pRS(0),							
										pDepthStencil(0)
{
	pWorldMatrix = NULL;
	pProjectionMatrix = NULL;
	pViewMatrix = NULL;


	CMatrix::CreateIdentityMatrix(pWorldMatrix);
	CMatrix::CreateIdentityMatrix(pProjectionMatrix);
	CMatrix::CreateIdentityMatrix(pViewMatrix);
}
/*******************************************************************
* Destructor
*******************************************************************/
CDirectXManager::~CDirectXManager()
{
	if ( pRenderTargetView ) pRenderTargetView->Release();
	if ( pSwapChain ) pSwapChain->Release();
	if ( pD3DDevice ) pD3DDevice->Release();	
	if ( pVertexLayout ) pVertexLayout->Release();
	if ( pRS ) pRS->Release();
	if ( pBasicEffect ) pBasicEffect->Release();	
	if ( pDepthStencil ) pDepthStencil->Release();

}
/*******************************************************************
* Initializes Direct3D Device
*******************************************************************/
bool CDirectXManager::initialize(_In_ HWND* hW )
{
	//window handle
	hWnd = hW;
	
	//get window dimensions
	RECT rc;
    GetClientRect( *hWnd, &rc );
    UINT width = rc.right - rc.left;
    UINT height = rc.bottom - rc.top;

	// CREATE DEVICE
	//*****************************************************************************
	if ( !createSwapChainAndDevice(width, height) ) return false;
	
	// INPUT ASSEMBLY STAGE
	//*****************************************************************************
	if ( !loadShadersAndCreateInputLayouts() ) return false;			

	// RASTERIZER STAGE SETUP
	//*****************************************************************************
	createViewports(width, height);
	initRasterizerState();	

	// OUTPUT-MERGER STAGE
	//*****************************************************************************
	if ( !createRenderTargetsAndDepthBuffer(width, height) ) return false;
	
	// Set up the view and projection matrices
	//*****************************************************************************
	CVector3 camera[] = {	CVector3(0.0f, 5.0f, -10.0f),
							CVector3(0.0f, 0.0f, 1.0f),
							CVector3(0.0f, 1.0f, 0.0f)	};
	
	CMatrix::CreateMatrixLookAtLH(&camera[0], &camera[1], &camera[2], pViewMatrix);		
	CMatrix::CreateMatrixPerspectiveFovLH((float)D3DX_PI * 0.5f, (float)width/(float)height, 0.1f, 100.0f, pProjectionMatrix);
	
	//set shader matrices
	pViewMatrixEffectVariable->SetMatrix(*pViewMatrix->GetD3DXMATRIX());
	pProjectionMatrixEffectVariable->SetMatrix(*pProjectionMatrix->GetD3DXMATRIX());

	// Initialize Scene Objects
	//*****************************************************************************

	//if ( !initializeObjects() ) return false;

	//everything completed successfully
	return true;
}
/*******************************************************************
* Create Swap Chain and D3D device
*******************************************************************/
bool CDirectXManager::createSwapChainAndDevice( UINT width, UINT height )
{
	//Set up DX swap chain
	//--------------------------------------------------------------
	DXGI_SWAP_CHAIN_DESC swapChainDesc;
	ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));
	
	//set buffer dimensions and format
	swapChainDesc.BufferCount = 2;
	swapChainDesc.BufferDesc.Width = width;
	swapChainDesc.BufferDesc.Height = height;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;;
	
	//set refresh rate
	swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
	swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	
	//sampling settings
	swapChainDesc.SampleDesc.Quality = 0;
	swapChainDesc.SampleDesc.Count = 1;

	//output window handle
	swapChainDesc.OutputWindow = *hWnd;
	swapChainDesc.Windowed = true;    

	//Create the D3D device
	//--------------------------------------------------------------
	if ( FAILED( D3D10CreateDeviceAndSwapChain(		NULL, 
													D3D10_DRIVER_TYPE_HARDWARE, 
													NULL, 
													0, 
													D3D10_SDK_VERSION, 
													&swapChainDesc, 
													&pSwapChain, 
													&pD3DDevice ) ) ) return fatalError("D3D device creation failed");
	return true;
}
/*******************************************************************
* Set up Viewports
*******************************************************************/
void CDirectXManager::createViewports( UINT width, UINT height )
{	
	//create viewport structure	
	viewPort.Width = width;
	viewPort.Height = height;
	viewPort.MinDepth = 0.0f;
	viewPort.MaxDepth = 1.0f;
	viewPort.TopLeftX = 0;
	viewPort.TopLeftY = 0;

	pD3DDevice->RSSetViewports(1, &viewPort);
}
/*******************************************************************
* Initialize Rasterizer State
*******************************************************************/
void CDirectXManager::initRasterizerState()
{
	//set rasterizer	
	D3D10_RASTERIZER_DESC rasterizerState;
	rasterizerState.CullMode = D3D10_CULL_NONE;
	rasterizerState.FillMode = D3D10_FILL_SOLID;
	rasterizerState.FrontCounterClockwise = true;
    rasterizerState.DepthBias = false;
    rasterizerState.DepthBiasClamp = 0;
    rasterizerState.SlopeScaledDepthBias = 0;
    rasterizerState.DepthClipEnable = true;
    rasterizerState.ScissorEnable = false;
    rasterizerState.MultisampleEnable = false;
    rasterizerState.AntialiasedLineEnable = true;

	pD3DDevice->CreateRasterizerState( &rasterizerState, &pRS);
	
	pD3DDevice->RSSetState(pRS);
}
/*******************************************************************
* Create Rendering Targets
*******************************************************************/
bool CDirectXManager::createRenderTargetsAndDepthBuffer( UINT width, UINT height )
{
	//try to get the back buffer
	ID3D10Texture2D* pBackBuffer;	
	if ( FAILED( pSwapChain->GetBuffer(0, __uuidof(ID3D10Texture2D), (LPVOID*) &pBackBuffer) ) ) return fatalError("Could not get back buffer");

	//try to create render target view
	if ( FAILED( pD3DDevice->CreateRenderTargetView(pBackBuffer, NULL, &pRenderTargetView) ) ) return fatalError("Could not create render target view");
	
	pBackBuffer->Release();
	
	//create depth stencil texture
    D3D10_TEXTURE2D_DESC descDepth;
    descDepth.Width = width;
    descDepth.Height = height;
    descDepth.MipLevels = 1;
    descDepth.ArraySize = 1;
    descDepth.Format = DXGI_FORMAT_D32_FLOAT;
    descDepth.SampleDesc.Count = 1;
    descDepth.SampleDesc.Quality = 0;
    descDepth.Usage = D3D10_USAGE_DEFAULT;
    descDepth.BindFlags = D3D10_BIND_DEPTH_STENCIL;
    descDepth.CPUAccessFlags = 0;
    descDepth.MiscFlags = 0;   
    
	if( FAILED( pD3DDevice->CreateTexture2D( &descDepth, NULL, &pDepthStencil ) ) )  return fatalError("Could not create depth stencil texture");

    // Create the depth stencil view
    D3D10_DEPTH_STENCIL_VIEW_DESC descDSV;
    descDSV.Format = descDepth.Format;
    descDSV.ViewDimension = D3D10_DSV_DIMENSION_TEXTURE2D;
    descDSV.Texture2D.MipSlice = 0;
    
    if( FAILED( pD3DDevice->CreateDepthStencilView( pDepthStencil, &descDSV, &pDepthStencilView ) ) ) return fatalError("Could not create depth stencil view");

	//set render targets
	pD3DDevice->OMSetRenderTargets( 1, &pRenderTargetView, pDepthStencilView );

	return true;
}
/*******************************************************************
* Shader Loader
*******************************************************************/
bool CDirectXManager::loadShadersAndCreateInputLayouts()
{
	if ( FAILED( D3DX10CreateEffectFromFile(	"basicEffect.fx", 
												NULL, NULL, 
												"fx_4_0", 
												D3D10_SHADER_ENABLE_STRICTNESS, 
												0, 
												pD3DDevice, 
												NULL, 
												NULL, 
												&pBasicEffect, 
												NULL, 
												NULL	) ) ) return fatalError("Could not load effect file!");	

	pBasicTechnique = pBasicEffect->GetTechniqueByName("render");
	if ( pBasicTechnique == NULL ) return fatalError("Could not find specified technique!");	
	

	//create matrix effect pointers
	pViewMatrixEffectVariable = pBasicEffect->GetVariableByName( "View" )->AsMatrix();
	pProjectionMatrixEffectVariable = pBasicEffect->GetVariableByName( "Projection" )->AsMatrix();
	pWorldMatrixEffectVariable = pBasicEffect->GetVariableByName( "World" )->AsMatrix();	

	//create input layout
	D3D10_PASS_DESC PassDesc;
	pBasicTechnique->GetPassByIndex( 0 )->GetDesc( &PassDesc );
	if ( FAILED( pD3DDevice->CreateInputLayout( vertexInputLayout, 
												2, 
												PassDesc.pIAInputSignature,
												PassDesc.IAInputSignatureSize, 
												&pVertexLayout ) ) ) return fatalError("Could not create Input Layout!");

	// Set the input layout
	pD3DDevice->IASetInputLayout( pVertexLayout );
	
	//get technique description
	pBasicTechnique->GetDesc( &techDesc );

	return true;
}
//-----------------------------------------------------------------------------
// Name: CreateMesh
// Type: Factory
// Vis: Public
// Desc: Wraps the DirectX Mesh creation function: D3DX10CreateMesh and
// provides some of the inputs
// Inputs:
//	- vertices: A vector of vertices for 
bool CDirectXManager::CreateMesh(	_In_ vector<vertex> vertices,
									_In_ vector<UINT> indices,
									_In_ int NumFaces,
									_Out_ CMesh* &pMesh)
{
	ID3DX10Mesh* pDXMesh = NULL;
	HRESULT result;
	if ( FAILED(result = D3DX10CreateMesh( pD3DDevice, vertexInputLayout, 2, "POSITION", vertices.size(), NumFaces, D3DX10_MESH_32_BIT, &pDXMesh)))
		return fatalError("Could not create mesh!");
	//insert data into mesh and commit changes
	pDXMesh->SetVertexData(0, &vertices[0]);
	pDXMesh->SetIndexData(&indices[0], 36);
	pDXMesh->CommitToDevice();
	pMesh = new CMesh(pDXMesh);
	return true;
}
void CDirectXManager::BeginScene(void)
{
	pD3DDevice->ClearRenderTargetView( pRenderTargetView, D3DXCOLOR(0,0,0,0) );
	pD3DDevice->ClearDepthStencilView( pDepthStencilView, D3D10_CLEAR_DEPTH, 1.0f, 0 );
}
void CDirectXManager::EndScene(void)
{
	pSwapChain->Present(0,0);
}
/*******************************************************************
* Scene Renderer
*******************************************************************/
void CDirectXManager::renderScene(CMesh* pMesh)
{
	//rotate object - rotation should be timer based but i'm lazy
	CMatrix* temp = new CMatrix();
	static float r = 0;	
	r += 0.0001f;

	D3DXVECTOR3 rcOrigin(-14, 0, 0);

	//draw lots of cubes
	for ( int cols = 0; cols < 10; cols++ )
	{
		for ( int rows = 0; rows < 15; rows ++ )
		{
			//position cube
			CMatrix::CreateMatrixRotationY(r,pWorldMatrix);
			CMatrix::CreateMatrixTranslation(rcOrigin.x + 4 * cols, 0, rcOrigin.z + 4 * rows,  temp);
			*pWorldMatrix *= *temp;
			delete temp;
			pWorldMatrixEffectVariable->SetMatrix(*pWorldMatrix->GetD3DXMATRIX());

			//draw cube
			for( UINT p = 0; p < techDesc.Passes; p++ )
			{
				//apply technique
				pBasicTechnique->GetPassByIndex( p )->Apply( 0 );
				pMesh->Draw();
			}
		}
	}
}

/*******************************************************************
* Fatal Error Handler
*******************************************************************/
bool CDirectXManager::fatalError(const LPCSTR msg)
{
	MessageBox(*hWnd, msg, "Fatal Error!", MB_ICONERROR);
	return false;
}
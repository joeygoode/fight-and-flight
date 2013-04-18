#include "DirectXManager.h"
#include <string>
using namespace std;

#include "Mesh.h"
#include "Matrix.h"
#include "Vector3.h"
#include "Effect.h"
#include "FontObj.h"

#include "../TinyXML/tinystr.h"
#include "../TinyXML/tinyxml.h"
#include "../TinyXML/tinyxml.cpp"
#include "../TinyXML/tinystr.cpp"
#include "../TinyXML/tinyxmlparser.cpp"
#include "../TinyXML/tinyxmlerror.cpp"

CDirectXManager* CDirectXManager::s_Singleton = NULL;

CDirectXManager* CDirectXManager::Get()
{
	if (!s_Singleton)
		s_Singleton = new CDirectXManager();
	return s_Singleton;
}

void CDirectXManager::Clear()
{
	if (s_Singleton)
		delete s_Singleton;
	s_Singleton = NULL;
}

/*******************************************************************
* Constructor
*******************************************************************/
CDirectXManager::CDirectXManager() :	pD3DDevice(NULL),
										pSwapChain(NULL),
										pRenderTargetView(NULL),							
										pVertexLayout(0),
										pRS(0),							
										pDepthStencil(0)
{
	hWnd = NULL;
}
/*******************************************************************
* Destructor
*******************************************************************/
CDirectXManager::~CDirectXManager()
{
	if ( pRenderTargetView ) pRenderTargetView->Release();
	if ( pSwapChain ) pSwapChain->Release();
	if ( pVertexLayout ) pVertexLayout->Release();
	if ( pRS ) pRS->Release();	
	if ( pDepthStencil ) pDepthStencil->Release();
	if ( pSprite ) pSprite->Release();
	if ( pD3DDevice ) pD3DDevice->Release();	
	

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
    width = rc.right - rc.left;
    height = rc.bottom - rc.top;

	// CREATE DEVICE
	//*****************************************************************************
	if ( !createSwapChainAndDevice(width, height) ) return false;	

	// RASTERIZER STAGE SETUP
	//*****************************************************************************
	createViewports(width, height);
	initRasterizerState();	

	// OUTPUT-MERGER STAGE
	//*****************************************************************************
	if ( !createRenderTargetsAndDepthBuffer(width, height) ) return false;
	
	// Set up the view and projection matrices
	//*****************************************************************************

	
	if(FAILED(D3DX10CreateSprite(pD3DDevice,16,&pSprite)))
		return fatalError("Sprite failed.");


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
bool CDirectXManager::CreateShader(_In_ const string& filename, 
								   _In_ const vector<string>& names, 
								   _In_ const vector<string>& types, 
								   _Out_ CEffect* &pEffect)
{
	ID3D10Effect* pDXEffect;
	ID3D10EffectTechnique* pDXTechnique;
	D3D10_TECHNIQUE_DESC DXtechDesc;
	if (FAILED(D3DX10CreateEffectFromFile(	filename.c_str(), 
											NULL, NULL, 
											"fx_4_0", 
											D3D10_SHADER_ENABLE_STRICTNESS, 
											0, 
											pD3DDevice, 
											NULL, 
											NULL, 
											&pDXEffect, 
											NULL, 
											NULL	))) 
		return fatalError("Could not load effect file!");	
	pDXTechnique = pDXEffect->GetTechniqueByName("render");
	if ( pDXTechnique == NULL ) return fatalError("Could not find specified technique!");	
	

	//create input layout
	D3D10_PASS_DESC PassDesc;
	pDXTechnique->GetPassByIndex( 0 )->GetDesc( &PassDesc );
	if ( FAILED( pD3DDevice->CreateInputLayout( vertexInputLayout, 
												2, 
												PassDesc.pIAInputSignature,
												PassDesc.IAInputSignatureSize, 
												&pVertexLayout ) ) ) return fatalError("Could not create Input Layout!");

	// Set the input layout
	pD3DDevice->IASetInputLayout( pVertexLayout );
	
	//get technique description
	pDXTechnique->GetDesc( &DXtechDesc );

	if (!pEffect)
		delete pEffect;
	pEffect = new CEffect(pDXEffect, pDXTechnique, DXtechDesc);

	pEffect->Initialize(names, types);


	return true;
}
//-----------------------------------------------------------------------------
// Name: CreateMesh
// Type: Factory
// Vis: Public
// Desc: Wraps the DirectX Mesh creation function: D3DX10CreateMesh and
// provides some of the inputs. It deletes anything stored in the
// pMesh pointer to make room for the new mesh.
// Inputs:
//	- vertices: A vector of the vertices in the mesh.
//	- indices: A vector of the indices in the mesh.
//	- NumFaces: The number of faces in the mesh.
// Outputs:
//	- out: A mesh to fill.
//	- retval: false if the API calls failed.
//-----------------------------------------------------------------------------
bool CDirectXManager::CreateMesh(	_In_ const vector<vertex>& vertices,
									_In_ const vector<UINT>& indices,
									_In_ int numFaces,
									_In_ const string& MeshID,
									_Out_ CMesh &out)
{
	if ( FAILED(D3DX10CreateMesh( pD3DDevice, vertexInputLayout, 2, "POSITION", vertices.size(), numFaces, D3DX10_MESH_32_BIT, &out.m_pDXMesh)))
		return fatalError("Could not create mesh!");
	//insert data into mesh and commit changes
	out.m_pDXMesh->SetVertexData(0, &vertices[0]);
	out.m_pDXMesh->SetIndexData(&indices[0], 36);
	out.m_pDXMesh->CommitToDevice();
	out.m_ID = MeshID;
	return true;
}
//-----------------------------------------------------------------------------
// Name: CreateMesh
// Type: Factory
// Vis: Public
// Desc: Wraps the DirectX Mesh creation function: D3DX10CreateMesh and
// provides some of the inputs. It deletes anything stored in the
// pMesh pointer to make room for the new mesh.
// Inputs:
//	- filename: the name of an XML file containing the mesh to load.
// Outputs:
//	- pMesh: a mesh to fill.
//	- retval: false if the API calls failed.
//-----------------------------------------------------------------------------

bool CDirectXManager::CreateMesh(	_In_ const string& filename,
									_Out_ CMesh &out)
{
	TiXmlDocument doc( filename.c_str() );
	doc.LoadFile();
	TiXmlHandle hDoc(&doc);
	TiXmlHandle hRoot(0);
	hRoot = hDoc.FirstChildElement("Mesh").Element();
	TiXmlHandle VertexXML = hRoot.FirstChildElement("Vertices");
	TiXmlHandle IndexXML = hRoot.FirstChildElement("Indices");
	vector<vertex> vertices = vector<vertex>();
	TiXmlElement *child;
	for( child = VertexXML.FirstChildElement().Element(); child; child = child->NextSiblingElement())
	{
		TiXmlElement* pos = child->FirstChildElement("Position");
		TiXmlElement* col = child->FirstChildElement("Color");
		D3DXVECTOR3 position = D3DXVECTOR3(0,0,0);
		D3DXCOLOR color = D3DXCOLOR(0,0,0,0);
		double d;
		pos->Attribute("x", &d);
		position.x = (float) d;
		pos->Attribute("y", &d);
		position.y = (float) d;
		pos->Attribute("z", &d);
		position.z = (float) d;
		col->Attribute("r", &d);
		color.r = (float) d;
		col->Attribute("g", &d);
		color.g = (float) d;
		col->Attribute("b", &d);
		color.b = (float) d;
		col->Attribute("a", &d);
		color.a = (float) d;
		vertices.push_back(vertex(position,color));
	}
	vector<unsigned int> indices = vector<unsigned int>();
	for (child = IndexXML.FirstChildElement().Element(); child; child = child->NextSiblingElement())
	{
		int i;
		child->Attribute("i", &i);
		indices.push_back((unsigned int) i);
	}
	int numFaces;
	hRoot.Element()->Attribute("NumFaces", &numFaces);
	

	return CreateMesh(vertices,indices,numFaces,filename.substr(0, filename.length() - 4), out);
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
* Fatal Error Handler
*******************************************************************/
bool CDirectXManager::fatalError(const LPCSTR msg)
{
	MessageBox(*hWnd, msg, "Fatal Error!", MB_ICONERROR);
	return false;
}

bool CDirectXManager::CreateFontObj(const string& name, int size, CFontObj* Out)
{
	Out->m_pD3DDevice = pD3DDevice;
	Out->m_pDXSprite = pSprite;
	D3DX10_FONT_DESC desc = {
		size,
		0,
		0,
		0,
		false,
		DEFAULT_CHARSET,
		OUT_TT_PRECIS,
		CLIP_DEFAULT_PRECIS,
		DEFAULT_PITCH,
		""
	};
	strcpy(desc.FaceName, name.c_str());
	ID3DX10Font* pDXFont = NULL;
	if (FAILED (D3DX10CreateFontIndirect(pD3DDevice, &desc, &Out->m_pDXFont)))
		return false;
	return true;
}

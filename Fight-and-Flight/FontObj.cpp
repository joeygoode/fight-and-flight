#include "FontObj.h"
#include "Color.h"
//-----------------------------------------------------------------------------
// Name: CFontObj
// Type: Constructor
// Vis: Public
// Desc: Creates a new FontObj.  Use CDirectXManager::CreateFont() after
// calling this method to initialize.
//-----------------------------------------------------------------------------
CFontObj::CFontObj(void)
{
	m_pDXFont = NULL;
	m_pDXSprite = NULL;
	m_pD3DDevice = NULL;
}

//-----------------------------------------------------------------------------
// Name: ~CFontObj
// Type: Destructor
// Vis: Public
// Desc: Destroys this font object.
//-----------------------------------------------------------------------------
CFontObj::~CFontObj(void)
{
	if (m_pDXFont)
		m_pDXFont->Release();
}

//-----------------------------------------------------------------------------
// Name: Draw
// Type: Method
// Vis: Public
// Desc: Draws the text string to the screen in this font at (x,y)
// Inputs:
//	- x: the x location of the top left corner of the rect containing the text
//	- y: the y location of the top left corner of the rect containing the text
//	- text: the string of text to be displayed.
//	- color:  The color to display the text in.
//-----------------------------------------------------------------------------
void CFontObj::Draw(int x, int y, const string& text,const CColor& color) const
{
	ID3D10DepthStencilState* pDSState = NULL;
	UINT reference;
	HRESULT result;
	m_pD3DDevice->OMGetDepthStencilState(&pDSState,&reference);
	RECT rect = {x,y,0,0};
	result = m_pDXFont->DrawText(NULL,text.c_str(),text.length(),&rect,DT_CALCRECT,color.GetD3DXCOLOR());
	result = m_pDXFont->DrawText(m_pDXSprite,text.c_str(),text.length(),&rect,DT_LEFT,color.GetD3DXCOLOR());
	m_pD3DDevice->OMSetDepthStencilState(pDSState,reference);
}

#include "Color.h"
#include <D3DX10.h>
//-----------------------------------------------------------------------------
// Name: CColor
// Type: Constructor
// Vis: Public
// Desc: Creates a new color object that wraps some APIs color implementation
// Inputs:
//	- r: A floating point red value.  Should be [0,1] bound.
//	- g: A floating point green value. Should be [0,1] bound.
//	- b: A floating point blue value. Should be [0,1] bound.
//	- a: A floating point alpha value. Should be [0,1] bound.
//-----------------------------------------------------------------------------
CColor::CColor(float r, float g, float b, float a)
{
#if (GRAPHICSAPI == DIRECTX10)
	m_DXColor = D3DXCOLOR(r,g,b,a);
#endif
}
//-----------------------------------------------------------------------------
// Name: ~CColor
// Type: Destructor
// Vis: Public
// Desc: Destroys this instance.
//-----------------------------------------------------------------------------
CColor::~CColor(void)
{
}


#if (GRAPHICSAPI == DIRECTX10)
//-----------------------------------------------------------------------------
// Name: CColor
// Type: Constructor
// Vis: Private
// Desc: Creates a new color object that wraps DirectX10s color implementation
// Inputs:
//	- DXColor: A D3DXCOLOR struct containing the color data for this Color
//-----------------------------------------------------------------------------
CColor::CColor(D3DXCOLOR DXColor)
{
	m_DXColor = DXColor;
}
//-----------------------------------------------------------------------------
// Name: GetD3DXCOLOR
// Type: Getter
// Vis: Private
// Outputs:
//	- retval: A D3DXCOLOR struct containing this Color's data.
//-----------------------------------------------------------------------------
D3DXCOLOR CColor::GetD3DXCOLOR(void) const
{
	return m_DXColor;
}
#endif
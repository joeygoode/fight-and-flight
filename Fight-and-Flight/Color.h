#pragma once
#include "GFXAPIBase.h"

class CColor : public CGFXAPIBase
{
	friend class CDirectXManager;
	friend class CFontObj;
public:
	//Constructor for Colors
	CColor(float r, float g, float b, float a);
	//Destructor for Colors
	~CColor(void);

// If using DirectX 10, use the following methods
#if (GRAPHICSAPI == DIRECTX10)
private:
	//Use a D3DXCOLOR struct to create a Color
	CColor(D3DXCOLOR DXColor);
	//Get a D3DXCOLOR from this color
	D3DXCOLOR GetD3DXCOLOR(void) const;
	// The wrapped D3DXCOLOR
	D3DXCOLOR m_DXColor;
#endif
};


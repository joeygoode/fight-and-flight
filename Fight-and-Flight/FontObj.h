#pragma once
#include "GFXAPIBase.h"
#include <string>
using namespace std;


class CFontObj : public CGFXAPIBase
{
public:
	//Constructor for font objects.  Use CDirectXManager::CreateFontObj to initialize
	CFontObj(void);
	//Destructor for font objects
	~CFontObj(void);
	//Draw the font object to the screen
	void Draw(int x, int y,const string& text,const CColor& color) const;

	friend class CDirectXManager;
private:
	// A pointer to the wrapped font.
	ID3DX10Font* m_pDXFont;
	// A pointer to the sprite object used to draw this font.
	ID3DX10Sprite* m_pDXSprite;
	// A pointer to the device, so that we can save the depth buffer state before drawing.
	ID3D10Device* m_pD3DDevice;
};


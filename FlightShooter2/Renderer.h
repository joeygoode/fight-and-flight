#pragma once
#include "MyDirectX.h"
#include "Component.h"

class CRenderer
	: public CComponent
{
public:
	CRenderer(int* width, int* height, D3DXVECTOR2* position, float* rotation, 
					 D3DXVECTOR2* scale, int* framenum, bool animseqishoriz, 
					 int numroworcol, int horizoffset, int vertoffset, int delim);
	~CRenderer(void);
	void Draw(LPDIRECT3DTEXTURE9 spritesheet);
	//Get a transform matrix for this CRenderer object
	D3DXMATRIX				GetMatrix() const;
	static LPD3DXMATRIXSTACK m_MatrixStack;
	static void Init_Matrix_Stack();
private:
	int* m_FrameNum;
	//This data is taken from looking at the sprite sheet
	//and used to determine which section of the sprite sheet to pull
	//There's no reason for it to change during runtime unless
	//the sprite sheet is being swapped out.
	bool m_AnimSeqIsHoriz;
	int m_NumRowOrCol;
	int m_HorizOffset;
	int m_VertOffset;
	int m_Delim;
};


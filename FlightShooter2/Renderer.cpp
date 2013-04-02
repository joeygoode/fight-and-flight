#include "Renderer.h"

LPD3DXMATRIXSTACK CRenderer::m_MatrixStack = NULL;

CRenderer::CRenderer(int* width, int* height, D3DXVECTOR2* position, float* rotation, 
					 D3DXVECTOR2* scale, int* framenum, bool animseqishoriz, 
					 int numroworcol, int horizoffset, int vertoffset, int delim)
	: CComponent(width, height, position, rotation, scale)
{
	m_FrameNum = framenum;
	m_AnimSeqIsHoriz = animseqishoriz;
	m_NumRowOrCol = numroworcol;
	m_HorizOffset = horizoffset;
	m_VertOffset = vertoffset;
	m_Delim = delim;
}


CRenderer::~CRenderer(void)
{
}

void CRenderer::Draw(LPDIRECT3DTEXTURE9 spritesheet)
{
	RECT srcRect = Sprite_Get_SrcRect(*m_FrameNum,*m_Width,*m_Height,m_AnimSeqIsHoriz,m_NumRowOrCol,m_HorizOffset,m_VertOffset,m_Delim);
	spriteobj->SetTransform(m_MatrixStack->GetTop());
	spriteobj->Draw(spritesheet,&srcRect,NULL,NULL,D3DCOLOR_XRGB(255,255,255));
}

void CRenderer::Init_Matrix_Stack()
{
	D3DXCreateMatrixStack(0,&m_MatrixStack);
}

//Get a transform matrix for this CRenderer object
D3DXMATRIX	CRenderer::GetMatrix() const
{
	D3DXVECTOR2 center = D3DXVECTOR2((float) *m_Width/2, (float) *m_Height/2);
	D3DXVECTOR2 position = D3DXVECTOR2(m_Position->x - *m_Width / 2, m_Position->y - *m_Height / 2);
	D3DXMATRIX matrix;
	D3DXMatrixTransformation2D(&matrix,&center,NULL,m_Scale,&center,D3DXToRadian(*m_Rotation),&position);
	return matrix;
}

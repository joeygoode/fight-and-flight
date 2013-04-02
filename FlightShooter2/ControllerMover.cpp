#include "ControllerMover.h"

// Magic Numbers for player control
int MOVEDISTANCE;

CControllerMover::CControllerMover(int* width, int* height, D3DXVECTOR2* position, float* rotation, D3DXVECTOR2* scale, int* framenum)
	:CMover(width, height, position, rotation, scale)
{
	m_FrameNum = framenum;
	TiXmlDocument doc( "InitialWorld.xml" );
	doc.LoadFile();
	TiXmlHandle hDoc(&doc);
	TiXmlElement* pElem;
	TiXmlHandle hRoot(0);
	hRoot = hDoc.FirstChildElement("World");
	pElem = hRoot.FirstChildElement("PlayerConstants").Element();
	pElem->Attribute("MOVEDISTANCE",&MOVEDISTANCE);
}


CControllerMover::~CControllerMover(void)
{
}

void			CControllerMover::Advance()
{
	*m_Position = *m_NextPosition;
	if(Key_Down(DIK_LEFT) && m_Position->x >= (*m_Width / 2))
		m_NextPosition->x -= MOVEDISTANCE;
	if(Key_Down(DIK_RIGHT) && m_Position->x <= (SCREENW - *m_Width / 2))
		m_NextPosition->x += MOVEDISTANCE;
	*m_FrameNum += 1;
	*m_FrameNum %= 3;
}

bool			CControllerMover::IsTimeToKill()
{
	return false;
}
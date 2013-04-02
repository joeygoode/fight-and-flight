#include "Player.h"
#include "MyDirectX.h"
#include <sstream>

//CPlayer* CPlayer::s_Singleton = NULL;

int STARTY = SCREENH - 50;

CPlayer::CPlayer()
	:CEntity(64, 64, D3DXVECTOR2((float) (SCREENW /2),(float) STARTY), CPlayer::GenerateHitboxVector(), true, 3, 0.0f, 
	D3DXVECTOR2(1,1), 4, 32*12+16, 2, 0, forward_list<CEntity>())
{
	m_Cash = 0;
	m_OverlayFont = MakeFont("Arial",24);
}


CPlayer::~CPlayer()
{
	m_OverlayFont->Release();
}

void CPlayer::ResetPlayer()
{
	m_Position->x = (float) (SCREENW / 2);
	m_Position->y = (float) STARTY;
	*m_FrameNum = 0;
}

vector<D3DXVECTOR2>	CPlayer::GenerateHitboxVector()
{
	vector<D3DXVECTOR2> container = vector<D3DXVECTOR2>();
	container.push_back(D3DXVECTOR2(0,0));
	container.push_back(D3DXVECTOR2(64,0));
	container.push_back(D3DXVECTOR2(0,64));
	container.push_back(D3DXVECTOR2(64,64));
	return container;
}

void CPlayer::DrawExtras()
{
	ostringstream convert;
	convert << m_Cash;
	FontPrint(m_OverlayFont, 50 ,SCREENH - 50,"$" + convert.str());
}

void CPlayer::GiveMoney(int money)
{
	m_Cash += money;
}
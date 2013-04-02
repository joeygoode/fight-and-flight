#include "World.h"
#include "Level.h"
#include "EFighter.h"
#include "Enemy.h"
#include "Player.h"
#include <list>
//TinyXML
#include "tinystr.h"
#include "tinystr.cpp"
#include "tinyxml.h"
#include "tinyxml.cpp"
#include "tinyxmlparser.cpp"
#include "tinyxmlerror.cpp"
//CWorld* CWorld::s_Singleton = NULL;
CWorld::CWorld()
{
	m_Player = new CPlayer();
	m_Levels = vector<CLevel*>();
	m_CurrentLevel = 0;
	m_SpriteSheet = NULL;
	list<CEnemy*> v = list<CEnemy*>();
	CLevel* level1 = new CLevel(v);
	m_Levels.push_back(level1);
}

void CWorld::LoadData()
{
	TiXmlDocument doc( "InitialWorld.xml" );
	doc.LoadFile();
	TiXmlHandle hDoc(&doc);
	TiXmlElement* pElem;
	TiXmlHandle hRoot(0);
	hRoot = hDoc.FirstChildElement("World");
	pElem = hRoot.FirstChildElement("WorldConstants").Element();
	int r,g,b;
	pElem->Attribute("colormatter",&r);
	pElem->Attribute("colormatteg",&g);
	pElem->Attribute("colormatteb",&b);
	m_SpriteSheet = LoadTexture(pElem->Attribute("spritesheet"),
		D3DCOLOR_XRGB(r,g,b));
	CEFighter::LoadData();
	for(auto itl = m_Levels.begin(); itl != m_Levels.end(); itl++)
	{
		(*itl)->LoadData();
	}
	
}


CWorld::~CWorld(void)
{
	delete m_Player;
	while (!m_Levels.empty())
	{
		delete m_Levels.back();
		m_Levels.pop_back();
	}
}


void CWorld::Update()
{
	m_Player->Update();
	m_Levels[m_CurrentLevel]->Update(m_Player);
	/*
	if (m_CurrentLevel > 0)
	{
		if (m_Levels[m_CurrentLevel]->IsComplete())
		{
			if (m_Levels.size() == m_CurrentLevel)
			{
				this->GameOver();
			}
			else
			{
				++m_CurrentLevel;
			}
		}
		m_Levels[m_CurrentLevel]->Update(m_Player);
	}
	*/
}
void CWorld::GameOver()
{
}
void CWorld::Draw()
{
	m_Levels[m_CurrentLevel]->Draw(m_SpriteSheet);
	m_Player->Draw(m_SpriteSheet);
}

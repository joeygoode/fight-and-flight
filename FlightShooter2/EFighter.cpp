#include "EFighter.h"

int framesarehoriz;
int numroworcol;
D3DXVECTOR2 scale;
int horizoffset;
int vertoffset;
int delim;
int framenum;
int value;

CEFighter::CEFighter(vector<KEYFRAME*> keyframes)
	: CEnemy(32, 32, keyframes, CEFighter::GenerateHitboxVector(), framesarehoriz, numroworcol, scale, horizoffset, vertoffset, delim, framenum, value)
{
}


CEFighter::~CEFighter(void)
{
}

vector<D3DXVECTOR2> CEFighter::GenerateHitboxVector()
{
	vector<D3DXVECTOR2> container = vector<D3DXVECTOR2>();
	container.push_back(D3DXVECTOR2(0,0));
	container.push_back(D3DXVECTOR2(32,0));
	container.push_back(D3DXVECTOR2(0,32));
	container.push_back(D3DXVECTOR2(32,32));
	return container;
}

void CEFighter::LoadData() 
{
	TiXmlDocument doc( "InitialWorld.xml" );
	doc.LoadFile();
	TiXmlHandle hDoc(&doc);
	TiXmlElement* pElem;
	TiXmlHandle hRoot(0);
	hRoot = hDoc.FirstChildElement("World");
	pElem = hRoot.FirstChildElement("FighterConstants").Element();
	if (!pElem)
	{
		//Elem is null, use default behavior
		framesarehoriz = true;
		numroworcol = 1;
		scale = D3DXVECTOR2(1,1);
		horizoffset = 4;
		vertoffset = 4;
		delim = 1;
		framenum = 0;
		value = 10;
	}
	else
	{
	pElem->Attribute("framesarehoriz",&framesarehoriz);
	pElem->Attribute("numroworcol", &numroworcol);
	scale = D3DXVECTOR2(1,1);
	pElem->Attribute("scalex", (double*)&scale.x);
	pElem->Attribute("scaley", (double*)&scale.y);
	pElem->Attribute("horizoffset", &horizoffset);
	pElem->Attribute("vertoffset", &vertoffset);
	pElem->Attribute("delim", &delim);
	pElem->Attribute("framenum", &framenum);
	pElem->Attribute("value", &value);
	}
}
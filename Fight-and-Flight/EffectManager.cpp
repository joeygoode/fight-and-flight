#include "EffectManager.h"

#include "Effect.h"
#include "../TinyXML/tinystr.h"
#include "../TinyXML/tinyxml.h"

CEffectManager* CEffectManager::s_Singleton = NULL;

CEffectManager* CEffectManager::Get(void)
{
	if (!s_Singleton)
		s_Singleton = new CEffectManager();
	return s_Singleton;
}

void CEffectManager::Clear(void)
{
	if (s_Singleton)
		delete s_Singleton;
	s_Singleton = NULL;
}

CEffectManager::CEffectManager(void)
{
	m_MaxEffects = 5;
	m_HighestAssigned = 0;
	m_CurrentEffect = 0;
	m_pEffects = vector<CEffect*>(m_MaxEffects);
	for (int i = 0; i <m_MaxEffects; i++)
	{
		m_pEffects[i] = new CEffect();
	}
}


CEffectManager::~CEffectManager(void)
{
}

bool CEffectManager::AllocateEffect(const string& filename)
{
	TiXmlDocument doc( filename.c_str() );
	doc.LoadFile();
	TiXmlHandle hDoc(&doc);
	TiXmlHandle hRoot(0);
	hRoot = hDoc.FirstChildElement("Effects").Element();
	for ( TiXmlElement *node = hRoot.FirstChildElement("Effect").Element(); node; node = node->NextSiblingElement("Effect"))
	{
		bool assigned = false;
		int top = (m_HighestAssigned == m_MaxEffects) ? m_MaxEffects : m_HighestAssigned + 1;
		for(int i = 0; i<top; i++)
		{
			if (!assigned && m_pEffects[i]->GetName().empty())
			{
				string effectfile = node->Attribute("filename");
				TiXmlElement *child;
				vector<string> names = vector<string>();
				vector<string> types = vector<string>();
				for( child = node->FirstChildElement("Variable"); child; child = child->NextSiblingElement("Variable"))
				{
					names.push_back(child->Attribute("name"));
					types.push_back(child->Attribute("type"));
				}
				CDirectXManager::Get()->CreateShader(effectfile, names, types, *m_pEffects[i]);
				++m_HighestAssigned;
			}
		}
	}
	return true;
}

CEffect* CEffectManager::GetEffectByIndex(int index) const
{
	if (index > m_HighestAssigned)
		return NULL;
	else
		return m_pEffects[index];
}

CEffect* CEffectManager::GetCurrentEffect(void) const
{
	return GetEffectByIndex(m_CurrentEffect);
}

int CEffectManager::GetEffectNumber(void) const
{
	return m_CurrentEffect;
}

void CEffectManager::Randomize(void)
{
	m_CurrentEffect = rand() % m_HighestAssigned;
}
#include <queue>
using std::queue;
#include <exception>
using std::exception;

#include "EntityManager.h"
#include "Entity.h"
#include "EntityRenderer.h"
#include "EntityTransform.h"
#include "EntityPhysics.h"
#include "Effect.h"
#include "Matrix.h"
#include "EntityControl.h"
#include "EffectManager.h"
#include <sstream>
using std::ostringstream;

#include "../TinyXML/tinystr.h"
#include "../TinyXML/tinyxml.h"

CEntityManager* CEntityManager::s_Singleton = NULL;

CEntityManager* CEntityManager::Get(void)
{
	if (!s_Singleton)
		s_Singleton = new CEntityManager();
	return s_Singleton;
}

void CEntityManager::Clear(void)
{
	if (s_Singleton)
		delete s_Singleton;
	s_Singleton = NULL;
}

CEntityManager::CEntityManager(void)
{
	m_MaxEntities = 200;
	m_HighestAssigned = 0;
	m_HighScore = 0;
	m_pEntities = new vector<CEntity>(m_MaxEntities);
	m_pRenderers = new vector<CEntityRenderer>(m_MaxEntities);
	m_pTransforms = new vector<CEntityTransform>(m_MaxEntities);
	m_pPhysics = new vector<CEntityPhysics>(m_MaxEntities);
	m_pControllers = new vector<CEntityControl>(m_MaxEntities);
	TiXmlDocument doc( "data.xml" );
	doc.LoadFile();
	TiXmlHandle hDoc(&doc);
	TiXmlHandle hRoot(0);
	hRoot = hDoc.FirstChildElement("root").Element();
	hRoot.Element()->Attribute("hiscore", &m_HighScore);
}


CEntityManager::~CEntityManager(void)
{
	delete m_pEntities;
	delete m_pRenderers;
	delete m_pTransforms;
	delete m_pPhysics;
	delete m_pControllers;
	TiXmlDocument doc( "data.xml" );
	doc.LoadFile();
	TiXmlHandle hDoc(&doc);
	TiXmlHandle hRoot(0);
	hRoot = hDoc.FirstChildElement("root").Element();
	hRoot.Element()->SetAttribute("hiscore", m_HighScore);
	doc.SaveFile();
}

ENTITY_DESC& CEntityManager::GetEntityDescFromFile(const string& filename, ENTITY_DESC& out)
{
	TiXmlDocument doc( filename.c_str() );
	doc.LoadFile();
	TiXmlHandle hDoc(&doc);
	TiXmlHandle hRoot(0);
	hRoot = hDoc.FirstChildElement("Entity").Element();
	out.name = hRoot.Element()->Attribute("name");
	out.mesh_id = hRoot.Element()->Attribute("mesh");
	string con = hRoot.Element()->Attribute("control");
	if (con == "player")
		out.playercontrol = true;
	else 
		out.playercontrol = false;
	hRoot.Element()->Attribute("hitpoints", &out.hitpoints);
	out.faction = hRoot.Element()->Attribute("faction");
	hRoot.Element()->Attribute("width", &out.width);
	hRoot.Element()->Attribute("height", &out.height);
	TiXmlElement *child;
	for( child = hRoot.FirstChildElement("Vec3").Element(); child; child = child->NextSiblingElement("Vec3"))
	{
		CVector3* vec;
		string type = child->Attribute("value");
		if (type == "position")
			vec = &out.position;
		else if (type == "orientation")
			vec = &out.orientation;
		else if (type == "scale")
			vec = &out.scale;
		else if (type == "velocity")
			vec = &out.velocity;
		else if (type == "rotational velocity")
			vec = &out.rotationalvelocity;
		else
			throw exception("Error reading XML.");
		double d;
		child->Attribute("x", &d);
		vec->SetX((float) d);
		child->Attribute("y", &d);
		vec->SetY((float) d);
		child->Attribute("z", &d);
		vec->SetZ((float) d);
	}
	out.hitbox = new vector<CVector3>();
	for( child = hRoot.FirstChildElement("Hitbox").FirstChildElement("Vec3").Element(); child; child = child->NextSiblingElement("Vec3"))
	{
		CVector3 vec;
		double d;
		child->Attribute("x", &d);
		vec.SetX((float) d);
		child->Attribute("y", &d);
		vec.SetY((float) d);
		child->Attribute("z", &d);
		vec.SetZ((float) d);
		out.hitbox->push_back(vec);
	}

	return out;
}

bool CEntityManager::AllocateEntityDynamic(const ENTITY_DESC& desc)
{
	int top = (m_HighestAssigned == m_MaxEntities) ? m_MaxEntities : m_HighestAssigned + 1;
	for(int i = 0; i<top; i++)
	{
		if ((*m_pEntities)[i].GetName().empty())
		{
			string name = desc.name;
			ostringstream convert;
			convert << i;
			name.append(convert.str());
			(*m_pEntities)[i].SetName(name);
			(*m_pEntities)[i].SetHitpoints(desc.hitpoints);
			(*m_pEntities)[i].SetFaction(desc.faction);
			(*m_pRenderers)[i].SetMeshID(desc.mesh_id);
			(*m_pTransforms)[i].SetPosition(desc.position);
			(*m_pTransforms)[i].SetOrientation(desc.orientation);
			(*m_pTransforms)[i].SetScale(desc.scale);
			(*m_pPhysics)[i].SetVelocity(desc.velocity);
			(*m_pPhysics)[i].SetRotationalVelocity(desc.rotationalvelocity);
			(*m_pPhysics)[i].SetWidth(desc.width);
			(*m_pPhysics)[i].SetHeight(desc.height);
			(*m_pPhysics)[i].DeleteHitbox();
			(*m_pPhysics)[i].SetHitbox(desc.hitbox);
			(*m_pControllers)[i].SetControl(desc.playercontrol);
			++m_HighestAssigned;
			return true;
		}
	}
	return false;
}

bool CEntityManager::AllocateEntity(const ENTITY_DESC& desc)
{
	int top = (m_HighestAssigned == m_MaxEntities) ? m_MaxEntities : m_HighestAssigned + 1;
	for(int i = 0; i<top; i++)
	{
		if ((*m_pEntities)[i].GetName().empty())
		{
			(*m_pEntities)[i].SetName(desc.name);
			(*m_pEntities)[i].SetHitpoints(desc.hitpoints);
			(*m_pRenderers)[i].SetMeshID(desc.mesh_id);
			(*m_pTransforms)[i].SetPosition(desc.position);
			(*m_pTransforms)[i].SetOrientation(desc.orientation);
			(*m_pTransforms)[i].SetScale(desc.scale);
			(*m_pPhysics)[i].SetVelocity(desc.velocity);
			(*m_pPhysics)[i].SetRotationalVelocity(desc.rotationalvelocity);
			(*m_pPhysics)[i].SetWidth(desc.width);
			(*m_pPhysics)[i].SetHeight(desc.height);
			(*m_pPhysics)[i].DeleteHitbox();
			(*m_pPhysics)[i].SetHitbox(desc.hitbox);
			(*m_pControllers)[i].SetControl(desc.playercontrol);
			++m_HighestAssigned;
			return true;
		}
	}
	return false;
}

bool CEntityManager::ProcessAllEntities(float ElapsedTime, float TotalTime, CEffect* pEffect)
{
	if (ElapsedTime <= 0.0)
		ElapsedTime = 0.001f;
	if (ElapsedTime > 0.03f)
		ElapsedTime = 0.03f;
	for(int i = 0; i < m_HighestAssigned; i++)
	{
		if (!(*m_pEntities)[i].GetName().empty())
		{
			(*m_pControllers)[i].Update(TotalTime, &(*m_pPhysics)[i],&(*m_pTransforms)[i],&(*m_pEntities)[i]);
			(*m_pPhysics)[i].Update(ElapsedTime,i, m_HighestAssigned,m_pPhysics, m_pTransforms,m_pEntities);
			
		}
	}
	for(int i = 0; i < m_HighestAssigned; i++)
	{
		if (!(*m_pEntities)[i].GetName().empty())
		{
			(*m_pEntities)[i].UpdateHP();
			if ((*m_pEntities)[i].GetHitpoints() == 0)
			{
				if ((*m_pEntities)[i].GetName() == "player")
					m_HighScore = (*m_pEntities)[i].m_AddtlData;
				if ((*m_pEntities)[i].GetName() == "power-up")
				{
					CEffectManager::Get()->Randomize();
					CEntity* player = NULL;
					if(GetEntityByName("player", player))
					++player->m_AddtlData;
				}
				if ((*m_pEntities)[i].GetName().substr(0,5) == "Enemy")
				{
					ENTITY_DESC desc;
					GetEntityDescFromFile("powerup.xml", desc);
					desc.position = (*m_pTransforms)[i].GetPosition();
					AllocateEntityDynamic(desc);
				}
				(*m_pEntities)[i].SetName("");
				CEntity* player = NULL;
				if(GetEntityByName("player", player))
					++player->m_AddtlData;
			}
			else if ((*m_pTransforms)[i].GetPosition().GetZ() > 130.0f ||(*m_pTransforms)[i].GetPosition().GetZ() < -10.0f )
				(*m_pEntities)[i].SetName("");
			else
			{
				pEffect->SetVariableByName("World",(*m_pTransforms)[i].GetMatrix());
				for( UINT p = 0; p < pEffect->GetTechDesc().Passes; p++ )
				{
					pEffect->GetTechnique()->GetPassByIndex( p )->Apply( 0 );
					(*m_pRenderers)[i].Draw();
				}
			}
		}
	}
	return true;
}

bool CEntityManager::KillByName(const string& name)
{
	for (int i = 0; i < m_MaxEntities; i++)
	{
		if (name == (*m_pEntities)[i].GetName())
		{
			(*m_pEntities)[i].Clear();
			return true;
		}
	}
	return false;
}

int CEntityManager::Compact(void)
{
	queue<int> unused = queue<int>();
	for (int i = 0; i < m_MaxEntities; i++)
	{
		if ((*m_pEntities)[i].GetName().empty())
		{
			unused.push(i);
		}
		else if (!unused.empty())
		{
			std::swap((*m_pEntities)[i],(*m_pEntities)[unused.front()]);
			std::swap((*m_pRenderers)[i],(*m_pRenderers)[unused.front()]);
			std::swap((*m_pTransforms)[i],(*m_pTransforms)[unused.front()]);
			unused.pop();
		}
	}
	return unused.size();
}

bool CEntityManager::GetEntityByName(const string& name, CEntity*& out) const
{
	for (int i = 0; i < m_MaxEntities; i++)
	{
		if ((*m_pEntities)[i].GetName() == name)
		{
			out = &(*m_pEntities)[i];
 			return true;
		}
	}
	return false;
}
#pragma once
#include <vector>
using std::vector;
#include <string>
using std::string;

#include "Vector3.h"
struct ENTITY_DESC
{
	string name;
	string mesh_id;
	CVector3 position;
	CVector3 orientation;
	CVector3 scale;
};

class CEntity;
class CEntityRenderer;
class CEntityTransform;
class CEffect;

//-----------------------------------------------------------------------------
// Name: CEntityManager
// Desc: Manages and constructs new enitites.  Contains a vector with a number
// of entites equal to the maximum number of entities.  When a new entity is
// requested, it finds the first entity with a non-null name string, and
// assigns the new entity to that place in the vector.  The entities position
// in the m_pEntities vector corresponds to it's position in the component
// vectors. 
//
// Hopefully we can get a compacting method written that will move all the
// entities into the first n slots in the vector.  We'll try to do it using
// swap at some point.
//-----------------------------------------------------------------------------
class CEntityManager
{
	int m_MaxEntities;
	int m_HighestAssigned;
	vector<CEntity>* m_pEntities;
	vector<CEntityRenderer>* m_pRenderers;
	vector<CEntityTransform>* m_pTransforms;
	static CEntityManager* s_Singleton;
public:
	static CEntityManager* Get(void);
	static void Clear(void);
	// Assigns a new entity from the pool.  Ensures that it's position
	// in other vectors has been reset.
	bool AllocateEntity(ENTITY_DESC desc);
	// Passes the physics vector and updates each entity.
	void DrawAllEntities(CEffect* pEffect) const;
	bool KillByName(const string& name);
	int Compact(void);
private:
	CEntityManager(void);
	~CEntityManager(void);
};


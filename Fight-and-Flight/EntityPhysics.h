#pragma once
#include "Vector3.h"

class CEntityTransform;
class CEntity;

class CEntityPhysics
{
	CVector3 m_Velocity;
	CVector3 m_RotationalVelocity;
	CVector3 m_PreviousPosition;
	vector<CVector3>* m_pVertices;
	int m_width;
	int m_height;
public:
	CEntityPhysics(void);
	~CEntityPhysics(void);
	void Update(float ElapsedTime,int index, int top, vector<CEntityPhysics>* physics, vector<CEntityTransform>* transforms, vector<CEntity>* entities);
	void SetVelocity(const CVector3& vec);
	void SetVelocity(float x, float y, float z);
	void SetRotationalVelocity(const CVector3& vec);
	void SetRotationalVelocity(float x, float y, float z);
	void SetWidth(int width);
	void SetHeight(int height);
	void SetHitbox(vector<CVector3>* hitbox);
	void DeleteHitbox(void);
private:
	int GetBoundingCircleRadiusSq(void) const;
	void GetVertices(const CMatrix& matrix, vector<CVector3>& out) const;
	bool BoundingCircleCollide(const CEntityPhysics& that, const CEntityTransform& thistransform, const CEntityTransform& thattransform) const;
	bool HitboxCollide(const CEntityPhysics& that, const CEntityTransform& thistransform, const CEntityTransform& thattransform) const;
	static bool Intersect(const CVector3& a, const CVector3& b, const CVector3& c, const CVector3& d);
	bool CollideWith(const CEntityPhysics& that, const CEntityTransform& thistransform, const CEntityTransform& thattransform) const;
};


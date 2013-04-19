#include "EntityPhysics.h"
#include "EntityTransform.h"
#include "Entity.h"
#include "Matrix.h"


CEntityPhysics::CEntityPhysics(void)
{
	m_pVertices = NULL;
}


CEntityPhysics::~CEntityPhysics(void)
{
	if (m_pVertices)
		delete m_pVertices;
}

void CEntityPhysics::Update(float ElapsedTime,int index, int top, vector<CEntityPhysics>* physics, vector<CEntityTransform>* transforms, vector<CEntity>* entities)
{
	for (int i = 0; i < top; i++)
	{
		if (i != index && (*entities)[i].GetFaction() != "neutral" && (*entities)[index].GetFaction() != "neutral" )
		{
			if (CollideWith((*physics)[i],(*transforms)[index],(*transforms)[i]) && (*entities)[index].GetFaction() != (*entities)[i].GetFaction())
				(*entities)[index].HurtMe((*entities)[i].GetHitpoints());
		}
		(*transforms)[index].Translate(m_Velocity * ElapsedTime);
		(*transforms)[index].Rotate(m_RotationalVelocity * ElapsedTime);
	}
}

void CEntityPhysics::SetVelocity(const CVector3& vec)
{
	m_Velocity.Set(vec);
}

void CEntityPhysics::SetVelocity(float x, float y, float z)
{
	m_Velocity.Set(CVector3(x,y,z));
}

void CEntityPhysics::SetRotationalVelocity(const CVector3& vec)
{
	m_RotationalVelocity.Set(vec);
}

void CEntityPhysics::SetRotationalVelocity(float x, float y, float z)
{
	m_RotationalVelocity.Set(CVector3(x,y,z));
}

//Get the bounding radius of this CCollider object
int CEntityPhysics::GetBoundingCircleRadiusSq() const
{
	return (int) (m_width * m_width + m_height * m_height);
}

//Get the hitbox vector for this CCollider object
void CEntityPhysics::GetVertices(const CMatrix& matrix, vector<CVector3>& out) const
{
	out = vector<CVector3>();
	for (auto it = m_pVertices->cbegin(); it != m_pVertices->cend(); it++)
	{
		out.push_back(it->Transform(matrix));
	}
}

//Did this CCollider object collide with that CCollider object
bool	CEntityPhysics::CollideWith(const CEntityPhysics& that, const CEntityTransform& thistransform, const CEntityTransform& thattransform) const
{
	if(this->BoundingCircleCollide(that,thistransform,thattransform))
	{
		bool movementintersection = Intersect(thistransform.GetPosition(),this->m_PreviousPosition,thattransform.GetPosition(),that.m_PreviousPosition);
		return this->HitboxCollide(that,thistransform,thattransform) || movementintersection;
	}
	else
		return false;
}

bool	CEntityPhysics::BoundingCircleCollide(const CEntityPhysics& that, const CEntityTransform& thistransform, const CEntityTransform& thattransform) const
{
	
	CVector3 thatPos = thattransform.GetPosition();
	CVector3 thisPos = thistransform.GetPosition();
	CVector3 centerToCenter = thatPos - thisPos;
	return centerToCenter.LengthSq() <= (this->GetBoundingCircleRadiusSq() + that.GetBoundingCircleRadiusSq());
}

// There could probably be a subroutine here, but I'll only fix it if it breaks.
bool CEntityPhysics::HitboxCollide(const CEntityPhysics& that, const CEntityTransform& thistransform, const CEntityTransform& thattransform) const
{
	if (m_pVertices == NULL || that.m_pVertices == NULL)
		return false;
	if (m_pVertices->size() == 0 || that.m_pVertices->size() == 0)
		return false;
	vector<CVector3>		thisboxes;
	this->GetVertices(thistransform.GetMatrix(), thisboxes);
	vector<CVector3>		thatboxes;
	that.GetVertices(thattransform.GetMatrix(), thatboxes);
	bool					intersection	= false;
	CVector3*				this_0			= &thisboxes[0];
	CVector3*				this_1			= NULL;
	CVector3*				this_2			= NULL;
	for (auto it = thisboxes.begin(); it != thisboxes.end(); it++)
	{
		if (!this_2)
		{
			this_2 = &*it;
		}
		else
		{
			this_1 = this_2;
			this_2 = &*it;
			CVector3* that_0	= &thatboxes[0];
			CVector3* that_1 = NULL;
			CVector3* that_2 = NULL;
			for (auto it2 = thatboxes.begin(); it2 != thatboxes.end(); it2++)
			{
				if (!that_2)
				{
					that_2 = &*it2;
				}
				else
				{
				that_1 = that_2;
				that_2 = &*it2;
				intersection = intersection || Intersect(*this_1,*this_2,*that_1,*that_2);
				}
			}
			intersection = intersection || Intersect(*this_2,*this_0,*that_2,*that_0);
		}
	}
	CVector3* that_0	= &thatboxes[0];
	CVector3* that_1 = NULL;
	CVector3* that_2 = NULL;
	for (auto it2 = thatboxes.begin(); it2 != thatboxes.end(); it2++)
	{
		if (!that_2)
		{
			that_2 = &*it2;
		}
		else
		{
			that_1 = that_2;
			that_2 = &*it2;
			intersection = intersection || Intersect(*this_1,*this_2,*that_1,*that_2);
		}
	}
	intersection = intersection || Intersect(*this_2,*this_0,*that_2,*that_0);
	return intersection;
}

bool CEntityPhysics::Intersect(const CVector3& a,const CVector3& b,const CVector3& c,const CVector3& d)
{
	float den = ((d.GetZ()-c.GetZ())*(b.GetX()-a.GetX())-(d.GetX()-c.GetX())*(b.GetZ()-a.GetZ())); 
	float num1 = ((d.GetX() - c.GetX())*(a.GetZ()-c.GetZ()) - (d.GetZ()- c.GetZ())*(a.GetX()-c.GetX())); 
	float num2 = ((b.GetX()-a.GetX())*(a.GetZ()-c.GetZ())-(b.GetZ()-a.GetZ())*(a.GetX()-c.GetX())); 
	float u1 = num1/den; 
	float u2 = num2/den;
	if (den == 0 && num1 == 0 && num2 == 0)
		/* The two lines are coincidents */
		return false;
	if (den == 0) 
		/* The two lines are parallel */ 
		return false; 
	if (u1 <0 || u1 > 1 || u2 < 0 || u2 > 1) 
		/* Lines do not collide */ 
		return false; 
	/* Lines DO collide */ 
	return true; 
} 

void CEntityPhysics::SetWidth(int width)
{
	m_width = width;
}
void CEntityPhysics::SetHeight(int height)
{
	m_height = height;
}
void CEntityPhysics::SetHitbox(vector<CVector3>* hitbox)
{
	m_pVertices = hitbox;
}
void CEntityPhysics::DeleteHitbox(void)
{
	if (m_pVertices)
		delete m_pVertices;
}

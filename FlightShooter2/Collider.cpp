#include "Collider.h"

//Constructor for CColliders
CCollider::CCollider(int* width, int* height, D3DXVECTOR2* position, vector<D3DXVECTOR2> vertices, float* rotation, D3DXVECTOR2* scale)
	: CComponent(width, height, position, rotation, scale)
{
	m_Vertices			= vector<D3DXVECTOR2*>();
	for (auto itv = vertices.begin(); itv != vertices.end(); itv++)
	{
		m_Vertices.push_back(&*itv);
	}
}

//Destructor for CColliders
CCollider::~CCollider(void)
{
	for (unsigned int i = 0; i < m_Vertices.size(); i++)
	{
		delete m_Vertices.back();
		m_Vertices.pop_back();
	}
}
//Get a transform matrix for this CComponent object
D3DXMATRIX	CCollider::GetMatrix() const
{
	D3DXVECTOR2 center = D3DXVECTOR2((float) *m_Width/2, (float) *m_Height/2);
	D3DXVECTOR2 position = D3DXVECTOR2(m_Position->x - *m_Width / 2, m_Position->y - *m_Height / 2);
	D3DXMATRIX matrix;
	D3DXMatrixTransformation2D(&matrix,&center,NULL,m_Scale,&center,D3DXToRadian(*m_Rotation),&position);
	return matrix;
}
//Get the bounding radius of this CCollider object
int CCollider::GetBoundingCircleRadiusSq() const
{
	return (int) (pow(*m_Width,2) + pow(*m_Height,2));
}
//Get the hitbox vector for this CCollider object
vector<D3DXVECTOR2>			CCollider::GetVertices() const
{
	D3DXMATRIX matrix = this->GetMatrix();
	vector<D3DXVECTOR2> absHitboxes = vector<D3DXVECTOR2>();
	for (auto it = m_Vertices.begin(); it != m_Vertices.end(); it++)
	{
		D3DXVECTOR4 temp;
		D3DXVec2Transform(&temp,*it, &matrix);
		D3DXVECTOR2 temp2 = D3DXVECTOR2(temp.x,temp.y);
		absHitboxes.push_back(temp2);
	}
	return absHitboxes;
}

//Did this CCollider object collide with that CCollider object
bool					CCollider::CollideWith(const CCollider* that, D3DXVECTOR2 thisnext, D3DXVECTOR2 thatnext) const
{
	if(this->BoundingCircleCollide(that))
	{
		bool movementintersection = intersect(this->GetPositon(),thisnext,that->GetPositon(),thatnext);
		return this->HitboxCollide(that) || movementintersection;
	}
	else
		return false;
}

bool					CCollider::BoundingCircleCollide(const CCollider* that) const
{
	D3DXVECTOR2 centerToCenter;
	D3DXVECTOR2 thatPos = that->GetPositon();
	D3DXVECTOR2 thisPos = this->GetPositon();
	D3DXVec2Subtract(&centerToCenter, &thatPos, &thisPos);
	return D3DXVec2LengthSq(&centerToCenter) <= (this->GetBoundingCircleRadiusSq() + that->GetBoundingCircleRadiusSq());
}

// There could probably be a subroutine here, but I'll only fix it if it breaks.
bool					CCollider::HitboxCollide(const CCollider* that) const
{
	vector<D3DXVECTOR2>		thisboxes		= this->GetVertices();
	vector<D3DXVECTOR2>		thatboxes		= that->GetVertices();
	bool					intersection	= false;
	D3DXVECTOR2*				this_0		= &thisboxes[0];
	D3DXVECTOR2*				this_1		= NULL;
	D3DXVECTOR2*				this_2		= NULL;
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
			D3DXVECTOR2* that_0	= &thatboxes[0];
			D3DXVECTOR2* that_1 = NULL;
			D3DXVECTOR2* that_2 = NULL;
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
				intersection = intersection || intersect(*this_1,*this_2,*that_1,*that_2);
				}
			}
			intersection = intersection || intersect(*this_2,*this_0,*that_2,*that_0);
		}
	}
	D3DXVECTOR2* that_0	= &thatboxes[0];
	D3DXVECTOR2* that_1 = NULL;
	D3DXVECTOR2* that_2 = NULL;
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
			intersection = intersection || intersect(*this_1,*this_2,*that_1,*that_2);
		}
	}
	intersection = intersection || intersect(*this_2,*this_0,*that_2,*that_0);
	return intersection;
}


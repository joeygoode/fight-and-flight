#pragma once
#include "MyDirectX.h"
#include "Component.h"
#include <vector>
/*
An Collider represents one solid collidable component of an entity.
If an entity needs multiple collideable components, it's best to give entity
multiple collider slots.  

The vertices need to be ordered to create a closed loop.  We assume that
there are at least two vertices, as this seems like a sensible assumption.
If you break the at least two vertices invariant, it will probably crash
the game.  Don't do it.

They should also probably be convex.  I have no idea if it will work for
concave objects.  Maybe.

The width and height should be taken from the sprite.  It would be best
if this was loaded directly from the sprite so there is no way to screw
it up.

The Constructor for Colliders accepts pointers to the all data,
since it is the assumption that this data will also be used for renderers and
the like. The wrapper class is responsible for deleting this data.  However, the
list of hitbox vertices is probably exclusive to the collider component and
so is passed in by value to ensure that it is never changed.

There is now a superclass for all components that holds common methods for all
components.  Generally utility methods that see use in multiple components should
be in the superclass. If most of the methods of two components overlap, they
should be merged instead.

The Destructor for Colliders is responsible for deleting the vertex vector.
*/
class CCollider
	: public CComponent
{
public:
	//Constructor for CColliders
							CCollider(int* width, int* height, D3DXVECTOR2* position, vector<D3DXVECTOR2> vertices, float* rotation, D3DXVECTOR2* scale);
	//Destructor for CColliders
							~CCollider();
	//Get the bounding radius of this CCollider object
	int						GetBoundingCircleRadiusSq() const;
	//Get the absolute vertices of this CCollider object
	vector<D3DXVECTOR2>		GetVertices() const;
	//Did this CCollider object collide with that CCollider object
	bool					CollideWith(const CCollider* that, D3DXVECTOR2 thisnext, D3DXVECTOR2 thatnext) const;
	//Get a transform matrix for this CCollider object
	D3DXMATRIX				GetMatrix() const;

private:
	//A vector of hitboxes for complex collisions
	//Based of m_BoundingBox.  Use GetHitboxes to get absolute hitboxes.
	//Hitboxes are oriented based on default orientation (i.e. m_orientation is (0,0))
	vector<D3DXVECTOR2*>	m_Vertices;
	//Test the two CColliders for a bounding box collision
	bool					BoundingCircleCollide(const CCollider* that) const;
	//Text the two CColliders for a per-pixel collision
	bool					HitboxCollide(const CCollider* that) const;

};


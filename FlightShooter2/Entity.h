#pragma once
#include "MyDirectX.h"
#include <vector>
#include <forward_list>
#include "Mover.h"
class CCollider;
class CRenderer;


class CEntity
{
public:
	~CEntity(void);
	D3DXVECTOR2		GetPosition();
	D3DXVECTOR2		GetScale();
	float			GetRotation();
	bool			CollideWith(const CEntity* that) const;
	bool			CollideWith(const CCollider* that, D3DXVECTOR2 thatnext) const;
	void			Draw(LPDIRECT3DTEXTURE9 spritesheet);
	void			Update();
	bool			IsTimeToKill();
protected:
	CEntity(int width, int height, vector<KEYFRAME*> keyframes, vector<D3DXVECTOR2> vertices, bool animseqishoriz, 
				 int numroworcol, D3DXVECTOR2 scale, int horizoffset, int vertoffset, int delim,
				 int framenum, forward_list<CEntity> children);
	CEntity(int width, int height, D3DXVECTOR2 position, D3DXVECTOR2 velocity, vector<D3DXVECTOR2> vertices, bool animseqishoriz, 
				 int numroworcol, float rotation, float rotationalvelocity, D3DXVECTOR2 scale, int horizoffset, int vertoffset, int delim,
				 int framenum, forward_list<CEntity> children);
	CEntity(int width, int height, D3DXVECTOR2 position, vector<D3DXVECTOR2> vertices, bool animseqishoriz, 
				 int numroworcol, float rotation, D3DXVECTOR2 scale, int horizoffset, int vertoffset, int delim,
				 int framenum, forward_list<CEntity> children);
	virtual void DrawExtras() {};
	//Easy refence pointers to commonly changed values
	//These will change values in the colliders, renderers, etc.
	//as they all point to the same place;

	D3DXVECTOR2*	m_Position;
	D3DXVECTOR2*	m_Scale;
	float*			m_Rotation;
	int*			m_Width;
	int*			m_Height;
	int*			m_FrameNum;
	//Component Pointers

	//Collider Component
	CCollider*		m_Collider;
	CMover* m_Mover;
	CRenderer* m_Renderer;

	//Forward list of child nodes
	forward_list<CEntity*> m_Children;
};


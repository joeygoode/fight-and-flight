#include "Entity.h"
#include "Collider.h"
#include "Renderer.h"
#include "ScriptedMover.h"
#include "DynamicMover.h"
#include "ControllerMover.h"

CEntity::CEntity(int width, int height, vector<KEYFRAME*> keyframes, vector<D3DXVECTOR2> vertices, bool animseqishoriz, 
				 int numroworcol, D3DXVECTOR2 scale, int horizoffset, int vertoffset, int delim,
				 int framenum, forward_list<CEntity> children)
{
	m_Position	= new D3DXVECTOR2(keyframes[0]->position.x, keyframes[0]->position.y);
	m_Scale		= new D3DXVECTOR2(scale.x, scale.y);
	m_Rotation	= new float(keyframes[0]->rotation);
	m_Width		= new int(width);
	m_Height	= new int(height);
	m_Collider	= new CCollider(m_Width, m_Height, m_Position, vertices, m_Rotation, m_Scale);
	m_FrameNum	= new int(framenum);
	m_Renderer	= new CRenderer(m_Width, m_Height, m_Position, m_Rotation, m_Scale, m_FrameNum, animseqishoriz, numroworcol, horizoffset, vertoffset, delim);
	m_Mover		= new CScriptedMover(m_Width, m_Height, m_Position, m_Rotation, m_Scale, keyframes);
	m_Children	= forward_list<CEntity*>();
}
CEntity::CEntity(int width, int height,D3DXVECTOR2 position, D3DXVECTOR2 velocity, vector<D3DXVECTOR2> vertices, bool animseqishoriz, 
				 int numroworcol, float rotation, float rotationalvelocity, D3DXVECTOR2 scale, int horizoffset, int vertoffset, int delim,
				 int framenum, forward_list<CEntity> children)
{
	m_Position	= new D3DXVECTOR2(position.x, position.y);
	m_Scale		= new D3DXVECTOR2(scale.x, scale.y);
	m_Rotation	= new float(rotation);
	m_Width		= new int(width);
	m_Height	= new int(height);
	m_Collider	= new CCollider(m_Width, m_Height, m_Position, vertices, m_Rotation, m_Scale);
	m_FrameNum	= new int(framenum);
	m_Renderer	= new CRenderer(m_Width, m_Height, m_Position, m_Rotation, m_Scale, m_FrameNum, animseqishoriz, numroworcol, horizoffset, vertoffset, delim);
	m_Mover		= new CDynamicMover(m_Width, m_Height, m_Position, m_Rotation, m_Scale, velocity, rotationalvelocity);
	m_Children	= forward_list<CEntity*>();
	for (auto it = children.begin(); it != children.end(); it++)
	{
		m_Children.push_front(&*it);
	}
}

CEntity::CEntity(int width, int height, D3DXVECTOR2 position, vector<D3DXVECTOR2> vertices, bool animseqishoriz, 
				 int numroworcol, float rotation, D3DXVECTOR2 scale, int horizoffset, int vertoffset, int delim,
				 int framenum, forward_list<CEntity> children)
{
	m_Position	= new D3DXVECTOR2(position.x, position.y);
	m_Scale		= new D3DXVECTOR2(scale.x, scale.y);
	m_Rotation	= new float(rotation);
	m_Width		= new int(width);
	m_Height	= new int(height);
	m_Collider	= new CCollider(m_Width, m_Height, m_Position, vertices, m_Rotation, m_Scale);
	m_FrameNum	= new int(framenum);
	m_Renderer	= new CRenderer(m_Width, m_Height, m_Position, m_Rotation, m_Scale, m_FrameNum, animseqishoriz, numroworcol, horizoffset, vertoffset, delim);
	m_Mover		= new CControllerMover(m_Width, m_Height, m_Position, m_Rotation, m_Scale, m_FrameNum);
	m_Children	= forward_list<CEntity*>();
	for (auto it = children.begin(); it != children.end(); it++)
	{
		m_Children.push_front(&*it);
	}
}

CEntity::~CEntity(void)
{
	delete m_Position;
	m_Position = NULL;
	delete m_Scale;
	m_Scale = NULL;
	delete m_Rotation;
	m_Rotation = NULL;
	delete m_Collider;
	m_Collider = NULL;
	delete m_Renderer;
	m_Renderer = NULL;
}

D3DXVECTOR2		CEntity::GetPosition()
{
	return *m_Position;
}

D3DXVECTOR2		CEntity::GetScale()
{
	return *m_Scale;
}

float			CEntity::GetRotation()
{
	return *m_Rotation;
}

bool			CEntity::CollideWith(const CEntity* that) const
{
	return that->CollideWith(m_Collider, m_Mover->GetNextPosition());
}

bool			CEntity::CollideWith(const CCollider* that, D3DXVECTOR2 thatnext) const
{
	return
		that->CollideWith(m_Collider, thatnext, m_Mover->GetNextPosition());
}

void			CEntity::Draw(LPDIRECT3DTEXTURE9 spritesheet)
{
	CRenderer::m_MatrixStack->Push();
	D3DXMATRIX matrix = m_Renderer->GetMatrix();
	CRenderer::m_MatrixStack->MultMatrix(&matrix);
	m_Renderer->Draw(spritesheet);
	for(auto it = m_Children.begin(); it != m_Children.end(); it++)
	{
		(*it)->Draw(spritesheet);
	}
	CRenderer::m_MatrixStack->Pop();
	this->DrawExtras();
}
void			CEntity::Update()
{
	m_Mover->Advance();
}
bool			CEntity::IsTimeToKill()
{
	return m_Mover->IsTimeToKill();
}
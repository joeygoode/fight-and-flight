#include "EntityRenderer.h"


CEntityRenderer::CEntityRenderer(void)
{
}


CEntityRenderer::~CEntityRenderer(void)
{
}

void CEntityRenderer::Clear(void)
{
	m_MeshID.clear();
}

void CEntityRenderer::SetMeshID(string MeshID)
{
	m_MeshID = MeshID;
}
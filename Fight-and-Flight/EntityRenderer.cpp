#include "EntityRenderer.h"
#include "MeshManager.h"

CEntityRenderer::CEntityRenderer(void)
{
}


CEntityRenderer::~CEntityRenderer(void)
{
}

void CEntityRenderer::SetMeshID(string MeshID)
{
	m_MeshID = MeshID;
}

void CEntityRenderer::Draw(void) const
{
	CMeshManager::Get()->DrawMeshByID(m_MeshID);
}
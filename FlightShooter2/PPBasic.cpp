#include "PPBasic.h"
#include "World.h"

CPPBasic::CPPBasic(D3DXVECTOR2 position) 
	: CPlayerProjectile(32, 32, position, D3DXVECTOR2(0,-5), CPPBasic::GenerateHitboxVector(), true, 1, 0.0f, 0.0f, D3DXVECTOR2(1,1),32 * 2 + 6, 32 * 6 + 10,1,0)
{
}


CPPBasic::~CPPBasic()
{
}

vector<D3DXVECTOR2> CPPBasic::GenerateHitboxVector()
{
	vector<D3DXVECTOR2> container = vector<D3DXVECTOR2>();
	container.push_back(D3DXVECTOR2(12,12));
	container.push_back(D3DXVECTOR2(20,12));
	container.push_back(D3DXVECTOR2(12,20));
	container.push_back(D3DXVECTOR2(20,20));
	return container;
}
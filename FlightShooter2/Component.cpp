#include "Component.h"
#include <vector>


//Constructor for CComponents
CComponent::CComponent(int* width, int* height, D3DXVECTOR2* position, float* rotation, D3DXVECTOR2* scale)
{
	m_Position			= position;
	m_Rotation			= rotation;
	m_Scale				= scale;
	m_Width				= width;
	m_Height			= height;
}

//Destructor for CComponents
CComponent::~CComponent(void)
{
}

//Get the position of this CComponent object
D3DXVECTOR2	CComponent::GetPositon() const
{
	return *m_Position;
}


//Get the orientation of this CComponent object
float	CComponent::GetRotation() const
{
	return *m_Rotation;
}

D3DXVECTOR2 CComponent::GetScale() const
{
	return *m_Scale;
}

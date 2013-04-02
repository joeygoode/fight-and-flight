#pragma once
#include "MyDirectX.h"
#include "tinyxml.h"
#include "tinystr.h"
/*
Component superclass from which all components will inherit.  Although
it has not abstract members, and thus can be instantiated, it really has
no use except as a container for common functions.  It's really an 
organizational structure and has no place in the rest of the code outside
of a component.  Don't instatiate it and don't create a variable with
type CComponent.

The CComponent base is not responsible for any of its member variables.
the wrapper class should instantiate, maintain, and delete all input 
variables.
*/
class CComponent
{
public:
	CComponent(int* width, int* height, D3DXVECTOR2* position, float* rotation, D3DXVECTOR2* scale);
	~CComponent();
	//Get the position of this CComponent object
	D3DXVECTOR2				GetPositon() const;
	//Get the orientation of this CComponent object
	float					GetRotation() const;
	//Get the scale of this CComponent object
	D3DXVECTOR2				GetScale() const;
protected:
	//Position vector (for placement)
	D3DXVECTOR2*			m_Position;
	//Rotation (from default, straight down for enemies, straight up for players)
	float*					m_Rotation;
	//Scale vector (for placement)
	D3DXVECTOR2*			m_Scale;
	//Width (in pixels) of the CComponent object
	int*					m_Width;
	//Height (in pixels) of the CComponent object
	int*					m_Height;
};


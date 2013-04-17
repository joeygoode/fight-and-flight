#pragma once
#include <exception>
#if (GRAPHICSAPI == DIRECTX10)
#include "DirectXManager.h"
#endif

class CColor;
class CEffect;
class CEffectVariable;
class CFontObj;
class CMatrix;
class CMesh;
class CVector3;
class CVector4;
class CQuaternion;

class CGFXAPIBase
{
public:
	CGFXAPIBase(void);
	~CGFXAPIBase(void);
	virtual CGFXAPIBase		operator=	(CGFXAPIBase that) { throw std::exception(); };
	virtual bool			operator==	(CGFXAPIBase that) { throw std::exception(); };
	virtual bool			operator<	(CGFXAPIBase that) { throw std::exception(); };

};


#pragma once
#include <string>
#include "Effect.h"
#include "Matrix.h"
#include "Vector4.h"
using namespace std;

#if (GRAPHICSAPI == DIRECTX10)
#include <D3D10.h>
#endif

enum EFFECTVARTYPE {
	MATRIX,
	SCALAR,
	VECTOR
};

class CEffectVariable
{
public:
	CEffectVariable(void);
	~CEffectVariable(void);
	bool SetMatrixVariable(CMatrix matrix) const;
	bool SetVectorVariable(CVector4 vector) const;
	bool SetScalarVariable(float f) const;
	string GetName() const;
private:
	string m_name;
	EFFECTVARTYPE m_type;

#if (GRAPHICSAPI == DIRECTX10)
public:
	static bool CreateEffectVariable(_In_ const string& name,_In_ const string& type,_In_ const CEffect& effect,_Out_ CEffectVariable* pOut);
private:
	ID3D10EffectVariable* m_pVar;  
#endif
};


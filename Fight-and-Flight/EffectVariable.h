#pragma once
#include <string>
using namespace std;
#include "GFXAPIBase.h"

// An enum type for specifying the type of variable that exists within the shader
enum EFFECTVARTYPE {
	MATRIX,
	SCALAR,
	VECTOR
};


class CEffectVariable : public CGFXAPIBase
{
public:
	// Destructor for effect variables
	~CEffectVariable(void);
	// Set a matrix variable.  Fails if the variable isn't a matrix variable
	bool SetMatrixVariable(const CMatrix& matrix) const;
	// Set a vector variable.  Fails if the variable isn't a vector variable
	bool SetVectorVariable(const CVector4& vector) const;
	// Set a scalar variable.  Fails if the variable isn't a vector variable
	bool SetScalarVariable(float f) const;
	// Gets the name of this variable
	string GetName() const;
	
	// Constructor for variables
	CEffectVariable(void);
	friend class CEffect;
private:
	// A string containing the name of the variable
	string m_name;
	// The type of the variable
	EFFECTVARTYPE m_type;

#if (GRAPHICSAPI == DIRECTX10)
private:
	// Builder for variables using DirectX 10
	static bool CreateEffectVariable(_In_ const string& name,_In_ const string& type,_In_ const CEffect& effect,_Out_ CEffectVariable* pOut);
	// A pointer to the stored variable
	ID3D10EffectVariable* m_pVar;  
#endif
};


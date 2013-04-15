#include "EffectVariable.h"
#include "Matrix.h"
#include "Vector4.h"
#include "Effect.h"



#if (GRAPHICSAPI == DIRECTX10)

//-----------------------------------------------------------------------------
// Name: CEffectVariable
// Type: Constructor
// Vis: Public
// Desc: Constructs a new EffectVariable.  xmemory wouldn't let me hide this
// method.  DON'T USE IT.
//-----------------------------------------------------------------------------
CEffectVariable::CEffectVariable(void)
{
	m_pVar = NULL;
}

//-----------------------------------------------------------------------------
// Name: ~CEffectVariable
// Type: Destructor
// Vis: Public
// Desc: Destroys the EffectVariable.  Since the content pointed to by
// m_pVar is owned by the effect, there's no need to clean it up.
//-----------------------------------------------------------------------------
CEffectVariable::~CEffectVariable(void)
{
}

//-----------------------------------------------------------------------------
// Name: SetMatrixVariable
// Type: Method
// Vis: Public
// Desc: Sets this uniform matrix variable if it is a matrix variable 
// Inputs:
//	- matrix: The matrix to set the variable with.
// Outputs:
//	- retval: False if this isn't a matrix variable
//-----------------------------------------------------------------------------
bool CEffectVariable::SetMatrixVariable(const CMatrix& matrix) const
{
	if (m_type == MATRIX)
	{
		((ID3D10EffectMatrixVariable*) m_pVar)->SetMatrix(matrix.GetD3DXMATRIX());
		return true;
	}
	else
		return false;
}

//-----------------------------------------------------------------------------
// Name: SetVectorVariable
// Type: Method
// Vis: Public
// Desc: Sets this uniform vector variable if it is a vector variable 
// Inputs:
//	- vector: The vector to set the variable with.
// Outputs:
//	- retval: False if this isn't a vector variable
//-----------------------------------------------------------------------------
bool CEffectVariable::SetVectorVariable(const CVector4& vector) const
{
	if (m_type == VECTOR)
	{
		((ID3D10EffectVectorVariable*) m_pVar)->SetFloatVector(vector.GetD3DXVECTOR4());
		return true;
	}
	else
		return false;
}

//-----------------------------------------------------------------------------
// Name: SetScalarVariable
// Type: Method
// Vis: Public
// Desc: Sets this uniform scalar variable if it is a scalar variable 
// Inputs:
//	- f: The float to set the variable with.
// Outputs:
//	- retval: False if this isn't a scalar variable
//-----------------------------------------------------------------------------
bool CEffectVariable::SetScalarVariable(float f) const
{
	if (m_type == SCALAR)
	{
		((ID3D10EffectScalarVariable*) m_pVar)->SetFloat(f);
		return true;
	}
	else
		return false;
}

//-----------------------------------------------------------------------------
// Name: GetName
// Type: Getter
// Vis: Public
// Desc: Get the name of this EffectVariable
// Outputs:
//	- retval: the name of this EffectVariable
//-----------------------------------------------------------------------------
string CEffectVariable::GetName() const
{
	return m_name;
}

//-----------------------------------------------------------------------------
// Name: CreateEffectVariable
// Type: Builder
// Vis: Public
// Desc: Does necessary set up for this EffectVariable
// Inputs:
//	- name: A name of a uniform varaible contain in the effect
//	- type: The type of the variable.  This ensures it cannot be set 
//			incorrectly.
//	- effect: The effect that owns this effect variable.
// Outputs:
//	- out: the EffectVariable to build.
//	- retval: False if the variable doesn't exist or the type is improperly 
//			  formatted.
//-----------------------------------------------------------------------------
bool CEffectVariable::CreateEffectVariable(_In_ const string& name,_In_ const string& type,_In_ const CEffect& effect,_Out_ CEffectVariable* pOut)
{
	pOut->m_name = name;
	ID3D10EffectVariable* pTempVar = effect.RetrieveVariableByName(pOut->m_name);
	if (type == "matrix")
	{
		pOut->m_type = MATRIX;
		pOut->m_pVar = pTempVar->AsMatrix();
	}
	else if (type == "scalar")
	{
		pOut->m_type = SCALAR;
		pOut->m_pVar = pTempVar->AsScalar();
	}
	else if (type == "vector")
	{
		pOut->m_type = VECTOR;
		pOut->m_pVar = pTempVar->AsVector();
	}
	else
		return false;
	return true;
}
#endif
#include "EffectVariable.h"

#if (GRAPHICSAPI == DIRECTX10)
CEffectVariable::CEffectVariable(void)
{
	m_pVar = NULL;
}

CEffectVariable::~CEffectVariable(void)
{
}

bool CEffectVariable::SetMatrixVariable(const CMatrix& matrix) const
{
#if (GRAPHICSAPI == DIRECTX10)
	if (m_type == MATRIX)
	{
		((ID3D10EffectMatrixVariable*) m_pVar)->SetMatrix(matrix.GetD3DXMATRIX());
		return true;
	}
	else
		return false;
#endif
}
bool CEffectVariable::SetVectorVariable(const CVector4& vector) const
{
#if (GRAPHICSAPI == DIRECTX10)
	if (m_type == VECTOR)
	{
		((ID3D10EffectVectorVariable*) m_pVar)->SetFloatVector(vector.GetD3DXVECTOR4());
		return true;
	}
	else
		return false;
#endif
}
bool CEffectVariable::SetScalarVariable(float f) const
{
#if (GRAPHICSAPI == DIRECTX10)
	if (m_type == SCALAR)
	{
		((ID3D10EffectScalarVariable*) m_pVar)->SetFloat(f);
		return true;
	}
	else
		return false;
#endif
}

string CEffectVariable::GetName() const
{
	return m_name;
}

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
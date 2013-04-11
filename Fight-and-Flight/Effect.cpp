#include "Effect.h"
#include "EffectVariable.h"
#include "Matrix.h"
#include "Vector4.h"
#include <algorithm>

bool CEffect::SetVariableByName(_In_ const string& name, _In_ const CMatrix& matrix) const
{
	CEffectVariable Temp;
	if (!this->GetVariableByName(name,Temp))
		return false;
	return Temp.SetMatrixVariable(matrix);
}
bool CEffect::SetVariableByName(_In_ const string& name, _In_ const CVector4& vector) const
{
	CEffectVariable* pTemp = NULL;
	if (!this->GetVariableByName(name,*pTemp))
		return false;
	return pTemp->SetVectorVariable(vector);
}
bool CEffect::SetVariableByName(_In_ const string& name, _In_ const float& f) const
{
	CEffectVariable* pTemp = NULL;
	if (this->GetVariableByName(name,*pTemp))
		return false;
	return pTemp->SetScalarVariable(f);
}
bool CEffect::GetVariableByName(_In_ const string& name, _Out_ CEffectVariable& out) const
{
	out = *find_if(m_FXVariables.begin(),
									m_FXVariables.end(), 
									[name](CEffectVariable var) throw() -> bool
	{
		if (var.GetName() == name)
			return true;
		else
			return false;
	});
	if (out.GetName() == name)
		return true;
	else
		return false;
}

#if (GRAPHICSAPI == DIRECTX10)
#include "DirectXManager.h"


CEffect::CEffect(ID3D10Effect* pDXEffect, ID3D10EffectTechnique* pDXTechnique, D3D10_TECHNIQUE_DESC DXTechDesc)
{
	m_pDXEffect = pDXEffect;
	m_pDXTechnique = pDXTechnique;
	m_DXTechDesc = DXTechDesc;
}

bool CEffect::Initialize(const vector<string>& names,const vector<string>& types)
{
	if (names.size() != types.size())
		return false;
	m_FXVariables.resize(names.size());
	for (unsigned int i = 0; i < names.size(); i++)
	{
		if (!CEffectVariable::CreateEffectVariable(names[i],types[i],*this, &m_FXVariables[i]))
			return false;
	}
	return true;
}

CEffect::~CEffect(void)
{
	if (m_pDXEffect)
		m_pDXEffect->Release();
}

ID3D10EffectTechnique* CEffect::GetTechnique() const
{
	return m_pDXTechnique;
}
D3D10_TECHNIQUE_DESC CEffect::GetTechDesc() const
{
	return m_DXTechDesc;
}
ID3D10EffectVariable* CEffect::RetrieveVariableByName(_In_ const string& name) const
{
	return m_pDXEffect->GetVariableByName(name.c_str());
}
#endif
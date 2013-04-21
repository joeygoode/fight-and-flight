#include "Effect.h"
#include "EffectVariable.h"
#include "Matrix.h"
#include "Vector4.h"
#include <algorithm>

string CEffect::GetName(void) const
{
	return m_name;
}
//-----------------------------------------------------------------------------
// Name: SetVariableByName
// Type: Method
// Vis: Public
// Desc: Sets a uniform matrix variable in the effect with the name "name".  
// Inputs:
//	- name: A string with the name of the variable to set.
//	- matrix: The matrix to set the variable with.
// Outputs:
//	- retval: False if the specified variable name wasn't found.
//-----------------------------------------------------------------------------
bool CEffect::SetVariableByName(_In_ const string& name, _In_ const CMatrix& matrix) const
{
	CEffectVariable* pTemp = NULL;
	if (!this->GetVariableByName(name,pTemp))
		return false;
	return pTemp->SetMatrixVariable(matrix);
}

//-----------------------------------------------------------------------------
// Name: SetVariableByName
// Type: Method
// Vis: Public
// Desc: Sets a uniform vector variable in the effect with the name "name".  
// Inputs:
//	- name: A string with the name of the variable to set.
//	- vector: The vector to set the variable with.
// Outputs:
//	- retval: False if the specified variable name wasn't found.
//-----------------------------------------------------------------------------
bool CEffect::SetVariableByName(_In_ const string& name, _In_ const CVector4& vector) const
{
	CEffectVariable* pTemp = NULL;
	if (!this->GetVariableByName(name,pTemp))
		return false;
	return pTemp->SetVectorVariable(vector);
}

//-----------------------------------------------------------------------------
// Name: SetVariableByName
// Type: Method
// Vis: Public
// Desc: Sets a uniform floating point variable in the effect with the name "name".  
// Inputs:
//	- name: A string with the name of the variable to set.
//	- f: The floating point number to set the variable with.
// Outputs:
//	- retval: False if the specified variable name wasn't found.
//-----------------------------------------------------------------------------
bool CEffect::SetVariableByName(_In_ const string& name, _In_ const float& f) const
{
	CEffectVariable* pTemp = NULL;
	if (this->GetVariableByName(name,pTemp))
		return false;
	return pTemp->SetScalarVariable(f);
}

//-----------------------------------------------------------------------------
// Name: GetVariableByName
// Type: Getter
// Vis: Private
// Desc: Gets a variable with the specified name from the variable vector  
// Inputs:
//	- name: A string with the name of the variable to get.
// Outputs:
//	- out: The stored variable.
//	- retval: False if the specified variable name wasn't found.
//-----------------------------------------------------------------------------
bool CEffect::GetVariableByName(_In_ const string& name, _Out_ CEffectVariable*& out) const
{
	// I would love it if someone would teach me a way to avoid const_casting here. It scares me,
	// but saves me an unnecessary assignment and copy of data.  It's worth it, considering it
	// happens every frame at least once, but there has to be a way to get a non-const pointer
	// out of find_if.
	out = const_cast<CEffectVariable*>(&*find_if(	m_FXVariables.begin(),
													m_FXVariables.end(), 
													[name](const CEffectVariable& var) throw() -> bool
	{
		if (var.GetName() == name)
			return true;
		else
			return false;
	}));
	if (out->GetName() == name)
		return true;
	else
		return false;
}

#if (GRAPHICSAPI == DIRECTX10)
#include "DirectXManager.h"

//-----------------------------------------------------------------------------
// Name: CEffect
// Type: Constructor
// Vis: Private
// Desc: Constructs a new Effect, wrapping the DirectX 10 library
// Inputs:
//	- pDXEffect: A pointer to the effect.
//	- pDXTechnique: A pointer to the technique we're using
//	- DXTechDesc:  A Technique Description structure
//-----------------------------------------------------------------------------
CEffect::CEffect()
{
	m_pDXEffect = NULL;
	m_pDXTechnique = NULL;
}

//-----------------------------------------------------------------------------
// Name: Initialize
// Type: Builder
// Vis: Private
// Desc: Initializes the Effect by creating references to it's variables  
// Inputs:
//	- name: A vector of strings with the names of the uniform variables of
//			the Effect
//	- types:  a vector of types to match the names
// Outputs:
//	- retval: False if the initialization failed.
//-----------------------------------------------------------------------------
bool CEffect::Initialize(const string& name, ID3D10Effect* pDXEffect, ID3D10EffectTechnique* pDXTechnique, D3D10_TECHNIQUE_DESC DXTechDesc, const vector<string>& names,const vector<string>& types)
{
	m_name = name;
	m_pDXEffect = pDXEffect;
	m_pDXTechnique = pDXTechnique;
	m_DXTechDesc = DXTechDesc;
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
//-----------------------------------------------------------------------------
// Name: ~CEffect
// Type: Destructor
// Vis: Public
// Desc: Destroys the CEffect and releases it's wrapped Effect. 
//-----------------------------------------------------------------------------
CEffect::~CEffect(void)
{
	if (m_pDXEffect)
		m_pDXEffect->Release();
}
//-----------------------------------------------------------------------------
// Name: GetTechnique
// Type: Getter
// Vis: Public
// Desc: Gets a pointer to the wrapped Technique
// Inputs:
// Outputs:
//	- retval: A pointer to the ID3D10EffectTechnique
//-----------------------------------------------------------------------------
ID3D10EffectTechnique* CEffect::GetTechnique() const
{
	return m_pDXTechnique;
}
//-----------------------------------------------------------------------------
// Name: GetTechDesc
// Type: Getter
// Vis: Public
// Desc: Gets a pointer to the wrapped technique description
// Outputs:
//	- retval: The wrapped technique description
//-----------------------------------------------------------------------------
D3D10_TECHNIQUE_DESC CEffect::GetTechDesc() const
{
	return m_DXTechDesc;
}
//-----------------------------------------------------------------------------
// Name: RetrieveVariableByName
// Type: Method
// Vis: Private
// Desc: Goes into the effect, and gets a new pointer to one of the effect
//		 variables  
// Inputs:
//	- name: A strings with the name of the variable to retrieve
// Outputs:
//	- retval: A pointer to the retrieved ID3D10EffectVariable
//-----------------------------------------------------------------------------
ID3D10EffectVariable* CEffect::RetrieveVariableByName(_In_ const string& name) const
{
	return m_pDXEffect->GetVariableByName(name.c_str());
}
#endif
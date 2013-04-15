#pragma once
#include <string>
#include <vector>
using namespace std;

#include "GFXAPIBase.h"

class CEffect : public CGFXAPIBase
{
public:
	~CEffect(void);
	//Initialize the effect and create it's variable vector.
	bool Initialize(_In_ const vector<string>& names, _In_ const vector<string>& types);
	//Set a matrix variable by it's name
	bool SetVariableByName(_In_ const string& name, _In_ const CMatrix& matrix) const;
	//Set a vector4 variable by it's name
	bool SetVariableByName(_In_ const string& name, _In_ const CVector4& vector) const;
	//Set a floating point variable by it's name
	bool SetVariableByName(_In_ const string& name, _In_ const float& f) const;
	friend class CDirectXManager;
	friend class CEffectVariable;
private:
	// A vector containing references to all the effects variables
	vector<CEffectVariable> m_FXVariables;
	// A helper method for setting variables
	bool GetVariableByName(_In_ const string& name, _Out_ CEffectVariable*& out) const;

// If we're using DirectX 10, use these methods.
#if (GRAPHICSAPI == DIRECTX10)
public:
	// Get the technique
	ID3D10EffectTechnique* GetTechnique() const;
	// Get the tech desc
	D3D10_TECHNIQUE_DESC GetTechDesc() const;
private:
	// Construct a new Effect
	CEffect(ID3D10Effect* pDXEffect, ID3D10EffectTechnique* pDXTechnique, D3D10_TECHNIQUE_DESC DXTechDesc);
	// Retrieve a variable from inside the effect.
	ID3D10EffectVariable* RetrieveVariableByName(_In_ const string& name) const;
	// A pointer to the effect.
	ID3D10Effect* m_pDXEffect;
	// A pointer to the technique
	ID3D10EffectTechnique* m_pDXTechnique;
	// A pointer to the technique description
	D3D10_TECHNIQUE_DESC m_DXTechDesc;
#endif
};


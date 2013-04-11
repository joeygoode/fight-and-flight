#pragma once
#include <string>
#include <vector>
using namespace std;
#if (GRAPHICSAPI == DIRECTX10)
#include <D3D10.h>
#endif

class CEffectVariable;
class CMatrix;
class CVector4;

class CEffect
{
public:
	~CEffect(void);
	
	bool Initialize(_In_ const vector<string>& names, _In_ const vector<string>& types);
	bool SetVariableByName(_In_ const string& name, _In_ const CMatrix& matrix) const;
	bool SetVariableByName(_In_ const string& name, _In_ const CVector4& vector) const;
	bool SetVariableByName(_In_ const string& name, _In_ const float& f) const;

private:
	vector<CEffectVariable> m_FXVariables;
	bool GetVariableByName(_In_ const string& name, _Out_ CEffectVariable& out) const;

#if (GRAPHICSAPI == DIRECTX10)
public:
	CEffect(ID3D10Effect* pDXEffect, ID3D10EffectTechnique* pDXTechnique, D3D10_TECHNIQUE_DESC DXTechDesc);
	ID3D10EffectTechnique* GetTechnique() const;
	D3D10_TECHNIQUE_DESC GetTechDesc() const;
	ID3D10EffectVariable* RetrieveVariableByName(_In_ const string& name) const;

private:
	ID3D10Effect* m_pDXEffect;
	ID3D10EffectTechnique* m_pDXTechnique;
	D3D10_TECHNIQUE_DESC m_DXTechDesc;
#endif


};


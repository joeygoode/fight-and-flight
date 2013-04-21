#pragma once

#include <vector>
using std::vector;

#include <string>
using std::string;

class CEffect;

class CEffectManager
{
	static CEffectManager* s_Singleton;
	int m_MaxEffects;
	int m_HighestAssigned;
	int m_CurrentEffect;
	vector<CEffect*> m_pEffects;
public:
	static CEffectManager* Get(void);
	static void Clear(void);
	bool AllocateEffect(const string& filename);
	CEffect* GetEffectByIndex(int index) const;
	CEffect* GetCurrentEffect(void) const;
	int GetEffectNumber(void) const;
	void Randomize(void);
private:
	CEffectManager(void);
	~CEffectManager(void);
};


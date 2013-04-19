#pragma once
#include <string>
using std::string;
class CEntity
{
	string m_name;
	int m_hitpoints;
	string m_faction;
public:
	CEntity(void);
	~CEntity(void);
	void SetName(const string& name);
	void SetHitpoints(int i);
	void HurtMe(int i);
	int GetHitpoints(void) const;
	const string& GetName(void) const;
	void SetFaction(const string& faction);
	const string& GetFaction(void) const;
	void Clear(void);
	
};


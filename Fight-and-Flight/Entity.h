#pragma once
#include <string>
using std::string;
class CEntity
{
public:
	CEntity(void);
	~CEntity(void);
	void SetName(string name);
	string GetName(void) const;
	void Clear(void);
private:
	string m_name;
};


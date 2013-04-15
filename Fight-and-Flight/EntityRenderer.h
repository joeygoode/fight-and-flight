#pragma once
#include <string>
using std::string;

class CEntityRenderer
{
	string m_MeshID;
public:
	CEntityRenderer(void);
	~CEntityRenderer(void);
	void SetMeshID(string MeshID);
	void Draw(void) const;
};


#pragma once
#include <string>
using std::string;

class CEntityRenderer
{
	string m_MeshID;
public:
	CEntityRenderer(void);
	~CEntityRenderer(void);
	void Clear();
	void SetMeshID(string MeshID);
};


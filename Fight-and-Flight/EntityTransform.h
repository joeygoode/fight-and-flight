#pragma once
#include "Vector3.h"

class CEntityTransform
{
	CVector3 m_Position;
	CVector3 m_Orientation;
	CVector3 m_Scale;
public:
	CEntityTransform(void);
	~CEntityTransform(void);
	const CVector3& GetPosition(void) const;
	const CVector3& GetOrientation(void) const;
	const CVector3& GetScale(void) const;
	void Translate(float x, float y, float z);
	void Translate(const CVector3& vec);
	void Rotate(float x, float y, float z);
	void Rotate(const CVector3& vec);
	void Scale(float x, float y, float z);
	void Scale(const CVector3& vec);
	void SetPosition(float x, float y, float z);
	void SetPosition(const CVector3& vec);
	void SetOrienation(float x, float y, float z);
	void SetOrientation(const CVector3& vec);
	void SetScale(float x, float y, float z);
	void SetScale(const CVector3& vec);
	CMatrix GetMatrix(void);
};


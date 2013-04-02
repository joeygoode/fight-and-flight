#pragma once
#include "mover.h"
class CScriptedMover :
	public CMover
{
public:
	CScriptedMover(int* width, int* height, D3DXVECTOR2* position, float* rotation, D3DXVECTOR2* scale, vector<KEYFRAME*> keyframes);
	~CScriptedMover(void);
	void			Advance();
	bool			IsTimeToKill();
	D3DXVECTOR2		GetNextPosition() const;
private:
	vector<KEYFRAME*>		m_Keyframes;
	KEYFRAME*				m_CurrentFrame;
	KEYFRAME*				m_NextFrame;
	int						m_CurrentFrameNum;
	bool					m_TimeToKill;
	void					AdvanceFrame();
	void					Update();
};


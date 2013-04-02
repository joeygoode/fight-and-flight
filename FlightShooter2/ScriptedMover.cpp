#include "ScriptedMover.h"


CScriptedMover::CScriptedMover(int* width, int* height, D3DXVECTOR2* position, float* rotation, D3DXVECTOR2* scale, vector<KEYFRAME*> keyframes)
	: CMover(width, height, position, rotation, scale)
{
	m_Keyframes = keyframes;
	m_CurrentFrame = m_Keyframes[0];
	m_NextFrame = m_CurrentFrame->next;
	m_NextPosition = new D3DXVECTOR2(position->x, position->y);
	m_CurrentFrameNum = 0;
	m_TimeToKill = false;
}


CScriptedMover::~CScriptedMover(void)
{
	while(!m_Keyframes.empty())
	{
		delete m_Keyframes.back();
		m_Keyframes.pop_back();
	}
}

void CScriptedMover::Advance()
{
	bool samepos	= *m_Position	== m_NextFrame->position;
	bool samerot	= *m_Rotation	== m_NextFrame->rotation;
	if (samepos && samerot)
		this->AdvanceFrame();
	else
		this->Update();
}

void CScriptedMover::AdvanceFrame()
{
	if (m_NextFrame->next)
	{
		KEYFRAME* nextcurr = m_NextFrame;
		KEYFRAME* nextnext = m_NextFrame->next;
		m_CurrentFrame = nextcurr;
		m_NextFrame = nextnext;
		m_CurrentFrameNum = 0;
	}
	else
	{
		m_TimeToKill = true;
	}
}

void CScriptedMover::Update()
{
	*m_Position = *m_NextPosition;
	D3DXVec2Lerp(m_NextPosition,&m_CurrentFrame->position,&m_NextFrame->position, (float) (m_CurrentFrameNum + 1) / (float) (m_CurrentFrame->framesuntilnext));
	float nextrot = m_NextFrame->rotation;
	if (m_NextFrame->rotation - m_CurrentFrame->rotation > 180)
		nextrot -= 360;
	if (m_NextFrame->rotation - m_CurrentFrame->rotation < -180)
		nextrot += 360;
	float newrot = m_CurrentFrame->rotation + (((float)(m_CurrentFrameNum + 1) / (float) (m_CurrentFrame->framesuntilnext)) * (float)(nextrot - m_CurrentFrame->rotation));
	if (newrot > 360)
		*m_Rotation = newrot - 360;
	else if (newrot < 0)
		*m_Rotation = newrot + 360;
	else
		*m_Rotation = newrot;
	m_CurrentFrameNum += 1;
}

bool CScriptedMover::IsTimeToKill()
{
	return m_TimeToKill;
}
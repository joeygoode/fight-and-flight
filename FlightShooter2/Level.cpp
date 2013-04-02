#include "Level.h"
#include "Player.h"
#include "PPBasic.h"
#include "PlayerProjectile.h"
#include "Enemy.h"
#include "EFighter.h"
int SHOTFRAME = 20;

CLevel::CLevel(list<CEnemy*> enemies)
{
	m_PlayerProjectiles = list<CPlayerProjectile*>();
	m_Enemies = enemies;
	m_Frames = 0;
}

CLevel::~CLevel(void)
{
	while (!m_Enemies.empty())
	{
		delete m_Enemies.back();
		m_Enemies.pop_back();
	}
	while (!m_PlayerProjectiles.empty())
	{
		delete m_PlayerProjectiles.back();
		m_PlayerProjectiles.pop_back();
	}
}
void CLevel::Draw(LPDIRECT3DTEXTURE9 spritesheet)
{
	DrawSurface(backbuffer,0,0,m_background);
	for(auto itp = m_PlayerProjectiles.begin(); itp != m_PlayerProjectiles.end();itp++)
	{
		(*itp)->Draw(spritesheet);
	}
	for(auto ite = m_Enemies.begin(); ite != m_Enemies.end(); ite++)
	{
		(*ite)->Draw(spritesheet);
	}
}

void CLevel::Update(CPlayer* player)
{
	if(Key_Down(DIK_SPACE) && m_Frames > SHOTFRAME)
	{
		m_PlayerProjectiles.push_back(new CPPBasic(player->GetPosition()));
		m_Frames = 0;
	}
	list<CPlayerProjectile*> newprojectiles = list<CPlayerProjectile*>();
	while (!m_PlayerProjectiles.empty())
	{
		CPlayerProjectile* current = m_PlayerProjectiles.back();
		if (!current->IsTimeToKill())
		{
			current->Update();
			newprojectiles.push_back(current);
		}
		m_PlayerProjectiles.pop_back();
	}
	m_PlayerProjectiles = newprojectiles;
	list<CEnemy*> newenemies = list<CEnemy*>();
	while (!m_Enemies.empty())
	{
		CEnemy* current = m_Enemies.back();
		if(!current->IsTimeToKill())
		{
			current->Update();
			newenemies.push_back(current);
		}
		m_Enemies.pop_back();
	}
	m_PlayerProjectiles = newprojectiles;
	m_Enemies = newenemies;
	for(auto itp = m_PlayerProjectiles.begin(); itp != m_PlayerProjectiles.end();itp++)
	{
		for(auto ite = m_Enemies.begin(); ite != m_Enemies.end(); ite++)
		{
			if((*itp)->CollideWith(*ite))
			{
				player->GiveMoney((*ite)->GetValue());
				newprojectiles.remove(*itp);
				newenemies.remove(*ite);
			}
		}
	}
	m_PlayerProjectiles = newprojectiles;
	m_Enemies = newenemies;
	if (rand() % 200 == 0)
	{
		KEYFRAME* k4 = new KEYFRAME(D3DXVECTOR2(SCREENW, 250), 225, 0, NULL);
		KEYFRAME* k3 = new KEYFRAME(D3DXVECTOR2(SCREENW / 2,500), 225, 120, k4);
		KEYFRAME* k2 = new KEYFRAME(D3DXVECTOR2(SCREENW / 2,500), 315, 30, k3);
		KEYFRAME* k1 = new KEYFRAME(D3DXVECTOR2(0,250), 315, 120, k2);
		vector<KEYFRAME*> frames = vector<KEYFRAME*>();
		frames.push_back(k1);
		frames.push_back(k2);
		frames.push_back(k3);
		frames.push_back(k4);
		CEFighter* e1 = new CEFighter(frames);
		m_Enemies.push_back(e1);
	}
	m_Frames += 1;
}

bool CLevel::IsComplete()
{
	return false;
}

void CLevel::LoadData()
{
	m_background = LoadSurface("background1.bmp");
}
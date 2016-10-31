#include "StdAfx.h"
#include "Village.h"
#include "Player.h"
#include "Monster.h"
#include "Factory.h"
#include "UI.h"
#include "CollisionMgr.h"


CVillage::CVillage(void)
{
	m_strKey = "Village";
}

CVillage::~CVillage(void)
{
	Release();
}

void CVillage::Initialize(void)
{
	LoadMap();
	LoadBmp();

	m_vecParent[OBJ_PLAYER].push_back(CFactory<CPlayer>::CreateParent(300.f, 300.f));
	m_vecUI.push_back(CFactory<CUI>::CreateUI(WINCX / 2.f, WINCY / 2.f, "UI"));

	((CPlayer*)m_vecParent[OBJ_PLAYER].back())->SetSkill(&m_vecParent[OBJ_SKILL]);

	for (int i = 0; i < 15; ++i)
	{
		m_vecParent[OBJ_MONSTER].push_back(CFactory<CMonster>::CreateParent(rand() % 1000, rand() % 600, "PurpleMushRoom_LEFT"));
	}
}

void CVillage::Progress(DWORD _delta)
{
	for (size_t i = 0; i < OBJ_END; ++i)
	{
		for (vector<CParent*>::iterator iter = m_vecParent[i].begin(); iter != m_vecParent[i].end();)
		{
			(*iter)->Progress(_delta);

			if ((*iter)->GetDestroy())
			{
				::Safe_Delete(*iter);
				iter = m_vecParent[i].erase(iter);

				if (iter == m_vecParent[i].end())
					break;
			}
			else
				++iter;
		}
	}
	
	for (size_t i = 0; i < m_vecUI.size(); ++i)
	{
		m_vecUI[i]->Progress(_delta);
	}

	CCollisionMgr::CollisionTile(&m_vecParent[OBJ_PLAYER], &m_vecTile);
	CCollisionMgr::CollisionTile(&m_vecParent[OBJ_MONSTER], &m_vecTile);
	CCollisionMgr::CollisionSKill(&m_vecParent[OBJ_SKILL], &m_vecParent[OBJ_MONSTER]);
}

void CVillage::Render(HDC hdc)
{
	BitBlt(m_BitMap["Back"]->GetMemdc(), 
		0 + m_vecParent[OBJ_PLAYER].back()->GetScroll().x,
		0 + m_vecParent[OBJ_PLAYER].back()->GetScroll().y, 
			1920, 680, 
			m_BitMap[m_strKey]->GetMemdc(),
			0, 0, SRCCOPY);

	for (size_t i = 0; i < OBJ_END; ++i)
	{
		for (vector<CParent*>::iterator iter = m_vecParent[i].begin(); iter != m_vecParent[i].end(); )
		{
			(*iter)->Render(m_BitMap["Back"]->GetMemdc());

			if (iter == m_vecParent[i].end())
				break;

			else
				++iter;
		}
	}

	for (size_t i = 0; i < m_vecUI.size(); ++i)
	{
		m_vecUI[i]->Render(m_BitMap["Back"]->GetMemdc());
	}
	

	BitBlt(hdc, 
			0, 0, 
			WINCX, WINCY, 
			m_BitMap["Back"]->GetMemdc(),
			0, 0, SRCCOPY);
}

void CVillage::Release(void)
{
}
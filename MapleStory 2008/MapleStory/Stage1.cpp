#include "StdAfx.h"
#include "Stage1.h"
#include "Player.h"
#include "Monster.h"
#include "Factory.h"
#include "UI.h"
#include "Portal.h"
#include "CollisionMgr.h"

CStage1::CStage1(void)
{
	m_strKey = "Stage1";
}

CStage1::~CStage1(void)
{
	Release();
}


void CStage1::Initialize(void)
{
	LoadMap();
	LoadBmp();

	m_vecParent[OBJ_PLAYER].back()->SetPos(100.f, 100.f);
	m_vecUI.push_back(CFactory<CUI>::CreateUI(WINCX / 2.f, WINCY / 2.f, "UI"));

	m_vecParent[OBJ_PORTAL].push_back(CFactory<CPortal>::CreateParent(100.f, 1190.f, "Portal"));
	((CPortal*)m_vecParent[OBJ_PORTAL].back())->SetPortal(1);

	m_vecParent[OBJ_PORTAL].push_back(CFactory<CPortal>::CreateParent(1650.f, 1190.f, "Portal"));
	((CPortal*)m_vecParent[OBJ_PORTAL].back())->SetPortal(3);

	((CPlayer*)m_vecParent[OBJ_PLAYER].back())->SetMapSize(1773.f, 1464.f);
}

void CStage1::Progress(DWORD _delta)
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

		if (GetAsyncKeyState(VK_UP) & 0x8001)
			CCollisionMgr::CollisionPortal(&m_vecParent[OBJ_PLAYER], &m_vecParent[OBJ_PORTAL]);

		CCollisionMgr::CollisionTile(&m_vecParent[OBJ_PLAYER], &m_vecTile);
		CCollisionMgr::CollisionTile(&m_vecParent[OBJ_MONSTER], &m_vecTile);
		CCollisionMgr::CollisionSKill(&m_vecParent[OBJ_SKILL], &m_vecParent[OBJ_MONSTER]);
}

void CStage1::Render(HDC hdc)
{
	BitBlt(m_BitMap["Back"]->GetMemdc(), 
		0 + m_vecParent[OBJ_PLAYER].back()->GetScroll().x,
		0 + m_vecParent[OBJ_PLAYER].back()->GetScroll().y, 
			1773, 1464, 
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

void CStage1::Release(void)
{
	
}
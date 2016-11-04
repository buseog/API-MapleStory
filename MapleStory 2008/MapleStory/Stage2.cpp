#include "StdAfx.h"
#include "Stage2.h"
#include "Player.h"
#include "Monster.h"
#include "Factory.h"
#include "UI.h"
#include "Portal.h"
#include "CollisionMgr.h"

CStage2::CStage2(void)
{
	m_strKey = "Stage2";
	m_vecPortal.push_back(CFactory<CPortal>::CreateParent(50.f, 570.f, "Portal"));
	((CPortal*)m_vecPortal.back())->SetPortal(2);

	m_vecPortal.push_back(CFactory<CPortal>::CreateParent(1800.f, 630.f, "Portal"));
	((CPortal*)m_vecPortal.back())->SetPortal(4);
}

CStage2::~CStage2(void)
{
	Release();
}

void CStage2::Initialize(void)
{
	LoadMap();
	LoadBmp();
	
	((CPlayer*)m_vecParent[PAR_PLAYER].back())->SetMapSize(1890, 941);
	m_pLoading = new CLoading();
}

void CStage2::Progress(DWORD _delta)
{
	KeyInput();
	UIDrag();

	for (size_t i = 0; i < PAR_END; ++i)
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
		
	for (size_t i = 0; i < UI_END; ++i)
	{
		if (m_bUIView[i])
		{
			m_vecUI[i].back()->Progress(_delta);
		}
	}

	for (size_t i = 0; i < m_vecPortal.size(); ++i)
	{
		m_vecPortal[i]->Progress(_delta);
	}

	if (m_pLoading)
	{
		m_pLoading->Progress(_delta);
		
		if (m_pLoading->GetDestroy())
			::Safe_Delete(m_pLoading);
	}

	if (GetAsyncKeyState(VK_UP))
		CCollisionMgr::CollisionPortal(&m_vecParent[PAR_PLAYER], &m_vecPortal);

	CCollisionMgr::CollisionPTile(&m_vecParent[PAR_PLAYER], &m_vecTile);
	CCollisionMgr::CollisionMTile(&m_vecParent[PAR_MONSTER], &m_vecTile);
	CCollisionMgr::CollisionSKill(&m_vecParent[PAR_SKILL], &m_vecParent[PAR_MONSTER]);
}

void CStage2::Render(HDC hdc)
{
	BitBlt(m_BitMap["Back"]->GetMemdc(), 
		0 + m_vecParent[PAR_PLAYER].back()->GetScroll().x,
		0 + m_vecParent[PAR_PLAYER].back()->GetScroll().y, 
			1890, 941, 
			m_BitMap[m_strKey]->GetMemdc(),
			0, 0, SRCCOPY);

	for (size_t i = 0; i < PAR_END; ++i)
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

	for (size_t i = 0; i < UI_END; ++i)
	{
		if (m_bUIView[i])
		{
			m_vecUI[i].back()->Render(m_BitMap["Back"]->GetMemdc());
		}
	}
	
	for (size_t i = 0; i < m_vecPortal.size(); ++i)
	{
		m_vecPortal[i]->Render(m_BitMap["Back"]->GetMemdc());
	}

	if (m_pLoading)
		m_pLoading->Render(m_BitMap["Back"]->GetMemdc());

	BitBlt(hdc, 
			0, 0, 
			WINCX, WINCY, 
			m_BitMap["Back"]->GetMemdc(),
			0, 0, SRCCOPY);
}

void CStage2::Release(void)
{	
	for (map<string, CBitBmp*>::iterator iter = m_BitMap.begin(); iter != m_BitMap.end(); ++iter)
	{
		::Safe_Delete(iter->second);
	}
	m_BitMap.clear();

	for (size_t i = 0; i < m_vecTile.size(); ++i)
	{
		::Safe_Delete(m_vecTile[i]);
	}
	m_vecTile.clear();

	for (size_t i = 0; i < m_vecPortal.size(); ++i)
	{
		::Safe_Delete(m_vecPortal[i]);
	}
	m_vecPortal.clear();
}
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
}

CStage2::~CStage2(void)
{
	Release();
}

void CStage2::Initialize(void)
{
	LoadMap();
	LoadBmp();

	m_vecParent[PAR_PLAYER].back()->SetPos(100.f, 100.f);

	m_vecPortal.push_back(CFactory<CPortal>::CreateParent(100.f, 570.f, "Portal"));
	((CPortal*)m_vecPortal.back())->SetPortal(2);

	m_vecPortal.push_back(CFactory<CPortal>::CreateParent(1700.f, 630.f, "Portal"));
	((CPortal*)m_vecPortal.back())->SetPortal(4);
	
	((CPlayer*)m_vecParent[PAR_PLAYER].back())->SetMapSize(1890, 941);

	CParent::SetBitMap(&m_BitMap);
	CUI::SetBitMap(&m_BitMap);
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

	if (GetAsyncKeyState(VK_UP) & 0x8001)
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

	BitBlt(hdc, 
			0, 0, 
			WINCX, WINCY, 
			m_BitMap["Back"]->GetMemdc(),
			0, 0, SRCCOPY);
}

void CStage2::Release(void)
{	
}
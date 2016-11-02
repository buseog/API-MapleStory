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
	LoadMap();
	LoadBmp();
}

CStage1::~CStage1(void)
{
	Release();
}


void CStage1::Initialize(void)
{
	ParentClear();
	m_vecParent[PAR_PLAYER].back()->SetPos(0.f, 0.f);
	m_vecUI.push_back(CFactory<CUI>::CreateUI(WINCX / 2.f, WINCY / 2.f, "UI"));

	m_vecPortal.push_back(CFactory<CPortal>::CreateParent(100.f, 1140.f, "Portal"));
	((CPortal*)m_vecPortal.back())->SetPortal(1);

	m_vecPortal.push_back(CFactory<CPortal>::CreateParent(1650.f, 1140.f, "Portal"));
	((CPortal*)m_vecPortal.back())->SetPortal(3);

	((CPlayer*)m_vecParent[PAR_PLAYER].back())->SetMapSize(1773.f, 1464.f);

	CParent::SetBitMap(&m_BitMap);
	CUI::SetBitMap(&m_BitMap);
}

void CStage1::Progress(DWORD _delta)
{
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
		
		for (size_t i = 0; i < m_vecUI.size(); ++i)
		{
			m_vecUI[i]->Progress(_delta);
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

void CStage1::Render(HDC hdc)
{
	BitBlt(m_BitMap["Back"]->GetMemdc(), 
		0 + m_vecParent[PAR_PLAYER].back()->GetScroll().x,
		0 + m_vecParent[PAR_PLAYER].back()->GetScroll().y, 
			1773, 1464, 
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

	for (size_t i = 0; i < m_vecUI.size(); ++i)
	{
		m_vecUI[i]->Render(m_BitMap["Back"]->GetMemdc());
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

void CStage1::Release(void)
{
	
}
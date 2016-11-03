#include "StdAfx.h"
#include "BossField.h"
#include "Player.h"
#include "Monster.h"
#include "Factory.h"
#include "UI.h"
#include "Portal.h"
#include "CollisionMgr.h"

CBossField::CBossField(void)
{
	m_strKey = "BossField";

	m_vecPortal.push_back(CFactory<CPortal>::CreateParent(50.f, 900.f, "Portal"));
	((CPortal*)m_vecPortal.back())->SetPortal(1);

}

CBossField::~CBossField(void)
{
	Release();
}

void CBossField::Initialize(void)
{
	LoadMap();
	LoadBmp();


	((CPlayer*)m_vecParent[PAR_PLAYER].back())->SetMapSize(1372, 1200);

	CParent::SetBitMap(&m_BitMap);
	CUI::SetBitMap(&m_BitMap);

	m_vecParent[PAR_LOADING].push_back(CFactory<CLoading>::CreateParent());
}

void CBossField::Progress(DWORD _delta)
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

	if (GetAsyncKeyState(VK_UP))
		CCollisionMgr::CollisionPortal(&m_vecParent[PAR_PLAYER], &m_vecPortal);

	CCollisionMgr::CollisionPTile(&m_vecParent[PAR_PLAYER], &m_vecTile);
	CCollisionMgr::CollisionMTile(&m_vecParent[PAR_MONSTER], &m_vecTile);
	CCollisionMgr::CollisionSKill(&m_vecParent[PAR_SKILL], &m_vecParent[PAR_MONSTER]);
}

void CBossField::Render(HDC hdc)
{
	BitBlt(m_BitMap["Back"]->GetMemdc(), 
		0 + m_vecParent[PAR_PLAYER].back()->GetScroll().x,
		0 + m_vecParent[PAR_PLAYER].back()->GetScroll().y, 
			1372, 1200, 
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

void CBossField::Release(void)
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
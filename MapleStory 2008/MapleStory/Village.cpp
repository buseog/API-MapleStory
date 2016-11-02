#include "StdAfx.h"
#include "Village.h"
#include "Player.h"
#include "Monster.h"
#include "Factory.h"
#include "UI.h"
#include "Portal.h"
#include "CollisionMgr.h"
#include "Item.h"


CVillage::CVillage(void)
{
	m_strKey = "Village";
	LoadMap();
	LoadBmp();
	m_vecParent[PAR_PLAYER].push_back(CFactory<CPlayer>::CreateParent(.0f, 0.f));
}

CVillage::~CVillage(void)
{
	Release();
}

void CVillage::Initialize(void)
{
	ParentClear();
	m_vecUI.push_back(CFactory<CUI>::CreateUI(WINCX / 2.f, WINCY / 2.f, "UI"));

	m_vecPortal.push_back(CFactory<CPortal>::CreateParent(1800.f, 470.f, "Portal"));
	((CPortal*)m_vecPortal.back())->SetPortal(2);

	((CPlayer*)m_vecParent[PAR_PLAYER].back())->SetSkill(&m_vecParent[PAR_SKILL]);
	((CPlayer*)m_vecParent[PAR_PLAYER].back())->SetMapSize(1920.f, 680.f);

	for (int i = 0; i < 15; ++i)
	{
		m_vecParent[PAR_MONSTER].push_back(CFactory<CMonster>::CreateParent(rand() % 1900, rand()% 500, "PurpleMushRoom_LEFT"));
	}

	CParent::SetBitMap(&m_BitMap);
	CUI::SetBitMap(&m_BitMap);
	CItem::SetBitMap(&m_BitMap);
}

void CVillage::Progress(DWORD _delta)
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

void CVillage::Render(HDC hdc)
{
	BitBlt(m_BitMap["Back"]->GetMemdc(), 
		0 + m_vecParent[PAR_PLAYER].back()->GetScroll().x,
		0 + m_vecParent[PAR_PLAYER].back()->GetScroll().y, 
			1920, 680, 
			m_BitMap[m_strKey]->GetMemdc(),
			0, 0, SRCCOPY);

	for (size_t i = 0; i < PAR_END; ++i)
	{
		for (vector<CParent*>::iterator iter = m_vecParent[i].begin(); iter != m_vecParent[i].end(); ++iter)
		{
			(*iter)->Render(m_BitMap["Back"]->GetMemdc());
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

void CVillage::Release(void)
{
}
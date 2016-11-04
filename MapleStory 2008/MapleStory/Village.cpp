#include "StdAfx.h"
#include "Village.h"
#include "Player.h"
#include "Monster.h"
#include "Factory.h"
#include "Portal.h"
#include "CollisionMgr.h"
#include "Item.h"
#include "Npc.h"

CVillage::CVillage(void)
:m_pStore(NULL)
{
	m_strKey = "Village";
	LoadMap();
	LoadBmp();
	m_vecParent[PAR_PLAYER].push_back(CFactory<CPlayer>::CreateParent(50.0f, 300.f));

	m_vecUI[UI_UI].push_back(CFactory<CUI>::CreateUI(WINCX / 2.f, WINCY / 2.f, "UI"));
	m_vecUI[UI_UI].push_back(CFactory<CUI>::CreateUI(250, 560, "HPBar"));
	m_vecUI[UI_UI].push_back(CFactory<CUI>::CreateUI(420, 560, "MPBar"));
	m_vecUI[UI_UI].push_back(CFactory<CUI>::CreateUI(250, 575, "EXPBar"));
	m_bUIView[UI_UI] = true;
	m_vecUI[UI_INVENTORY].push_back(CFactory<CInventory>::CreateUI(600.f, 300.f));
	m_vecUI[UI_EQUIPMENT].push_back(CFactory<CEquipment>::CreateUI(500.f, 300.f));
	m_vecUI[UI_SKILLPANEL].push_back(CFactory<CSkillPanel>::CreateUI(600.f, 400.f));
	m_vecUI[UI_QUICKSLOT].push_back(CFactory<CQuickSlot>::CreateUI(730.f, 480.f));

	m_vecPortal.push_back(CFactory<CPortal>::CreateParent(1800.f, 470.f, "Portal"));
	((CPortal*)m_vecPortal.back())->SetPortal(2);

	m_pStore = CFactory<CNPC>::CreateParent();
}

CVillage::~CVillage(void)
{
	Release();
}

void CVillage::Initialize(void)
{
	ParentClear();
	
	((CPlayer*)m_vecParent[PAR_PLAYER].back())->SetSkill(&m_vecParent[PAR_SKILL]);
	((CPlayer*)m_vecParent[PAR_PLAYER].back())->SetMapSize(1920.f, 680.f);

	for (int i = 0; i < 15; ++i)
	{
		m_vecParent[PAR_MONSTER].push_back(CFactory<CMonster>::CreateParent(rand() % 1900, rand()% 500, "PurpleMushRoom_LEFT"));
	}

	m_pLoading = new CLoading();

	CParent::SetBitMap(&m_BitMap);
	CUI::SetBitMap(&m_BitMap);
	CItem::SetBitMap(&m_BitMap);

}

void CVillage::Progress(DWORD _delta)
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
	
	float fHp = m_vecParent[PAR_PLAYER].back()->GetStat().fHp / m_vecParent[PAR_PLAYER].back()->GetStat().fFullHp;
	float fExp = m_vecParent[PAR_PLAYER].back()->GetStat().fExp / 1000.f;

	for (size_t i = 0; i < UI_END; ++i)
	{
		if (m_bUIView[i])
		{
			for (vector<CUI*>::iterator iter = m_vecUI[i].begin(); iter != m_vecUI[i].end(); ++iter)
			{
				(*iter)->SetPercent(fHp, fExp);
				(*iter)->Progress(_delta);
			}
		}
	}

	for (size_t i = 0; i < m_vecPortal.size(); ++i)
	{
		m_vecPortal[i]->Progress(_delta);
	}

	for (size_t i = 0; i < m_vecItem.size(); ++i)
	{
		m_vecItem[i]->Progress(_delta);
	}

	if (m_pStore)
		m_pStore->Progress(_delta);

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
	CCollisionMgr::CollisionITile(&m_vecItem, &m_vecTile);
	CCollisionMgr::CollisionBodyButt(&m_vecParent[PAR_PLAYER], &m_vecParent[PAR_MONSTER]);
	m_vecParent[PAR_PLAYER].back()->SetExp(CCollisionMgr::CollisionSKill(&m_vecParent[PAR_SKILL], &m_vecParent[PAR_MONSTER]));

	if (m_vecParent[PAR_PLAYER].back()->GetStat().fExp >= 1000.f)
		m_vecParent[PAR_PLAYER].back()->SetLevel();
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

	for (size_t i = 0; i < m_vecPortal.size(); ++i)
	{
		m_vecPortal[i]->Render(m_BitMap["Back"]->GetMemdc());
	}

	for (size_t i = 0; i < UI_END; ++i)
	{
		if (m_bUIView[i])
		{
			for (vector<CUI*>::iterator iter = m_vecUI[i].begin(); iter != m_vecUI[i].end(); ++iter)
			{
				(*iter)->Render(m_BitMap["Back"]->GetMemdc());
			}
		}
	}
	
	for (size_t i = 0; i < m_vecItem.size(); ++i)
	{
		m_vecItem[i]->Render(m_BitMap["Back"]->GetMemdc());
	}

	if (m_pStore)
		m_pStore->Render(m_BitMap["Back"]->GetMemdc());

	if (m_pLoading)
		m_pLoading->Render(m_BitMap["Back"]->GetMemdc());

	BitBlt(hdc, 
			0, 0, 
			WINCX, WINCY, 
			m_BitMap["Back"]->GetMemdc(),
			0, 0, SRCCOPY);
}

void CVillage::Release(void)
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

	for (int i = 0; i < PAR_END; ++i)
	{
		for (vector<CParent*>::iterator iter = m_vecParent[i].begin(); iter != m_vecParent[i].end(); ++iter)
		{
			::Safe_Delete(*iter);
		}
		m_vecParent[i].clear();
	}

	for (int i = 0; i < UI_END; ++i)
	{
		for (vector<CUI*>::iterator iter = m_vecUI[i].begin(); iter != m_vecUI[i].end(); ++iter)
		{
		::Safe_Delete(*iter);
		}
		m_vecUI[i].clear();
	}

	for (size_t i = 0; i < m_vecPortal.size(); ++i)
	{
		::Safe_Delete(m_vecPortal[i]);
	}
	m_vecPortal.clear();
	
}
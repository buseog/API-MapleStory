#include "StdAfx.h"
#include "Village.h"
#include "Player.h"
#include "Monster.h"
#include "Factory.h"
#include "Portal.h"
#include "CollisionMgr.h"
#include "RenderMgr.h"
#include "Item.h"
#include "Npc.h"
#include "SkillEffect.h"

CVillage::CVillage(void)
:m_pStoreNPC(NULL)
{
	m_strKey = "Village";
	LoadMap();
	LoadBmp();

	m_pStoreNPC = new CNPC("Store_NPC");
	m_pStoreNPC->Initialize();

	m_pQuestNPC = new CNPC("Quest_Npc");
	m_pQuestNPC->Initialize();

	m_vecUI[UI_MAIN].push_back(CFactory<CUI>::CreateUI(WINCX / 2.f, WINCY / 2.f, "UI"));
	m_vecUI[UI_MAIN].push_back(CFactory<CUI>::CreateUI(250, 560, "HPBar"));
	m_vecUI[UI_MAIN].push_back(CFactory<CUI>::CreateUI(420, 560, "MPBar"));
	m_vecUI[UI_MAIN].push_back(CFactory<CUI>::CreateUI(250, 576, "EXPBar"));

	m_vecUI[UI_INVENTORY].push_back(CFactory<CInventory>::CreateUI(600.f, 300.f));
	m_vecUI[UI_EQUIPMENT].push_back(CFactory<CEquipment>::CreateUI(500.f, 300.f));
	m_vecUI[UI_SKILLPANEL].push_back(CFactory<CSkillPanel>::CreateUI(500.f, 350.f));
	m_vecUI[UI_QUICKSLOT].push_back(CFactory<CQuickSlot>::CreateUI(730.f, 490.f));
	m_vecUI[UI_STATUS].push_back(CFactory<CStatus>::CreateUI(400.f, 450.f));

	m_vecUI[UI_STATUS].back()->SetPlayer(m_vecParent[PAR_PLAYER].back());
	m_vecUI[UI_INVENTORY].back()->SetPlayer(m_vecParent[PAR_PLAYER].back());
	m_vecUI[UI_EQUIPMENT].back()->SetPlayer(m_vecParent[PAR_PLAYER].back());

	m_vecPortal.push_back(CFactory<CPortal>::CreateParent(1800.f, 470.f, "Portal"));
	((CPortal*)m_vecPortal.back())->SetPortal(2);

	m_pStoreNPC->SetInventory(m_vecUI[UI_INVENTORY].back());
	m_pQuestNPC->SetInventory(m_vecUI[UI_INVENTORY].back());
	((CQuickSlot*)m_vecUI[UI_QUICKSLOT].back())->SetPanel(m_vecUI[UI_SKILLPANEL].back());
	((CPlayer*)m_vecParent[PAR_PLAYER].back())->SetQuickSlot(m_vecUI[UI_QUICKSLOT].back());

	CDevice::GetInstance()->SoundStop(0);
	CDevice::GetInstance()->SoundPlay(1, 1);
}

CVillage::~CVillage(void)
{
	Release();
}

void CVillage::Initialize(void)
{
	ParentClear();
	
	((CPlayer*)m_vecParent[PAR_PLAYER].back())->SetSkill(&m_vecParent[PAR_SKILL]);
	m_vecParent[PAR_PLAYER].back()->SetMapSize(1920.f, 680.f);

	m_pLoading = new CLoading();

	CParent::SetBitMap(&m_BitMap);
	CUI::SetBitMap(&m_BitMap);
	CItem::SetBitMap(&m_BitMap);

}

void CVillage::Progress(DWORD _delta)
{
	KeyInput();
	UIDrag();

	if(GetAsyncKeyState(VK_SPACE))
		CDevice::GetInstance()->SoundStop(1);

	if (m_pStoreNPC)
		m_pStoreNPC->Progress(_delta);

	if (m_pQuestNPC)
		m_pQuestNPC->Progress(_delta);

	for (size_t i = 0; i < PAR_END; ++i)
	{
		for (vector<CParent*>::iterator iter = m_vecParent[i].begin(); iter != m_vecParent[i].end();)
		{
			(*iter)->Progress(_delta);

			if ((*iter)->GetDestroy())
			{
				if (i == PAR_MONSTER)
					if(((CMonster*)(*iter))->GetDrop())
						m_vecItem.push_back(((CMonster*)(*iter))->GetDropItem());
						

				::Safe_Delete(*iter);
				iter = m_vecParent[i].erase(iter);

				if (iter == m_vecParent[i].end())
					break;
			}
			else
				++iter;
		}
	}

	for (size_t i = 0; i < m_vecPortal.size(); ++i)
	{
		m_vecPortal[i]->Progress(_delta);
	}

	CRenderMgr::GetInstance()->UIClear();

	for (int i = 0; i < UI_END; ++i)
	{
		for (vector<CUI*>::iterator iter = m_vecUI[i].begin(); iter != m_vecUI[i].end(); ++iter)
		{
			if ((*iter)->GetOnOff())
			{
				(*iter)->Progress(_delta);
				CRenderMgr::GetInstance()->AddUI(*iter);
			}
		}
	}

	for (size_t i = 0; i < m_vecItem.size(); ++i)
	{
		m_vecItem[i]->Progress(_delta);
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
	CCollisionMgr::CollisionITile(&m_vecItem, &m_vecTile);
	CCollisionMgr::CollisionBodyButt(&m_vecParent[PAR_PLAYER], &m_vecParent[PAR_MONSTER]);
	m_vecParent[PAR_PLAYER].back()->SetExp(CCollisionMgr::CollisionSKill(&m_vecParent[PAR_SKILL], &m_vecParent[PAR_MONSTER]));

	if (m_vecParent[PAR_PLAYER].back()->GetStat().fExp >= (800.f * m_vecParent[PAR_PLAYER].back()->GetStat().iLevel))
	{
		m_vecParent[PAR_PLAYER].back()->SetLevel();
		m_vecParent[PAR_EFFECT].push_back(CFactory<CSkillEffect>::CreateParent(m_vecParent[PAR_PLAYER].back()->GetInfo().fX, m_vecParent[PAR_PLAYER].back()->GetInfo().fY - 150, "LevelUpEFFECT"));
	}
}

void CVillage::Render(HDC hdc)
{
	BitBlt(m_BitMap["Back"]->GetMemdc(), 
		0 + m_vecParent[PAR_PLAYER].back()->GetScroll().x,
		0 + m_vecParent[PAR_PLAYER].back()->GetScroll().y, 
			1920, 680, 
			m_BitMap[m_strKey]->GetMemdc(),
			0, 0, SRCCOPY);

	if (m_pStoreNPC)
		m_pStoreNPC->Render(m_BitMap["Back"]->GetMemdc());

	if (m_pQuestNPC)
		m_pQuestNPC->Render(m_BitMap["Back"]->GetMemdc());

	for (size_t i = 0; i < m_vecPortal.size(); ++i)
	{
		m_vecPortal[i]->Render(m_BitMap["Back"]->GetMemdc());
	}

	for (int i = 0; i < PAR_END; ++i)
	{
		for (vector<CParent*>::iterator iter = m_vecParent[i].begin(); iter != m_vecParent[i].end(); ++iter)
		{
			(*iter)->Render(m_BitMap["Back"]->GetMemdc());
		}
	}

	for (size_t i = 0; i < m_vecItem.size(); ++i)
	{
		m_vecItem[i]->Render(m_BitMap["Back"]->GetMemdc());
	}

	CRenderMgr::GetInstance()->RenderUI(m_BitMap["Back"]->GetMemdc());

	if (m_pLoading)
		m_pLoading->Render(m_BitMap["Back"]->GetMemdc());

	++m_iFPS;

	if(m_dwTime + 1000 < GetTickCount())
	{
		m_dwTime = GetTickCount();
		wsprintf(m_szFPS, L"FPS : %d", m_iFPS);
		m_iFPS = 0;
	}
		SetWindowText(g_hWnd, m_szFPS);

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

	for (size_t i = 0; i < m_vecItem.size(); ++i)
	{
		::Safe_Delete(m_vecItem[i]);
	}
	m_vecItem.clear();

	::Safe_Delete(m_pLoading);
	::Safe_Delete(m_pQuestNPC);
	::Safe_Delete(m_pStoreNPC);
}
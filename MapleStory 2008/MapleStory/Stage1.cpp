#include "StdAfx.h"
#include "Stage1.h"
#include "Player.h"
#include "Monster.h"
#include "Factory.h"
#include "UI.h"
#include "Portal.h"
#include "CollisionMgr.h"
#include "RenderMgr.h"
#include "Item.h"
#include "SkillEffect.h"

CStage1::CStage1(void)
{
	m_strKey = "Stage1";
	LoadMap();
	LoadBmp();

	m_vecPortal.push_back(CFactory<CPortal>::CreateParent(50.f, 1140.f, "Portal"));
	((CPortal*)m_vecPortal.back())->SetPortal(1);

	m_vecPortal.push_back(CFactory<CPortal>::CreateParent(1650.f, 1140.f, "Portal"));
	((CPortal*)m_vecPortal.back())->SetPortal(3);
}

CStage1::~CStage1(void)
{
	Release();
}


void CStage1::Initialize(void)
{
	ParentClear();
	m_fRegenTime = 7000.f;
	((CPlayer*)m_vecParent[PAR_PLAYER].back())->SetMapSize(1773.f, 1464.f);

	CParent::SetBitMap(&m_BitMap);
	CUI::SetBitMap(&m_BitMap);

	m_pLoading = new CLoading();


	for (int i = 0; i < 9; ++i)
	{
		CDevice::GetInstance()->SoundStop(i);
	}
	CDevice::GetInstance()->SoundPlay(2, 1);
}

void CStage1::Progress(DWORD _delta)
{
	KeyInput();
	UIDrag();

	
	if(GetAsyncKeyState(VK_SPACE))
		CDevice::GetInstance()->SoundStop(2);

	if ((m_fRegenTime -= _delta) <= 0)
	{
		Regen();
		m_fRegenTime = 7000 + float(rand() % 2000);
	}

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
		if (m_vecUI[i].back()->GetOnOff())
		{
			for (vector<CUI*>::iterator iter = m_vecUI[i].begin(); iter != m_vecUI[i].end(); ++iter)
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

void CStage1::Render(HDC hdc)
{
	BitBlt(m_BitMap["Back"]->GetMemdc(), 
		0 + m_vecParent[PAR_PLAYER].back()->GetScroll().x,
		0 + m_vecParent[PAR_PLAYER].back()->GetScroll().y, 
			1773, 1464, 
			m_BitMap[m_strKey]->GetMemdc(),
			0, 0, SRCCOPY);

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

void CStage1::Release(void)
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


	for (size_t i = 0; i < m_vecItem.size(); ++i)
	{
		::Safe_Delete(m_vecItem[i]);
	}
	m_vecItem.clear();

	for (size_t i = 0; i < m_vecParent[PAR_MONSTER].size(); ++i)
	{
		::Safe_Delete(m_vecParent[PAR_MONSTER][i]);		
	}
	m_vecParent[PAR_MONSTER].clear();

	::Safe_Delete(m_pLoading);
}

void CStage1::Regen(void)
{
	int Regen = 20 - m_vecParent[PAR_MONSTER].size();

	for (int i = 0; i < Regen; ++i)
	{
		int iRandom = rand() % 5 + 1;

		switch (iRandom)
		{
		case 1:
			m_vecParent[PAR_MONSTER].push_back(CFactory<CMonster>::CreateParent(float(rand() % 700 + 500), 1230.f, "BlueMushRoom_RIGHT"));
			break;

		case 2:
			m_vecParent[PAR_MONSTER].push_back(CFactory<CMonster>::CreateParent(float(rand() % 700 + 700), 980.f, "GreenMushRoom_RIGHT"));
			break;

		case 3:
			m_vecParent[PAR_MONSTER].push_back(CFactory<CMonster>::CreateParent(float(rand() % 700 + 700), 730.f, "BlueMushRoom_RIGHT"));
			break;

		case 4:
			m_vecParent[PAR_MONSTER].push_back(CFactory<CMonster>::CreateParent(float(rand() % 600 + 700), 500.f, "BlueMushRoom_RIGHT"));
			break;

		case 5:
			m_vecParent[PAR_MONSTER].push_back(CFactory<CMonster>::CreateParent(float(rand() % 600 + 700), 255.f, "GreenMushRoom_RIGHT"));
			break;
		}
	}
}
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
}

CBossField::~CBossField(void)
{
	Release();
}

void CBossField::Initialize(void)
{
	LoadMap();
	LoadBmp();

	m_vecParent[OBJ_PLAYER].back()->SetPos(100.f, 100.f);
	m_vecUI.push_back(CFactory<CUI>::CreateUI(WINCX / 2.f, WINCY / 2.f, "UI"));

	((CPlayer*)m_vecParent[OBJ_PLAYER].back())->SetMapSize(1372, 1200);

}

void CBossField::Progress(DWORD _delta)
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

void CBossField::Render(HDC hdc)
{
	BitBlt(m_BitMap["Back"]->GetMemdc(), 
		0 + m_vecParent[OBJ_PLAYER].back()->GetScroll().x,
		0 + m_vecParent[OBJ_PLAYER].back()->GetScroll().y, 
			1372, 1200, 
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

void CBossField::Release(void)
{
}
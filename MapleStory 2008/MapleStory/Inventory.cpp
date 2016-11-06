#include "StdAfx.h"
#include "Inventory.h"
#include "SceneMgr.h"
#include "Factory.h"
#include "ItemEmpty.h"
#include "Potion.h"

CInventory::CInventory(void)
{
}

CInventory::CInventory(string _strKey)
{
}

CInventory::~CInventory(void)
{
	Release();
}

void CInventory::Initialize(void)
{
	m_bOnOff = false;
	m_dwTime = GetTickCount();
	m_pPick = NULL;
	m_pDrop = NULL;
	m_vecItem.reserve(INVENSIZE);
	m_vecItem.resize(INVENSIZE);
	m_ReturnItem = NULL;
	m_iSwap = 100;
	m_strKey = "Inventory";
	m_tInfo = INFO(0, 0, 172.f, 335.f);

	m_pCloseButton = CFactory<CUI>::CreateUI(0.f, 0.f, "Close");
}

void CInventory::Progress(DWORD _delta)
{
	ItemPos();

	for (size_t i = 0; i < m_vecItem.size(); ++i)
	{
		if (m_vecItem[i])
		{
			m_vecItem[i]->Progress(_delta);
		}
		else
			m_vecItem[i] = new CItemEmpty();
	}

	if (m_pPick)
		m_pPick->SetPos((float)GetMouse().x, (float)GetMouse().y);
}

void CInventory::Render(HDC hdc)
{
	BitBlt(hdc,
		int(m_tInfo.fX - m_tInfo.fCX / 2.f),
		int(m_tInfo.fY - m_tInfo.fCY / 2.f),
		int(m_tInfo.fCX),
		int(m_tInfo.fCY),
		(*m_pBitMap)[m_strKey]->GetMemdc(),
		0,
		0,
		SRCCOPY);

	for (size_t i = 0; i < m_vecItem.size(); ++i)
	{
		if (m_vecItem[i])
			m_vecItem[i]->Render(hdc);
	}

	SetBkMode((*m_pBitMap)["Back"]->GetMemdc(),TRANSPARENT);

	TCHAR szGold[128] = L"";
	wsprintf(szGold, L"%d", (int)m_pPlayer->GetStat().iGold);
					TextOut(hdc, int(m_tInfo.fX - 5), int(m_tInfo.fY + 97), szGold, lstrlen(szGold));

	

	m_pCloseButton->Render(hdc);

	if (m_pPick)
		m_pPick->Render(hdc);
}

void CInventory::Release(void)
{
	for (size_t i = 0; i < m_vecItem.size(); ++i)
	{
		::Safe_Delete(m_vecItem[i]);
	}
	m_vecItem.clear();
}

void CInventory::AddItem(CItem*	_pItem)
{
	if (_pItem->GetItem().iType == IT_POTION)
	{
		for (size_t i = 0; i < m_vecItem.size();)
		{
			if (m_vecItem[i]->GetItem().iType == IT_POTION && m_vecItem[i]->GetItem().iCount < 10)
			{
				((CPotion*)m_vecItem[i])->SetCount(_pItem->GetItem().iCount);
				::Safe_Delete(_pItem);
				return;
			}
			else
				++i;
		}
	}

	for (size_t i = 0; i < m_vecItem.size(); ++i)
	{
		if (m_vecItem[i]->GetItem().iType == IT_EMPTY)
		{
			::Safe_Delete(m_vecItem[i]);
			m_vecItem[i] = _pItem;
			break;
		}
	}
	
}

void CInventory::ItemPos(void)
{
	float fItemX = m_tInfo.fX - 60;
	float fItemY = m_tInfo.fY - 100;

	int iCount = 0;

	for (vector<CItem*>::iterator iter = m_vecItem.begin(); iter != m_vecItem.end(); ++iter)
	{
		int iX = iCount / 4;
		int iY = iCount - (iX * 4);

		if (*iter != NULL)
		{
			(*iter)->SetPos(fItemX + (35 * iY), fItemY + (35 * iX));
		}

		++iCount;
	}

	float fCloseX = m_tInfo.fX + m_tInfo.fCX / 2.f - 17.f;
	float fCloseY = m_tInfo.fY - m_tInfo.fCY / 2.f + 12.f;

	m_pCloseButton->SetPos(fCloseX, fCloseY);
}

RECT CInventory::GetRect(void)
{ 
	RECT	rc = {

		int(m_tInfo.fX - m_tInfo.fCX / 2.f),
		int(m_tInfo.fY - m_tInfo.fCY / 2.f),
		int(m_tInfo.fX + m_tInfo.fCX / 2.f),
		int(m_tInfo.fY - m_tInfo.fCY / 2.f + 20)
	};

	return rc;
}

void CInventory::UIPicking(void)
{
	if (PtInRect(&m_pCloseButton->GetRect(), GetMouse()))
	{
		if (GetAsyncKeyState(VK_LBUTTON))
			m_bOnOff = false;
	}

	if (m_pPick)
	{
		if (GetAsyncKeyState(VK_LBUTTON))
		{
			 if (!(GetMouse().x > m_tInfo.fX - m_tInfo.fCX / 2 &&
				 GetMouse().y > m_tInfo.fY - m_tInfo.fCY / 2 &&
				 GetMouse().x < m_tInfo.fX + m_tInfo.fCX / 2 &&
				 GetMouse().y < m_tInfo.fY + m_tInfo.fCY / 2))
			 {
				m_pDrop = m_pPick;
				m_pPick->SetDrawID(0);
				m_pPick->SetDropID(1);
				m_pPick = NULL;
			 }
		}
	}


	for(size_t i = 0; i < m_vecItem.size(); ++i)
	{
		if (m_vecItem[i])
		{
			if(PtInRect(&m_vecItem[i]->GetRect(), GetMouse()))
			{
				if (m_dwTime + 80 <= GetTickCount())
				{
					if (GetAsyncKeyState(VK_RBUTTON) & 0x0001)
					{
						if (m_vecItem[i]->GetItem().iType == IT_POTION)
						{
							((CPotion*)m_vecItem[i])->SetPotion();
							m_ReturnItem = new CPotion(L"HPPotion", 1000, 1, 1, IT_POTION);
							m_vecItem[i]->SetDrawID(0);

							if (m_vecItem[i]->GetItem().iCount <= 0)
							{
								m_vecItem[i] = new CItemEmpty();
							}
						}
						else
						{
							m_ReturnItem = m_vecItem[i];
							m_vecItem[i]->SetDrawID(0);
							m_vecItem[i] = new CItemEmpty();
						}
					}

					if (GetAsyncKeyState(VK_LBUTTON))
					{
						if (m_pPick == NULL)
						{
							m_pPick = m_vecItem[i];
							m_vecItem[i] = new CItemEmpty();
							m_iSwap = i;
						}
						else
						{
							m_vecItem[m_iSwap] = m_vecItem[i];
							m_vecItem[i] = m_pPick;
							m_pPick = NULL;
						}
					}
					m_dwTime = GetTickCount();
				}
			}
		}
	}
}

void CInventory::SetDropItem(void)
{
	m_pDrop = NULL;
}

CItem* CInventory::GetDropItem(void)
{
	return m_pDrop;
}
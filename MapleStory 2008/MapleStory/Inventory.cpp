#include "StdAfx.h"
#include "Inventory.h"

CInventory::CInventory(void)
{
}

CInventory::CInventory(string _strKey)
{
}

CInventory::~CInventory(void)
{
}

void CInventory::Initialize(void)
{
	m_iSwap = 100;
	m_strKey = "Inventory";
	m_tInfo = INFO(0, 0, 172.f, 335.f);
	m_vecItem.reserve(24);
}

void CInventory::Progress(DWORD _delta)
{
	for(size_t i = 0; i < m_vecItem.size(); ++i)
	{
		m_vecItem[i]->Progress(_delta);

		if(PtInRect(&m_vecItem[i]->GetRect(), GetMouse()))
		{
			if (GetAsyncKeyState(VK_LBUTTON))
			{
				if (m_iSwap == 100)
				{
					m_iSwap = i;
					return;
				}

				else
				{
					swap(m_vecItem[m_iSwap], m_vecItem[i]);
					m_iSwap = 100;
					return;
				}
			}
			if (GetAsyncKeyState(VK_RBUTTON))
			{
				m_vecItem.erase(m_vecItem.begin() + i);
				return;
			}
		}
	}

	ItemPos();
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
		m_vecItem[i]->Render(hdc);
	}
}

void CInventory::Release(void)
{
	
}

void CInventory::AddItem(CItem*	_pItem)
{
	if (m_vecItem.size() < 24)
	{	
		m_vecItem.push_back(_pItem);
	}
	
	else
		return;
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
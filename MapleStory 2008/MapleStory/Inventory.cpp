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
	Release();
}

void CInventory::Initialize(void)
{
	m_dwTime = GetTickCount();
	m_pPick = NULL;
	m_vecItem.reserve(INVENSIZE);
	m_vecItem.resize(INVENSIZE);
	m_ReturnItem = NULL;
	m_iSwap = 100;
	m_strKey = "Inventory";
	m_tInfo = INFO(0, 0, 172.f, 335.f);
	m_vecItem.reserve(24);
}

void CInventory::Progress(DWORD _delta)
{
	ItemPos();

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

	if (m_pPick)
		m_pPick->Render(hdc);
}

void CInventory::Release(void)
{
	for (size_t i = 0; i < m_vecItem.size(); ++i)
	{
		if (m_vecItem[i] == NULL)
		{
			::Safe_Delete(m_vecItem[i]);
		}
	}
	m_vecItem.clear();
}

void CInventory::AddItem(CItem*	_pItem)
{
	for (size_t i = 0; i < m_vecItem.size(); ++i)
	{
		if (m_vecItem[i] == NULL)
		{
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
						m_ReturnItem = m_vecItem[i];
						m_vecItem[i] = NULL;
					}


					if (GetAsyncKeyState(VK_LBUTTON))
					{
						if (m_pPick == NULL)
						{
							m_pPick = m_vecItem[i];
							m_vecItem[i] = NULL;
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
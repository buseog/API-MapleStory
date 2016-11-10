#include "StdAfx.h"
#include "Store.h"
#include "Factory.h"
#include "Inventory.h"
#include "Weapon.h"
#include "Armor.h"
#include "Potion.h"

CStore::CStore(void)
{
}

CStore::CStore(string _strKey)
{
	m_strKey = _strKey;
	m_pInventory = NULL;
}

CStore::~CStore(void)
{
	Release();
}

void	CStore::Initialize(void)
{
	m_bOnOff = false;
	m_tInfo = INFO(300.f, 200.f, 271.f, 500.f);
	m_dwTime = GetTickCount();

	m_pCloseButton = CFactory<CUI>::CreateUI(0.f, 0.f, "Close");

	m_vecItemList.push_back(new CWeapon(L"Weapon", 100, 1, 5000, IT_WEAPON));
	m_vecItemList.push_back(new CArmor(L"Armor", 50, 1, 5000, IT_ARMOR));
	m_vecItemList.push_back(new CArmor(L"Armor2", 100, 1, 1000, IT_ARMOR));
	m_vecItemList.push_back(new CPotion(L"HPPotion", 100, 1, 500, IT_POTION));
}

void	CStore::Progress(DWORD _dwDelta)
{
	if (m_dwTime + 100 <= GetTickCount())
	{
		UIPicking();
		m_dwTime = GetTickCount();
	}

	float fCloseX = m_tInfo.fX + m_tInfo.fCX / 2.f - 17;
	float fCloseY = m_tInfo.fY - m_tInfo.fCY / 2.f + 17;

	for (size_t i = 0; i < m_vecItemList.size(); ++i)
	{
		m_vecItemList[i]->SetPos(m_tInfo.fX - 110, m_tInfo.fY - 110 + (40 * i));
		m_vecItemList[i]->Progress(_dwDelta);
	}

	if (m_bOnOff)
	{
		((CInventory*)m_pInventory)->SellStore();
		m_pCloseButton->SetPos(fCloseX, fCloseY);
	}
}

void	CStore::Render(HDC hdc)
{
	BitBlt(hdc, 
	int(m_tInfo.fX - m_tInfo.fCX / 2.f), 
	int(m_tInfo.fY - m_tInfo.fCY / 2.f), 
	int(m_tInfo.fCX), 
	int(m_tInfo.fCY), 
	(*m_pBitMap)[m_strKey]->GetMemdc(), 
	0, 0, SRCCOPY);

	TCHAR szString[128] = L"";

	for (size_t i = 0; i < m_vecItemList.size(); ++i)
	{
		m_vecItemList[i]->Render(hdc);
	}

	if (m_bOnOff)
	{
		m_pCloseButton->Render(hdc);
	}
}

void	CStore::Release(void)
{
	for(size_t i = 0; i < m_vecItemList.size(); ++i)
	{
		::Safe_Delete(m_vecItemList[i]);
	}
	m_vecItemList.clear();

	m_pInventory = NULL;
	::Safe_Delete(m_pCloseButton);
}

RECT CStore::GetRect(void)
{
	RECT	rc = {
		int(m_tInfo.fX - m_tInfo.fCX / 2.f),
		int(m_tInfo.fY - m_tInfo.fCY / 2.f),
		int(m_tInfo.fX + m_tInfo.fCX / 2.f),
		int(m_tInfo.fY - m_tInfo.fCY / 2.f + 20)
	};

	return rc;
}

void CStore::UIPicking(void)
{
	if (PtInRect(&m_pCloseButton->GetRect(), GetMouse()))
	{
		if (GetAsyncKeyState(VK_LBUTTON))
		{
			m_bOnOff = false;
		}
	}
	
	for (size_t i = 0; i < m_vecItemList.size(); ++i)
	{
		if (PtInRect(&m_vecItemList[i]->GetRect(), GetMouse()))
		{
			if (GetAsyncKeyState(VK_RBUTTON) & 0x8000)
			{
				if (m_pPlayer->GetStat().iGold >= m_vecItemList[i]->GetItem().iPrice)
				{
					((CPlayer*)m_pPlayer)->BuyItem(m_vecItemList[i]->GetItem().iPrice);

					if (m_vecItemList[i]->GetItem().iType == IT_WEAPON)
					{
						CItem* pBuyItem = new CWeapon(*m_vecItemList[i]);
						((CInventory*)m_pInventory)->AddItem(pBuyItem);
					}
					else if (m_vecItemList[i]->GetItem().iType == IT_ARMOR)
					{
						CItem* pBuyItem = new CArmor(*m_vecItemList[i]);
						((CInventory*)m_pInventory)->AddItem(pBuyItem);
					}
					else if (m_vecItemList[i]->GetItem().iType == IT_POTION)
					{
						CItem* pBuyItem = new CPotion(*m_vecItemList[i]);
						((CInventory*)m_pInventory)->AddItem(pBuyItem);
					}
				}
			}
		}
	}
}

void CStore::SetInventory(CUI*	_pInventory)
{
	m_pInventory = _pInventory;
}
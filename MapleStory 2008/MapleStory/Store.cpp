#include "StdAfx.h"
#include "Store.h"
#include "Factory.h"

CStore::CStore(void)
{
}

CStore::CStore(string _strKey)
{
	m_strKey = _strKey;
}
CStore::~CStore(void)
{
	Release();
}

void	CStore::Initialize(void)
{
	m_bDrag = false;
	m_tInfo = INFO(WINCX / 2.f, WINCY / 2.f, 500.f, 500.f);
	m_bOnOff = false;

	m_pCloseButton = CFactory<CUI>::CreateUI(0.f, 0.f, "Close");

	m_vecItemList.push_back(new CWeapon(L"Weapon", 100, 1, 5000, IT_WEAPON));

	m_vecItemList.push_back(new CWeapon(L"Armor", 50, 1, 5000, IT_ARMOR));
	m_vecItemList.push_back(new CWeapon(L"Armor2", 100, 1, 1000, IT_ARMOR));

	/*m_vecItemList[IT_WEAPON].push_back(new CWeapon(L"Weapon", 100, 1, 5000, IT_WEAPON));
	m_vecItemList[IT_WEAPON].push_back(new CWeapon(L"Weapon", 100, 1, 5000, IT_WEAPON));*/
}

void	CStore::Progress(DWORD _dwDelta)
{
	UIPicking();

	float fCloseX = m_tInfo.fX + m_tInfo.fCX / 2.f - 17;
	float fCloseY = m_tInfo.fY - m_tInfo.fCY / 2.f + 17;

	for (size_t i = 0; i < m_vecItemList.size(); ++i)
	{
		m_vecItemList[i]->SetPos(m_tInfo.fX - 220, m_tInfo.fY - 110 + (35 * i));
	}


	m_pCloseButton->SetPos(fCloseX, fCloseY);
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


	for (size_t i = 0; i < m_vecItemList.size(); ++i)
	{
		m_vecItemList[i]->Render(hdc);
	}

	m_pCloseButton->Render(hdc);
}

void	CStore::Release(void)
{
	for(size_t i = 0; i < m_vecItemList.size(); ++i)
	{
		::Safe_Delete(m_vecItemList[i]);
	}
	m_vecItemList.clear();

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
	float fX = float(GetMouse().x - m_prevPT.x);
	float fY = float(GetMouse().y - m_prevPT.y);

	if (PtInRect(&m_pCloseButton->GetRect(), GetMouse()))
	{
		if (GetAsyncKeyState(VK_LBUTTON))
			m_bOnOff = false;
	}

	if(m_bDrag)
	{
		m_tInfo.fX += fX;
		m_tInfo.fY += fY;
	}


	
	if (GetAsyncKeyState(VK_LBUTTON))
	{
		if(PtInRect(&GetRect(), GetMouse()))
		{
			m_prevPT = GetMouse();
			m_bDrag = true;
		}
	}
	else
	{
		m_bDrag = false;
	}

}
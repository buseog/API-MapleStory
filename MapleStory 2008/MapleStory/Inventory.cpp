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
	m_bMouse = false;
	m_strKey = "Inventory";
	m_tInfo = INFO(0, 0, 172.f, 335.f);
}

void CInventory::Progress(DWORD _delta)
{
	float fX = float(GetMouse().x - m_prevPT.x);
	float fY = float(GetMouse().y - m_prevPT.y);
	
	if(m_bMouse)
	{
		m_tInfo.fX += fX;
		m_tInfo.fY += fY;

		float fItemX = m_tInfo.fX - 60;
		float fItemY = m_tInfo.fY - 100;

		for (size_t i = 0; i < m_vecItem.size(); i += 4;)
		{
			m_vecItem[i]->SetPos(m_vecItem[i]->GetInfo().fX + fX, m_vecItem[i]->GetInfo().fY + fY);
		}
	}

	if(PtInRect(&GetRect(), GetMouse()))
	{
		if(GetAsyncKeyState(VK_LBUTTON))
		{
			m_prevPT = GetMouse();
			m_bMouse = true;
		}
		else
			m_bMouse = false;
	}
	else
		m_bMouse = false;

	
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
	if (m_vecItem.size() < 23)
		m_vecItem.push_back(_pItem);

	else
		return;
}

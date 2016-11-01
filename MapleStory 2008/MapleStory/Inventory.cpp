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
	m_tInfo = INFO(0, 0, 172.f, 335.f);
	m_tSprite = SPRITE(0, 0, 0, 0);
}

void CInventory::Progress(DWORD _delta)
{

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
}

void CInventory::Release(void)
{
	
}
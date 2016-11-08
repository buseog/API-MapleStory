#include "StdAfx.h"
#include "Pet.h"

CPet::CPet(void)
{
}

CPet::~CPet(void)
{
	Release();
}


void CPet::Initialize(void)
{
	m_strKey = "Pet";
	m_tInfo = INFO(0, 0, 100.f, 80.f);
	m_tStat = STAT(100.f, 100.f, 200.f, 0.f, 1, 0.f, 4.f, 1000);
	m_tSprite = SPRITE(0, 4, 0, 90);
	m_dwTime = GetTickCount();
	m_dwState = ST_STAND;
	m_dwKey = 0;
}

void CPet::Progress(DWORD _delta)
{
	if (m_dwTime + m_tSprite.dwTime < GetTickCount())
	{
		m_dwTime = GetTickCount();

		++m_tSprite.iStart;
	}

	if (m_tSprite.iStart >= m_tSprite.iLast)
	{
		m_tSprite.iStart = 0;
	}
}

void CPet::Render(HDC hdc)
{
	TransparentBlt(hdc,
		int(m_tInfo.fX - m_tInfo.fCX / 2.f + m_ptScroll.x),
		int(m_tInfo.fY - m_tInfo.fCY / 2.f + m_ptScroll.y),
		int(m_tInfo.fCX), 
		int(m_tInfo.fCY), 
		(*m_pBitMap)[m_strKey]->GetMemdc(),
		int(m_tInfo.fCX * m_tSprite.iStart), 
		int(m_tInfo.fCY * m_tSprite.iMotion),
		(int)m_tInfo.fCX, 
		(int)m_tInfo.fCY, 
		RGB(255, 255, 250));
}

void CPet::Release(void)
{
	
}
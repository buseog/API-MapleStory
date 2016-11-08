#include "StdAfx.h"
#include "Boss.h"

CBoss::CBoss(void)
{
}

CBoss::~CBoss(void)
{
}

void CBoss::Initialize(void)
{
	m_cTimer.TimeSetting();

	if (m_strKey == "GreenMushRoom_LEFT" || m_strKey == "GreenMushRoom_RIGHT")
	{
		m_tInfo = INFO(0, 0, 60.f, 60.f);
		m_tStat = STAT(1500.f, 1500.f, 500.f, 0.f, 1, 50.f, 2.f, 500);
		m_tSprite = SPRITE(0, 4, 1, 80);
	}

	m_dwTime = GetTickCount();
	m_dwKey = 0;
}
void CBoss::Progress(DWORD _delta)
{
	if (m_dwTime + m_tSprite.dwTime < GetTickCount())
	{
		m_dwTime = GetTickCount();

		++m_tSprite.iStart;
	}

	if (m_tSprite.iStart >= m_tSprite.iLast)
	{
 		if (m_dwState != ST_STAND)
			m_dwState = ST_STAND;

		m_tSprite.iStart = 0;
	}

}
void CBoss::Render(HDC hdc)
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
void CBoss::Release(void)
{

}

void CBoss::SetState(DWORD _dwState, int _iLast, int _iMotion, DWORD _dwTime)
{
	if (m_dwState & _dwState)
	{
		if (m_tSprite.iMotion != _iMotion)
			m_tSprite.iStart = 0;

		m_tSprite.iLast = _iLast;
		m_tSprite.iMotion = _iMotion;
		m_tSprite.dwTime = _dwTime;
	}
}

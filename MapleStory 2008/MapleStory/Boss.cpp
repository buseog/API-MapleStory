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
	m_iPattern = 0;
	m_cTimer.TimeSetting();

	m_tInfo = INFO(0, 0, 386.f, 308.f);
	m_tStat = STAT(1000000.f, 1000000.f, 1500.f, 100.f, 10, 500.f, 1.f, 50000);
	m_tSprite = SPRITE(0, 8, 1, 80);

	m_dwState = ST_STAND;
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
		if (m_dwState == ST_DEATH)
			m_bDestroy = true;

 		if (m_dwState != ST_STAND)
			m_dwState = ST_STAND;

		m_tSprite.iStart = 0;
	}

	SetState(ST_STAND, 8, 1, 100);
	SetState(ST_ATTACK, 31, 0, 80);
	SetState(ST_ATTACK2, 31, 0, 80);
	SetState(ST_HIT, 1, 4, 900);
	SetState(ST_DEATH, 7, 5, 300);

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
		RGB(210, 228, 247));
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

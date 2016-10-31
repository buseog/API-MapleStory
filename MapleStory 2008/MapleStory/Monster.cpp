#include "StdAfx.h"
#include "Monster.h"

CMonster::CMonster(void)
{
}

CMonster::~CMonster(void)
{
}

void CMonster::Initialize(void)
{
	m_cTimer.TimeSetting();

	if (m_strKey == "GreenMushRoom_LEFT" || m_strKey == "GreenMushRoom_RIGHT")
	{
		m_tInfo = INFO(0, 0, 60.f, 60.f);
		m_tStat = STAT(10.f, 10.f, 10.f, 5.f);
		m_tSprite = SPRITE(0, 4, 1, 80);
	}

	if (m_strKey == "CoupleMushRoom_LEFT" || m_strKey == "CoupleMushRoom_RIGHT")
	{
		m_tInfo = INFO(0, 0, 170.f, 170.f);
		m_tStat = STAT(10.f, 10.f, 10.f, 5.f);
		m_tSprite = SPRITE(0, 8, 0, 80);
	}

	if (m_strKey == "BlueMushRoom_LEFT" || m_strKey == "BlueMushRoom_RIGHT")
	{
		m_tInfo = INFO(0, 0, 70.f, 70.f);
		m_tStat = STAT(10.f, 10.f, 10.f, 5.f);
		m_tSprite = SPRITE(0, 3, 3, 80);
	}

	if (m_strKey == "PurpleMushRoom_LEFT" || m_strKey == "PurpleMushRoom_RIGHT")
	{
		m_tInfo = INFO(0, 0, 80.f, 80.f);
		m_tStat = STAT(10.f, 10.f, 10.f, 5.f);
		m_tSprite = SPRITE(0, 4, 1, 80);

	}

	m_dwTime = GetTickCount();
	m_dwKey = 0;
	m_iDrawID = 0;
}
void CMonster::Progress(DWORD _delta)
{
	Gravity();

	if ((m_cTimer.m_fRemainTime[1] -= _delta) >= 0)
	{
		m_tInfo.fX -= m_tStat.fSpeed;
	}
	else
	{
		m_tStat.fSpeed *= -1.f;
		m_cTimer.m_fRemainTime[1] = 1000.f;
	}	

	if (m_dwTime + m_tSprite.dwTime < GetTickCount())
	{
		m_dwTime = GetTickCount();

		++m_tSprite.iStart;
	}

	if (m_tSprite.iStart >= m_tSprite.iLast)
	{
 		if (m_dwState != ST_STAND && m_dwState != ST_PROSTRATE && m_dwState != ST_JUMP)
			m_dwState = ST_STAND;

		m_tSprite.iStart = 0;
	}
}
void CMonster::Render(HDC hdc)
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
void CMonster::Release(void)
{

}
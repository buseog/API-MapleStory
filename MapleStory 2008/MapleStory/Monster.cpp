#include "StdAfx.h"
#include "Monster.h"
#include "Gold.h"

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
		m_tStat = STAT(1500.f, 1500.f, 500.f, 0.f, 1, 50.f, 2.f, 500);
		m_tSprite = SPRITE(0, 4, 1, 80);
	}

	if (m_strKey == "CoupleMushRoom_LEFT" || m_strKey == "CoupleMushRoom_RIGHT")
	{
		m_tInfo = INFO(0, 0, 170.f, 110.f);
		m_tStat = STAT(1500.f, 1500.f, 500.f, 0.f, 1, 500.f, 2.f, 500);
		m_tSprite = SPRITE(0, 8, 0, 80);
	}

	if (m_strKey == "BlueMushRoom_LEFT" || m_strKey == "BlueMushRoom_RIGHT")
	{
		m_tInfo = INFO(0, 0, 70.f, 70.f);
		m_tStat = STAT(1500.f, 1500.f, 500.f, 0.f, 1, 150.f, 2.f, 500);
		m_tSprite = SPRITE(0, 3, 3, 80);
	}

	if (m_strKey == "PurpleMushRoom_LEFT" || m_strKey == "PurpleMushRoom_RIGHT")
	{
		m_tInfo = INFO(0, 0, 80.f, 80.f);
		m_tStat = STAT(1500.f, 1500.f, 500.f, 0.f, 1, 300.f, 2.f, 500);
		m_tSprite = SPRITE(0, 4, 1, 80);
	}

	m_dwTime = GetTickCount();
	m_dwKey = 0;
}
void CMonster::Progress(DWORD _delta)
{
	Gravity();

	if (m_dwState != ST_HIT)
	{
		if ((m_cTimer.dwRemainTime[1] + 1100) >= GetTickCount())
		{			
			m_tInfo.fX -= m_tStat.fSpeed;
		}
		else
		{
			if (m_strKey == "PurpleMushRoom_LEFT")
			{
				m_strKey = "PurpleMushRoom_RIGHT";
			}
			else if (m_strKey == "PurpleMushRoom_RIGHT")
			{
				m_strKey = "PurpleMushRoom_LEFT";
			}

			if (m_strKey == "GreenMushRoom_LEFT")
			{
				m_strKey = "GreenMushRoom_RIGHT";
			}
			else if (m_strKey == "GreenMushRoom_RIGHT")
			{
				m_strKey = "GreenMushRoom_LEFT";
			}

			if (m_strKey == "BlueMushRoom_LEFT")
			{
				m_strKey = "BlueMushRoom_RIGHT";
			}
			else if (m_strKey == "BlueMushRoom_RIGHT")
			{
				m_strKey = "BlueMushRoom_LEFT";
			}

			if (m_strKey == "CoupleMushRoom_LEFT")
			{
				m_strKey = "CoupleMushRoom_RIGHT";
			}
			else if (m_strKey == "CoupleMushRoom_RIGHT")
			{
				m_strKey = "CoupleMushRoom_LEFT";
			}
			m_tStat.fSpeed *= -1.f;
			m_cTimer.dwRemainTime[1] = GetTickCount();
		}
	}

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


	if (m_strKey == "GreenMushRoom_LEFT" || m_strKey == "GreenMushRoom_RIGHT")
	{
		SetState(ST_STAND, 2, 0, 100);
		SetState(ST_WALK, 5, 1, 100);
		SetState(ST_HIT, 1, 2, 800);
		SetState(ST_DEATH, 10, 3, 80);
	}

	else if (m_strKey == "CoupleMushRoom_LEFT" || m_strKey == "CoupleMushRoom_RIGHT")
	{		
		SetState(ST_STAND, 8, 0, 100);
		SetState(ST_WALK, 14, 1, 80);
		SetState(ST_HIT, 1, 2, 800);
		SetState(ST_DEATH, 5, 3, 80);
		
	}

	else if (m_strKey == "BlueMushRoom_LEFT" || m_strKey == "BlueMushRoom_RIGHT")
	{
		SetState(ST_STAND, 2, 0, 100);
		SetState(ST_WALK, 3, 1, 100);
		SetState(ST_HIT, 1, 2, 800);
		SetState(ST_DEATH, 3, 3, 80);
	}

	else if (m_strKey == "PurpleMushRoom_LEFT" || m_strKey == "PurpleMushRoom_RIGHT")
	{
		SetState(ST_STAND, 4, 0, 100);
		SetState(ST_WALK, 4, 1, 100);
		SetState(ST_HIT, 1, 2, 800);
		SetState(ST_DEATH, 10, 3, 80);
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

void CMonster::SetState(DWORD _dwState, int _iLast, int _iMotion, DWORD _dwTime)
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

CItem* CMonster::GetDropItem(void)
{
	int Random = m_tStat.iGold + rand() % 1000;
	CItem* pDropItem = NULL;

	if (Random < 100)
	{
		pDropItem = new CGold(L"Gold3", Random, 1, 1, IT_GOLD);
	}
	else if (Random < 1000)
	{
		pDropItem = new CGold(L"Gold2", Random, 1, 1, IT_GOLD);
	}
	else
	{
		pDropItem = new CGold(L"Gold", Random, 1, 1, IT_GOLD);
	}

	pDropItem->SetPos(m_tInfo.fX, m_tInfo.fY - 15);
	return pDropItem;
}

DWORD CMonster::GetDrop(void)
{
	return m_dwDrop;
}

void CMonster::SetDrop(int _dwDrop)
{
	m_dwDrop = _dwDrop;
}
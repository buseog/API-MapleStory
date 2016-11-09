#include "StdAfx.h"
#include "Pet.h"
#include "Player.h"
#include "KeyMgr.h"

CPet::CPet(void)
{
}

CPet::~CPet(void)
{
	Release();
}


void CPet::Initialize(void)
{
	m_cTimer.TimeSetting();
	m_strKey = "RPet";
	m_tInfo = INFO(0, 0, 50.f, 40.f);
	m_tStat = STAT(100.f, 100.f, 200.f, 0.f, 1, 0.f, 2.f, 1000);
	m_tSprite = SPRITE(0, 5, 0, 90);
	m_dwTime = GetTickCount();
	m_dwState = ST_STAND;
	m_dwKey = 0;
}

void CPet::Progress(DWORD _delta)
{
	if (m_dwState == ST_STAND)
	{
		if ((m_cTimer.fRemainTime[0] += _delta) > 5000.f)
		{
			
		}
	}

	if (m_pPlayer->GetInfo().fX > m_tInfo.fX)
		m_strKey = "RPet";

	else
		m_strKey = "Pet";

	if (m_dwTime + m_tSprite.dwTime < GetTickCount())
	{
		m_dwTime = GetTickCount();

		++m_tSprite.iStart;
	}

	if (m_tSprite.iStart >= m_tSprite.iLast)
	{
		if ((m_dwState != ST_STAND) && (m_dwState != ST_PROSTRATE) && (m_dwState != ST_JUMP) && (m_dwState != ST_UP) &&  (m_dwState != ST_HIT) && (m_dwState != ST_PROSTATTACK))
			m_dwState = ST_STAND;

		m_tSprite.iStart = 0;
		
	}


	if (m_dwState == ST_WALK)
	{
		if (m_pPlayer->GetInfo().fX - m_tInfo.fX > 10)
		{
			m_strKey = "RPet";
			m_tInfo.fX += m_tStat.fSpeed;
		}
		else
		{
			m_dwState = ST_STAND;
		}
		
		if (m_pPlayer->GetInfo().fX - m_tInfo.fX < -10)
		{
			m_strKey = "Pet";
			m_tInfo.fX -= m_tStat.fSpeed;
		}
		else
		{
			m_dwState = ST_STAND;
		}

	}

	if (m_pPlayer->GetInfo().fX - m_tInfo.fX > 300 || m_pPlayer->GetInfo().fX - m_tInfo.fX < -300)
		m_dwState = ST_WALK;


	SetState(ST_STAND, 5, 0, 80);
	SetState(ST_WALK, 4, 1, 80);
	SetState(ST_ATTACK, 3, 2, 80);
	SetState(ST_ATTACK2, 3, 3, 80);
	SetState(ST_ATTACK3, 6, 5, 80);
}

void CPet::Render(HDC hdc)
{
	TransparentBlt(hdc,
		int(m_tInfo.fX - m_tInfo.fCX / 2.f + CParent::m_ptScroll.x),
		int(m_tInfo.fY - m_tInfo.fCY / 2.f + CParent::m_ptScroll.y),
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

void	CPet::SetPlayer(CParent*	_pPlayer)
{
	m_pPlayer = _pPlayer;
}

void CPet::SetState(DWORD _dwState, int _iLast, int _iMotion, DWORD _dwTime)
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

void CPet::KeyInput(void)
{
	m_dwKey = CKeyMgr::GetInstance()->GetKey();

	if (!m_dwKey && (m_dwState != ST_ATTACK) && (m_dwState != ST_ATTACK2) && (m_dwState != ST_UP) && (m_bLand == true) && (m_dwState != ST_HIT))
	{
   		m_dwState = ST_STAND;
	}
	
	if (m_dwKey && (m_dwKey != KEY_UP) && (m_dwState != ST_ATTACK) && (m_dwState != ST_ATTACK2) && 
		(m_dwState != ST_PROSTRATE) && (m_dwState != ST_UP) && (m_bLand == true) && (m_dwState != ST_PROSTATTACK) &&
		(m_dwKey != KEY_Q) && (m_dwKey != KEY_W) && (m_dwKey != KEY_E) && (m_dwKey != KEY_R))
	{
		m_dwState = ST_WALK;
	}
}
#include "StdAfx.h"
#include "Player.h"

CPlayer::CPlayer(void)
{
}

CPlayer::~CPlayer(void)
{
	Release();
}

void CPlayer::Initialize(void)
{
	m_tInfo = INFO(WINCX / 2.f, WINCY / 2.f, 100.f, 100.f);
	m_tStat = STAT(10.f, 10.f, 10.f, 10.f);

	m_BmpKey = "Player_LEFT";
	m_iDrawID = 0;
}

void CPlayer::Progress(void)
{
	KeyInput();
	Gravity();
}

void CPlayer::Render(HDC hdc)
{
		TransparentBlt(hdc, 
		int(m_tInfo.fX - m_tInfo.fCX / 2.f + m_fScrollX),
		int(m_tInfo.fY - m_tInfo.fCY / 2.f + m_fScrollY),
		int(m_tInfo.fCX), int(m_tInfo.fCY)
		, (*m_pBitMap)[m_BmpKey]->GetMemdc(),
		int(m_tInfo.fCX), 
		int(m_tInfo.fCY), 
		(int)m_tInfo.fCX, (int)m_tInfo.fCY, 
		RGB(71, 0, 60));
}

void CPlayer::Release(void)
{
}

void CPlayer::KeyInput(void)
{
	if(GetAsyncKeyState(VK_LEFT))
	{
		m_tInfo.fX -= m_tStat.fSpeed;
		m_fScrollX += m_tStat.fSpeed;
	}
	if(GetAsyncKeyState(VK_RIGHT))
	{
		m_tInfo.fX += m_tStat.fSpeed;
		m_fScrollX -= m_tStat.fSpeed;
	}
	if(GetAsyncKeyState(VK_UP))
	{
		m_tInfo.fY -= m_tStat.fSpeed;
		m_fScrollY += m_tStat.fSpeed;
	}

	if(GetAsyncKeyState(VK_DOWN))
	{
		m_tInfo.fY += m_tStat.fSpeed;
		m_fScrollY -= m_tStat.fSpeed;
	}

	if(GetAsyncKeyState(VK_SPACE))
	{
		if (m_bLand == true)
		{
			m_fJpower = -10.f;
			m_bLand = false;
		}
	}
}


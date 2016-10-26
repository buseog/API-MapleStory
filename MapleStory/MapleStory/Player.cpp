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
}

void CPlayer::Progress(void)
{
	KeyInput();
	Gravity();
}

void CPlayer::Render(HDC hdc)
{
	Graphics graphics(hdc);
	Image	image(L"../Texture/alert_0.png");
	graphics.DrawImage(&image, m_tInfo.fX + m_fScrollX, m_tInfo.fY + m_fScrollY);
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


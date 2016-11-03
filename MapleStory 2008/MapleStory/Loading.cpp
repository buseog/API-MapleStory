#include "StdAfx.h"
#include "Loading.h"

CLoading::CLoading(void)
{
}

CLoading::~CLoading(void)
{
	Release();
}

void CLoading::Initialize(void)
{
	m_strKey = "Loading";
	m_tInfo = INFO(WINCX / 2.f, WINCY / 2.f, 800.f, 600.f);
	m_tSprite = SPRITE(0, 14, 0, 150);
}
void CLoading::Progress(DWORD _delta)
{
	if (m_dwTime + m_tSprite.dwTime < GetTickCount())
	{
		m_dwTime = GetTickCount();

		++m_tSprite.iStart;
	}

	if (m_tSprite.iStart >= m_tSprite.iLast)
	{
		SetDestroy(true);
		return;
	}
}
void CLoading::Render(HDC hdc)
{
	BitBlt(hdc,
		int(m_tInfo.fX - m_tInfo.fCX / 2.f),
		int(m_tInfo.fY - m_tInfo.fCY / 2.f),
		int(m_tInfo.fCX),
		int(m_tInfo.fCY),
		(*m_pBitMap)[m_strKey]->GetMemdc(),
		int(m_tInfo.fCX * m_tSprite.iStart),
		int(m_tInfo.fCY * m_tSprite.iMotion),
		SRCCOPY);
}
void CLoading::Release(void)
{
}
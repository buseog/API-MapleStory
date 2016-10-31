#include "StdAfx.h"
#include "Effect.h"

CEffect::CEffect(void)
{
}

CEffect::~CEffect(void)
{
}


void CEffect::Initialize(void)
{
	if (m_strKey == "Ascend_EFFECT")
	{
		m_tInfo = INFO(0, 0, 100.f, 114.f);
		m_tSprite = SPRITE(0, 6, 0, 80);
	}

	if (m_strKey == "Annihilation_EFFECT")
	{
		m_tInfo = INFO(0, 0, 120.f, 140.f);
		m_tSprite = SPRITE(0, 5, 0, 80);
	}


	if (m_strKey == "Bolt_EFFECT")
	{
		m_tInfo = INFO(0, 0, 150.f, 100.f);
		m_tSprite = SPRITE(0, 6, 0, 80);
	}

	if (m_strKey == "Typhoon_EFFECT")
	{
		m_tInfo = INFO(0, 0, 130.f, 130.f);
		m_tSprite = SPRITE(0, 7, 0, 80);
	}
}
void CEffect::Progress(DWORD _delta)
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
void CEffect::Render(HDC hdc)
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
void CEffect::Release(void)
{

}
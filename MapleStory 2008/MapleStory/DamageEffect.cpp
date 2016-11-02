#include "StdAfx.h"
#include "DamageEffect.h"

CDamageEffect::CDamageEffect(void)
{
}

CDamageEffect::~CDamageEffect(void)
{
}


void CDamageEffect::Initialize(void)
{
	if (m_strKey == "DamageEffect")
	{
		m_tInfo = INFO(0, 0, 70.f, 70.f);
		m_tStat = STAT(0, 0, 0, 5.f);
		m_tSprite = SPRITE(0, 10, 0, 80);
	}

	if (m_strKey == "CriticalEffect")
	{
		m_tInfo = INFO(0, 0, 70.f, 70.f);
		m_tStat = STAT(0, 0, 0, 5.f);
		m_tSprite = SPRITE(0, 10, 0, 80);
	}

}
void CDamageEffect::Progress(DWORD _delta)
{
	m_tInfo.fY -= m_tStat.fSpeed;

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
void CDamageEffect::Render(HDC hdc)
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
void CDamageEffect::Release(void)
{

}
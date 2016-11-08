#include "StdAfx.h"
#include "DamageEffect.h"

CDamageEffect::CDamageEffect(void)
:m_iDamage(0)
{
}

CDamageEffect::~CDamageEffect(void)
{
}


void CDamageEffect::Initialize(void)
{
	m_cTimer.fRemainTime[0] = 1000.f;

	int iPosition = 10000;

	for (int i = 0; i < 5; ++i)
	{
		m_iPrintDamage[i] = m_iDamage / iPosition;
		 m_iDamage -= m_iPrintDamage[i] * iPosition;
		iPosition /= 10;
	}

	if (m_strKey == "DamageEffect")
	{
		m_tInfo = INFO(0, 0, 50.f, 40.f);
		m_tStat.fSpeed = 2.f;
		m_tSprite = SPRITE(0, 10, 0, 80);
	}

	else if (m_strKey == "CriticalEffect")
	{
		m_tInfo = INFO(0, 0, 60.f, 50.f);
		m_tStat.fSpeed = 2.f;
		m_tSprite = SPRITE(0, 10, 0, 80);
	}

	else if (m_strKey == "HitEffect")
	{
		m_tInfo = INFO(0, 0, 50.f, 40.f);
		m_tStat.fSpeed = 2.f;
		m_tSprite = SPRITE(0, 10, 0, 80);
	}
	
}
void CDamageEffect::Progress(DWORD _delta)
{
	if ((m_cTimer.fRemainTime[0] -= _delta) <= 0)
		m_bDestroy = true;

	else
		m_tInfo.fY -= m_tStat.fSpeed;

	
}
void CDamageEffect::Render(HDC hdc)
{
	int iCount = 0;
	bool bSkip = true;

	for (int i = 0; i < 5; ++i)
	{
		if (m_iPrintDamage[i] == 0 && bSkip)
		{
			bSkip = true;
		}
		else
		{
			bSkip = false;
		}

		if (!bSkip)
		{
		TransparentBlt(hdc,
			int(m_tInfo.fX - m_tInfo.fCX / 2.f + (30 * iCount) + m_ptScroll.x),
			int(m_tInfo.fY - m_tInfo.fCY / 2.f + m_ptScroll.y),
			int(m_tInfo.fCX),
			int(m_tInfo.fCY),
			(*m_pBitMap)[m_strKey]->GetMemdc(),
			int(m_tInfo.fCX * m_iPrintDamage[i]),
			int(m_tInfo.fCY * m_tSprite.iMotion),
			(int)m_tInfo.fCX,
			(int)m_tInfo.fCY,
			RGB(255, 255, 250));

		++iCount;
		}
	}
}
void CDamageEffect::Release(void)
{

}

void CDamageEffect::SetDamage(int _Damage)
{
	m_iDamage = _Damage;
}
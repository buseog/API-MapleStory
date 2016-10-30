#include "stdafx.h"
#include "Skill.h"

CSkill::CSkill()
{
}


CSkill::~CSkill()
{
	Release();
}

void CSkill::Initialize(void)
{
	if (m_strKey == "Annihilation_LEFT" || m_strKey == "Annihilation_RIGHT")
	{
		m_tInfo = INFO(0, 0, 630.f, 230.f);
		m_tSprite = SPRITE(0, 13, 0, 80);
	}

	if (m_strKey == "Typhoon_LEFT" || m_strKey == "Typhoon_RIGHT")
	{
		m_tInfo = INFO(0, 0, 788.f, 450.f);
		m_tSprite = SPRITE(0, 21, 0, 80);
	}

	if (m_strKey == "Range_LEFT" || m_strKey == "Range_LEFT")
	{
		m_tInfo = INFO(0, 0, 699.f, 370.f);
		m_tSprite = SPRITE(0, 10, 0, 80);
	}

	if (m_strKey == "Beyond_LEFT" || m_strKey == "Beyond_RIGHT")
	{
		m_tInfo = INFO(0, 0, 400.f, 400.f);
		m_tSprite = SPRITE(0, 14, 0, 80);
	}
	
	m_dwTime = GetTickCount();
	m_dwKey = 0;
	m_iDrawID = 0;
}
void CSkill::Progress(void)
{
	if (m_dwTime + m_tSprite.dwTime < GetTickCount())
	{
		m_dwTime = GetTickCount();

		++m_tSprite.iStart;
	}

	if (m_tSprite.iStart >= m_tSprite.iLast)
		return;
}
void CSkill::Render(HDC hdc)
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
void CSkill::Release(void)
{

}
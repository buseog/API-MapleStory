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
	m_tInfo = INFO(WINCX / 2.f, WINCY / 2.f, 630.f, 230.f);
	m_tSprite = SPRITE(0, 13, 0, 80);

	m_dwTime = GetTickCount();
	m_strKey = "Annihilation_LEFT";
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
		int(m_tInfo.fX - m_tInfo.fCX / 2.f + m_fScrollX),
		int(m_tInfo.fY - m_tInfo.fCY / 2.f + m_fScrollY),
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
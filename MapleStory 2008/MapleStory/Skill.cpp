#include "stdafx.h"
#include "Skill.h"

CSkill::CSkill()
:m_bHit(false)
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
		m_tInfo = INFO(0, 0, 315.f, 115.f);
		m_tSprite = SPRITE(0, 13, 0, 60);
	}

	if (m_strKey == "Ascend_LEFT" || m_strKey == "Ascend_RIGHT")
	{
		m_tInfo = INFO(0, 0, 250.f, 250.f);
		m_tSprite = SPRITE(0, 10, 0, 60);
	}


	if (m_strKey == "Typhoon_LEFT" || m_strKey == "Typhoon_RIGHT")
	{
		m_tInfo = INFO(0, 0, 300.f, 171.f);
		m_tSprite = SPRITE(0, 17, 0, 60);
	}

	if (m_strKey == "Bolt_LEFT" || m_strKey == "Bolt_RIGHT")
	{
		m_tInfo = INFO(0, 0, 243.f, 142.f);
		m_tSprite = SPRITE(0, 15, 0, 60);
	}

	if (m_strKey == "Range")
	{
		m_tInfo = INFO(0, 0, 233.f, 123.f);
		m_tSprite = SPRITE(0, 10, 0, 60);
	}

	if (m_strKey == "Beyond_LEFT" || m_strKey == "Beyond_RIGHT")
	{
		m_tInfo = INFO(0, 0, 400.f, 400.f);
		m_tSprite = SPRITE(0, 14, 0, 60);
	}

	if (m_strKey == "Beyond2_LEFT" || m_strKey == "Beyond2_RIGHT")
	{
		m_tInfo = INFO(0, 0, 649.f, 300.f);
		m_tSprite = SPRITE(0, 10, 0, 60);
	}

	if (m_strKey == "Beyond3_LEFT" || m_strKey == "Beyond3_RIGHT")
	{
		m_tInfo = INFO(0, 0, 400.f, 300.f);
		m_tSprite = SPRITE(0, 13, 0, 60);
	}

	m_dwTime = GetTickCount();
	m_dwKey = 0;
}
void CSkill::Progress(DWORD _delta)
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

void	CSkill::SetHit(bool _YN)
{
	m_bHit = _YN;
}
bool	CSkill::GetHit(void)
{
	return m_bHit;
}
#include "StdAfx.h"
#include "SkillEffect.h"

CSkillEffect::CSkillEffect(void)
{
}

CSkillEffect::~CSkillEffect(void)
{
	Release();
}

void CSkillEffect::Initialize(void)
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
		m_tInfo = INFO(0, 0, 130.f, 110.f);
		m_tSprite = SPRITE(0, 7, 0, 80);
	}

	if (m_strKey == "Beyond1_EFFECT")
	{
		m_tInfo = INFO(0, 0, 220.f, 200.f);
		m_tSprite = SPRITE(0, 6, 0, 80);
	}

	if (m_strKey == "Beyond2_EFFECT")
	{
		m_tInfo = INFO(0, 0, 250.f, 100.f);
		m_tSprite = SPRITE(0, 6, 0, 80);
	}

	if (m_strKey == "Beyond3_EFFECT")
	{
		m_tInfo = INFO(0, 0, 350.f, 300.f);
		m_tSprite = SPRITE(0, 7, 0, 80);
	}

	if (m_strKey == "Range_EFFECT")
	{
		m_tInfo = INFO(0, 0, 150.f, 110.f);
		m_tSprite = SPRITE(0, 4, 0, 80);
	}

	if (m_strKey == "LevelUpEFFECT")
	{
		m_tInfo = INFO(0, 0, 350.f, 420.f);
		m_tSprite = SPRITE(0, 21, 0, 50);
	}

	if (m_strKey == "Boss_Back")
	{
		m_tInfo = INFO(0, 0, 297.f, 333.f);
		m_tStat.fAttack = 100.f;
		m_tSprite = SPRITE(0, 27, 0, 30);
	}
	if (m_strKey == "Boss_Fire")
	{
		m_tInfo = INFO(0, 0, 154.f, 152.f);
		m_tStat.fAttack = 600.f;
		m_tSprite = SPRITE(0, 6, 0, 80);
	}

	if (m_strKey == "Intensity_EFFECT")
	{
		m_tInfo = INFO(0, 0, 178.f, 244.f);
		m_tSprite = SPRITE(0, 17, 0, 80);
	}

	if (m_strKey == "Fire_EFFECT")
	{
		m_tInfo = INFO(0, 0, 154.f, 152.f);
		m_tSprite = SPRITE(0, 6, 0, 80);
	}

	if (m_strKey == "Boss_Skill")
	{
		m_tInfo = INFO(0, 0, 103.f, 103.f);
		m_tSprite = SPRITE(0, 16, 0, 80);
	}

	if (m_strKey == "Boss_Skill2")
	{
		m_tInfo = INFO(0, 0, 220.f, 195.f);
		m_tSprite = SPRITE(0, 6, 0, 80);
	}

	if (m_strKey == "Boss_Skill3")
	{
		m_tInfo = INFO(0, 0, 300.f, 271.f);
		m_tSprite = SPRITE(0, 12, 0, 80);
	}
}
void CSkillEffect::Progress(DWORD _delta)
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
void CSkillEffect::Render(HDC hdc)
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
void CSkillEffect::Release(void)
{

}
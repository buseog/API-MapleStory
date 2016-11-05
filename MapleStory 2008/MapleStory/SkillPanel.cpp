#include "StdAfx.h"
#include "SkillPanel.h"

CSkillPanel::CSkillPanel(void)
{
}

CSkillPanel::~CSkillPanel(void)
{
}

void CSkillPanel::Initialize(void)
{
	m_strKey = "SkillPanel";
	m_tInfo = INFO(0, 0, 174.f, 300.f);
}

void CSkillPanel::Progress(DWORD _delta)
{

}

void CSkillPanel::Render(HDC hdc)
{
	BitBlt(hdc,
		int(m_tInfo.fX - m_tInfo.fCX / 2.f),
		int(m_tInfo.fY - m_tInfo.fCY / 2.f),
		int(m_tInfo.fCX),
		int(m_tInfo.fCY),
		(*m_pBitMap)[m_strKey]->GetMemdc(),
		0,
		0,
		SRCCOPY);
}

void CSkillPanel::Release(void)
{

}

RECT CSkillPanel::GetRect(void)
{
	RECT	rc = {
		int(m_tInfo.fX - m_tInfo.fCX / 2.f),
		int(m_tInfo.fY - m_tInfo.fCY / 2.f),
		int(m_tInfo.fX + m_tInfo.fCX / 2.f),
		int(m_tInfo.fY - m_tInfo.fCY / 2.f + 20)
	};

	return rc;
}

void CSkillPanel::UIPicking(void)
{
}
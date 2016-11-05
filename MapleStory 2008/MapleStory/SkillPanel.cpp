#include "StdAfx.h"
#include "SkillPanel.h"
#include "Factory.h"

CSkillPanel::CSkillPanel(void)
{
}

CSkillPanel::~CSkillPanel(void)
{
}

void CSkillPanel::Initialize(void)
{
	m_bOnOff = false;
	m_strKey = "SkillPanel";
	m_tInfo = INFO(0, 0, 174.f, 300.f);

	m_pCloseButton = CFactory<CUI>::CreateUI(0.f, 0.f, "Close");
}

void CSkillPanel::Progress(DWORD _delta)
{
	if (PtInRect(&m_pCloseButton->GetRect(), GetMouse()))
	{
		if (GetAsyncKeyState(VK_LBUTTON))
			m_bOnOff = false;
	}

	float fCloseX = m_tInfo.fX + m_tInfo.fCX / 2.f - 17.f;
	float fCloseY = m_tInfo.fY - m_tInfo.fCY / 2.f + 12.f;

	m_pCloseButton->SetPos(fCloseX, fCloseY);
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

	m_pCloseButton->Render(hdc);
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
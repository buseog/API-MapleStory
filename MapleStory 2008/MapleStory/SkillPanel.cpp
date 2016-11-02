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
	m_bMouse = false;
	m_strKey = "SkillPanel";
	m_tInfo = INFO(0, 0, 174.f, 300.f);
}

void CSkillPanel::Progress(DWORD _delta)
{
	float fX = float(GetMouse().x - m_prevPT.x);
	float fY = float(GetMouse().y - m_prevPT.y);
	
	if(m_bMouse)
	{
		m_tInfo.fX += fX;
		m_tInfo.fY += fY;
	}

	if(PtInRect(&GetRect(), GetMouse()))
	{
		if(GetAsyncKeyState(VK_LBUTTON))
		{
			m_prevPT = GetMouse();
			m_bMouse = true;
		}
		else
			m_bMouse = false;
	}
	else
		m_bMouse = false;
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
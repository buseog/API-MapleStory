#include "StdAfx.h"
#include "UI.h"

CUI::CUI(void)
{
}

CUI::~CUI(void)
{
}

void CUI::Initialize(void)
{
	if (m_strKey == "UI")
	{
		m_tInfo = INFO(0, 0, 800.f, 600.f);
		m_tSprite = SPRITE(0, 0, 0, 0);
	}
}

void CUI::Progress(void)
{

}

void CUI::Render(HDC hdc)
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

void CUI::Release(void)
{
	
}
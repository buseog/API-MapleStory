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

	if (m_strKey == "Inventory")
	{
		m_tInfo = INFO(0, 0, 172.f, 335.f);
		m_tSprite = SPRITE(0, 0, 0, 0);
	}

	if (m_strKey == "Equipment")
	{
		m_tInfo = INFO(0, 0, 237.f, 332.f);
		m_tSprite = SPRITE(0, 0, 0, 0);
	}

	if (m_strKey == "Skill")
	{
		m_tInfo = INFO(0, 0, 174.f, 300.f);
		m_tSprite = SPRITE(0, 0, 0, 0);
	}
}

void CUI::Progress(void)
{

}

void CUI::Render(HDC hdc)
{
	if (m_strKey == "UI")
	{
		TransparentBlt(hdc,
			int(m_tInfo.fX - m_tInfo.fCX / 2.f),
			int(m_tInfo.fY - m_tInfo.fCY / 2.f),
			int(m_tInfo.fCX),
			int(m_tInfo.fCY),
			(*m_pBitMap)[m_strKey]->GetMemdc(),
			int(m_tInfo.fCX * m_tSprite.iStart),
			int(m_tInfo.fCY * m_tSprite.iMotion),
			(int)m_tInfo.fCX,
			(int)m_tInfo.fCY,
			RGB(255, 255, 250));
	}

	else if (m_strKey == "Inventory" || m_strKey == "Equipment" || m_strKey == "Skill")
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
}

void CUI::Release(void)
{
	
}
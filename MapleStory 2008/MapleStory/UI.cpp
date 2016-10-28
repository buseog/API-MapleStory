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
	m_tInfo.fCX = 150.f;
	m_tInfo.fCY = 60.f;
	m_iDrawID   = 0;
}

void CUI::Progress(void)
{
	if(PtInRect(&GetRect(), GetMouse()))
	{
		m_iDrawID = 1;

		if(GetAsyncKeyState(VK_LBUTTON))
		{
			if(m_strKey == "Start")
				m_iButton = SC_VILLAGE;

			else if(m_strKey == "Edit")
				m_iButton = SC_MAPEDIT;

			else if(m_strKey == "Exit")
				m_iButton = SC_END;
		}
	}
	else
		m_iDrawID = 0;
}

void CUI::Render(HDC hdc)
{
	TransparentBlt(hdc, 
		int(m_tInfo.fX - m_tInfo.fCX / 2.f),
		int(m_tInfo.fY - m_tInfo.fCY / 2.f),
		int(m_tInfo.fCX), 
		int(m_tInfo.fCY),
		(*m_pBitMap)[m_strKey]->GetMemdc(),
		0, 
		int(m_tInfo.fCY * m_iDrawID), 
		(int)m_tInfo.fCX, 
		(int)m_tInfo.fCY, 
		RGB(255, 0, 255));
}

void CUI::Release(void)
{
	
}
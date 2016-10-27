#include "StdAfx.h"
#include "MyButton.h"
#include "BitBmp.h"

CMyButton::CMyButton(void)
:m_iDrawID(0)
,m_iButton(0)
{
}

CMyButton::~CMyButton(void)
{
	Release();
}

void CMyButton::Initialize(void)
{
	m_tInfo.fCX = 150.f;
	m_tInfo.fCY = 60.f;
	m_iDrawID   = 0;
}

void CMyButton::Progress(void)
{
	if(PtInRect(&GetRect(), GetMouse()))
	{
		m_iDrawID = 1;

		if(GetAsyncKeyState(VK_LBUTTON))
		{
			if(m_BmpKey == "Start")
				m_iButton = SC_VILLAGE;

			else if(m_BmpKey == "Edit")
				m_iButton = SC_MAPEDIT;

			else if(m_BmpKey == "Exit")
				m_iButton = SC_END;
		}
	}
	else
		m_iDrawID = 0;
}

void CMyButton::Render(HDC hdc)
{
	TransparentBlt(hdc, 
		int(m_tInfo.fX - m_tInfo.fCX / 2.f),
		int(m_tInfo.fY - m_tInfo.fCY / 2.f),
		int(m_tInfo.fCX), 
		int(m_tInfo.fCY),
		(*m_pBitMap)[m_BmpKey]->GetMemdc(),
		0, 
		int(m_tInfo.fCY * m_iDrawID), 
		(int)m_tInfo.fCX, 
		(int)m_tInfo.fCY, 
		RGB(255, 0, 255));
}

void CMyButton::Release(void)
{
	
}

int CMyButton::GetSelect(void)
{
	return m_iButton;
}
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
				m_iButton = BT_START;

			else if(m_BmpKey == "Edit")
				m_iButton = BT_EDIT;

			else if(m_BmpKey == "Exit")
				m_iButton = BT_EXIT;
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
		int(m_tInfo.fCX * m_iDrawID), 0, 
		(int)m_tInfo.fCX, 
		(int)m_tInfo.fCY, 
		RGB(255, 255, 255));
}

void CMyButton::Release(void)
{
	
}

int CMyButton::GetSelect(void)
{
	return m_iButton;
}
#include "StdAfx.h"
#include "MyButton.h"
#include "BitBmp.h"

CMyButton::CMyButton(void)

{
}

CMyButton::CMyButton(string _strKey)
:m_iButton(0)
,CUI(_strKey)
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

void CMyButton::Progress(DWORD _delta)
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

void CMyButton::Render(HDC hdc)
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

void CMyButton::Release(void)
{
	
}

int CMyButton::GetSelect(void)
{
	return m_iButton;
}

RECT CMyButton::GetRect(void)
{
	RECT	rc = {

		int(m_tInfo.fX - m_tInfo.fCX / 2.f),
		int(m_tInfo.fY - m_tInfo.fCY / 2.f),
		int(m_tInfo.fX + m_tInfo.fCX / 2.f),
		int(m_tInfo.fY + m_tInfo.fCY / 2.f)
	};

	return rc;
}
#include "StdAfx.h"
#include "Qeust.h"
#include "Factory.h"

CQeust::CQeust(void)
{
}

CQeust::CQeust(string _strKey)
{
	m_strKey = _strKey;
}

CQeust::~CQeust(void)
{
}


void	CQeust::Initialize(void)
{
	m_bOnOff = false;
	m_tInfo = INFO(300.f, 200.f, 517.f, 188.f);
	m_dwTime = GetTickCount();
	QeustStart();
}

void	CQeust::Progress(DWORD _dwDelta)
{
	if (m_dwTime + 60 <= GetTickCount())
	{
		UIPicking();
		m_dwTime = GetTickCount();
	}

	if (GetAsyncKeyState(VK_RETURN))
	{
		m_bOnOff = false;
	}

	switch (((CPlayer*)m_pPlayer)->GetQuest())
	{
	case 0:
		break;
	}
}

void CQeust::Render(HDC hdc)
{
	BitBlt(hdc, 
	int(m_tInfo.fX - m_tInfo.fCX / 2.f), 
	int(m_tInfo.fY - m_tInfo.fCY / 2.f), 
	int(m_tInfo.fCX), 
	int(m_tInfo.fCY), 
	(*m_pBitMap)[m_strKey]->GetMemdc(), 
	0, 0, SRCCOPY);

}

void CQeust::Release(void)
{
	::Safe_Delete(m_pCloseButton);
}

void CQeust::UIPicking(void)
{

}

RECT CQeust::GetRect(void)
{
	RECT rc = {
		long(m_tInfo.fX - m_tInfo.fCX / 2.f),
		long(m_tInfo.fY - m_tInfo.fCY / 2.f),
		long(m_tInfo.fX + m_tInfo.fCX / 2.f),
		long(m_tInfo.fY - m_tInfo.fCY / 2.f + 20)
	};

	return rc;
}

void CQeust::QeustStart(void)
{
	
}
#include "StdAfx.h"
#include "QuickSlot.h"

CQuickSlot::CQuickSlot(void)
{
}

CQuickSlot::~CQuickSlot(void)
{
}

void CQuickSlot::Initialize(void)
{
	m_strKey = "QuickSlot";
	m_tInfo = INFO(0, 0, 140.f, 80.f);
}

void CQuickSlot::Progress(DWORD _delta)
{
	
}

void CQuickSlot::Render(HDC hdc)
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

void CQuickSlot::Release(void)
{

}

RECT CQuickSlot::GetRect(void)
{
	RECT	rc = {

		int(m_tInfo.fX - m_tInfo.fCX / 2.f),
		int(m_tInfo.fY - m_tInfo.fCY / 2.f),
		int(m_tInfo.fX + m_tInfo.fCX / 2.f),
		int(m_tInfo.fY + m_tInfo.fCY / 2.f)
	};

	return rc;
}

void CQuickSlot::UIPicking(void)
{
}
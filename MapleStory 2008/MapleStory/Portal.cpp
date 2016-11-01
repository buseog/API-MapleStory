#include "StdAfx.h"
#include "Portal.h"

CPortal::CPortal(void)
{
}

CPortal::CPortal(string _strKey)
:m_iPortal(0)
{
}

CPortal::~CPortal(void)
{
}

void CPortal::Initialize(void)
{
	if (m_strKey == "Portal")
	{
		m_tInfo = INFO(0, 0, 89.f, 137.f);
		m_tSprite = SPRITE(0, 8, 0, 60);
	}
}

void CPortal::Progress(DWORD _delta)
{
	if (m_dwTime + m_tSprite.dwTime < GetTickCount())
	{
		m_dwTime = GetTickCount();

		++m_tSprite.iStart;
	}

	if (m_tSprite.iStart >= m_tSprite.iLast)
	{
		m_tSprite.iStart = 0;
	}
}

void CPortal::Render(HDC hdc)
{
	TransparentBlt(hdc,
		int(m_tInfo.fX - m_tInfo.fCX / 2.f + m_ptScroll.x),
		int(m_tInfo.fY - m_tInfo.fCY / 2.f + m_ptScroll.y),
		int(m_tInfo.fCX),
		int(m_tInfo.fCY),
		(*m_pBitMap)[m_strKey]->GetMemdc(),
		int(m_tInfo.fCX * m_tSprite.iStart),
		int(m_tInfo.fCY * m_tSprite.iMotion),
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY,
		RGB(255, 255, 250));
}

void CPortal::Release(void)
{
	
}

SCENEID CPortal::GetPortal(void)
{
	SCENEID eStage;

	switch (m_iPortal)
	{
	case 1:
		eStage = SC_VILLAGE;
		break;

	case 2:
		eStage = SC_STAGE1;
		break;

	case 3:
		eStage = SC_STAGE2;
		break;

	case 4:
		eStage = SC_BOSS;
		break;
	}

	return eStage;
}

void CPortal::SetPortal(int _iPortal)
{
	m_iPortal = _iPortal;
}
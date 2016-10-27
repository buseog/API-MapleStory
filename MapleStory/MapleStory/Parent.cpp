#include "StdAfx.h"
#include "Parent.h"

map<string, CBitBmp*>*		CParent::m_pBitMap = NULL;

CParent::CParent(void)
:m_fScrollX(0)
,m_fScrollY(0)
,m_fJpower(0)
,m_bLand(true)
{
}

CParent::~CParent(void)
{
}

INFO CParent::GetInfo(void)
{
	return m_tInfo;
}

STAT CParent::GetStat(void)
{
	return m_tStat;
}

void CParent::SetPos(float _fX, float _fY)
{
	m_tInfo.fX = _fX;
	m_tInfo.fY = _fY;
}

void CParent::SetBitMap(map<string, CBitBmp*>* _pBitMap)
{
	m_pBitMap = _pBitMap;
}

void CParent::SetBmpKey(string _BmpKey)
{
	m_BmpKey = _BmpKey;
}

void CParent::Gravity(void)
{
	if (m_bLand == true)
	{
	}
	else
	{
		if (m_tInfo.fY >= WINCY + m_fScrollY)
		{
			m_tInfo.fY = WINCY + m_fScrollY - 50;
			m_fJpower = 0;
			m_bLand = true;
		}

		m_fJpower += 0.5f;
		m_tInfo.fY += m_fJpower + m_fScrollY;
	}
}

RECT CParent::GetRect(void)
{
	RECT	rc = {

		int(m_tInfo.fX - m_tInfo.fCX / 2.f),
		int(m_tInfo.fY - m_tInfo.fCY / 2.f),
		int(m_tInfo.fX + m_tInfo.fCX / 2.f),
		int(m_tInfo.fY + m_tInfo.fCY / 2.f)
	};

	return rc;
}
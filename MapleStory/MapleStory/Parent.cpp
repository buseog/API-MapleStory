#include "StdAfx.h"
#include "Parent.h"

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

void CParent::Gravity(void)
{
	if (m_bLand == true)
	{
	}
	else
	{
		if (m_tInfo.fY >= WINCY)
		{
			m_tInfo.fY = WINCY - 50;
			m_fJpower = 0;
			m_bLand = true;
		}

		m_fJpower += 0.3f;
		m_tInfo.fY += m_fJpower;


	}
}
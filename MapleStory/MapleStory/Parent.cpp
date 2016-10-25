#include "StdAfx.h"
#include "Parent.h"

CParent::CParent(void)
:m_fScrollX(0),
m_fScrollY(0)
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

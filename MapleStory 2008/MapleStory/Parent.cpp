#include "StdAfx.h"
#include "Parent.h"

map<string, CBitBmp*>*		CParent::m_pBitMap = NULL;
POINT CParent::m_ptScroll = {};

CParent::CParent(void)
:m_fJpower(0)
,m_fGravity(7.f)
,m_bLand(true)
,m_iDrawID(0)
,m_dwTime(0)
,m_dwKey(0)
,m_dwState(0)
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

SPRITE	CParent::GetSprite(void)
{
	return m_tSprite;
}

void	CParent::SetLand(bool YN)
{
	m_bLand = YN;
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

void CParent::SetStrKey(string _strKey)
{
	m_strKey = _strKey;
}

void CParent::Gravity(void)
{
	if (m_bLand == true)
	{
		m_fJpower = m_fGravity;
	}

	else
	{
		m_fJpower += 0.5f;
	}
	
	m_tInfo.fY += m_fJpower;
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

POINT CParent::GetScroll(void)
{
	return m_ptScroll;
}
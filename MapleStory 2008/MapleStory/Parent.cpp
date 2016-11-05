#include "StdAfx.h"
#include "Parent.h"
#include "Item.h"

POINT CParent::m_ptScroll;
map<string, CBitBmp*>*		CParent::m_pBitMap;

CParent::CParent(void)
:m_fJpower(0)
,m_fGravity(10.f)
,m_bLand(true)
,m_bDestroy(false)
,m_bUnbeatable(false)
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

string	CParent::GetStrKey(void)
{
	return m_strKey;
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
		m_fJpower += 0.6f;
	}

	if (m_dwState != ST_UP)
	{
		m_tInfo.fY += m_fJpower;
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

POINT CParent::GetScroll(void)
{
	return m_ptScroll;
}

bool CParent::GetDestroy(void)
{
	return m_bDestroy;
}

bool CParent::GetUnbeatable(void)
{
	return m_bUnbeatable;
}

DWORD CParent::GetState(void)
{
	return m_dwState;
}

void	CParent::SetDestroy(bool _YN)
{
	m_bDestroy = _YN;
}

void	CParent::SetDamage(float _fDamage)
{
	m_tStat.fHp -= _fDamage;
}

void	CParent::SetUnbeatable(bool _YN)
{
	m_bUnbeatable = _YN;
}

void	CParent::SetScroll(float _fX, float _fY)
{
	m_ptScroll.x = (long)_fX;
	m_ptScroll.y = (long)_fY;
}

float	CParent::GetJumpPower(void)
{
	return m_fJpower;
}


void CParent::SetState(DWORD _dwState)
{
	m_dwState = _dwState;
}

void CParent::SetExp(float _fExp)
{
	m_tStat.fExp += _fExp;
}

void CParent::SetLevel(void)
{
	m_tStat.fAttack += 50.f;
	m_tStat.iLevel += 1;
	m_tStat.fDefense += 10.f;
	m_tStat.fFullHp += 100.f;
	m_tStat.fHp = m_tStat.fFullHp;
	
	m_tStat.fExp = 0.f;
}

void CParent::HavePotion(CItem* _pPotion)
{
	m_tStat.fHp += _pPotion->GetItem().iOption;
	if (_pPotion->GetItem().strName.c_str() == L"HPPotion")
	{
		
		m_tStat.fHp += _pPotion->GetItem().iOption;
	}

	if (m_tStat.fHp >= m_tStat.fFullHp)
		m_tStat.fHp = m_tStat.fFullHp;
}

void CParent::SetGold(int _iGold)
{
	m_tStat.iGold += _iGold;
}
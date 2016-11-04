#include "StdAfx.h"
#include "Item.h"

map<string, CBitBmp*>*		CItem::m_pBitMap = NULL;

CItem::CItem(void)
{
}

CItem::CItem(string _strName, int _iOption, int _iCount, int _iPrice, int _iType)
:m_tItem(_strName, _iOption, _iCount, _iPrice, _iType)
,m_DrawId(0)
{

}

CItem::~CItem(void)
{
}

INFO CItem::GetInfo(void)
{
	return m_tInfo;
}


ITEM CItem::GetItem(void)
{
	return m_tItem;
}

RECT CItem::GetRect(void)
{
	RECT rc = {
		long(m_tInfo.fX - m_tInfo.fCX / 2.f),
		long(m_tInfo.fY - m_tInfo.fCY / 2.f),
		long(m_tInfo.fX + m_tInfo.fCX / 2.f),
		long(m_tInfo.fY + m_tInfo.fCY / 2.f)
	};

	return rc;
}

DWORD CItem::GetDraw(void)
{
	return m_DrawId;
}

void CItem::SetPos(float _fX, float _fY)
{
	m_tInfo.fX = _fX;
	m_tInfo.fY = _fY;
}

void CItem::SetBitMap(map<string, CBitBmp*>* _pBitMap)
{
	m_pBitMap = _pBitMap;
}

void CItem::Status(HDC hdc)
{
}
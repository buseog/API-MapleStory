#include "StdAfx.h"
#include "Item.h"

CItem::CItem(void)
{
}

CItem::CItem(int _iAttack, int _iDeffense, int _iCount, int _iPrice, int _iType)
:m_tItem(_iAttack, _iDeffense, _iCount, _iPrice, _iType)
{

}

CItem::~CItem(void)
{
}

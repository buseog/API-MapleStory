#include "StdAfx.h"
#include "ItemEmpty.h"

CItemEmpty::CItemEmpty(void)
{
	m_tInfo = INFO(0, 0, 32.f, 32.f);
	m_tItem.iType = IT_EMPTY;
}

CItemEmpty::~CItemEmpty(void)
{
}


void CItemEmpty::Initialize(void)
{
}

void CItemEmpty::Progress(DWORD _delta)
{
}

void CItemEmpty::Render(HDC hdc)
{
}

void CItemEmpty::Release(void)
{

}
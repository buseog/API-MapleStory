#include "StdAfx.h"
#include "Gold.h"

CGold::CGold(void)
{
}
CGold::CGold(wstring _strName, int _iOption, int _iCount, int _iPrice, int _iType)
:CItem(_strName, _iOption, _iCount, _iPrice, _iType)
{
	Initialize();
}
CGold::~CGold(void)
{
}

void CGold::Initialize(void)
{
	m_dwTime = GetTickCount();
	m_tInfo = INFO(0, 0, 32.f, 32.f);
	m_tSprite = SPRITE(0, 4, 0, 90);
	m_DropId = 1;
}

void CGold::Progress(DWORD _delta)
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

	if (m_DropId == 1)
	{
		m_tInfo.fY += 5.f;
	}
}

void CGold::Render(HDC hdc)
{
	string str;

	str.assign(m_tItem.strName.begin(), m_tItem.strName.end());

	if (m_DropId == 1)
	{
		TransparentBlt(hdc,
			int(m_tInfo.fX - m_tInfo.fCX / 2.f + CParent::m_ptScroll.x),
			int(m_tInfo.fY - m_tInfo.fCY / 2.f + CParent::m_ptScroll.y),
			int(m_tInfo.fCX),
			int(m_tInfo.fCY),
			(*m_pBitMap)[str]->GetMemdc(),
			int(m_tInfo.fCX * m_tSprite.iStart), 
			int(m_tInfo.fCY * m_tSprite.iMotion),
			(int)m_tInfo.fCX, 
			(int)m_tInfo.fCY,
			RGB(255, 255, 250));
	}
}

void CGold::Release(void)
{

}
#include "StdAfx.h"
#include "NPC.h"
#include "Parent.h"

CNPC::CNPC(void)
{
}


CNPC::~CNPC(void)
{
	Release();
}

void CNPC::Initialize(void)
{
	m_pBit = (new CBitBmp)->LoadBmp(L"../Texture/NPC.bmp");
	m_tInfo = INFO(580.f, 560.f, 68.f, 56.f);
	m_tSprite = SPRITE(0, 16, 0, 80);
	m_dwTime = GetTickCount();
}

void CNPC::Progress(DWORD _delta)
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

	if(PtInRect(&GetRect(), GetMouse()))
	{
		if (GetAsyncKeyState(VK_LBUTTON))
		{

		}
	}
}

void CNPC::Render(HDC hdc)
{
	TransparentBlt(hdc,
		int(m_tInfo.fX - m_tInfo.fCX / 2.f + CParent::m_ptScroll.x),
		int(m_tInfo.fY - m_tInfo.fCY / 2.f + CParent::m_ptScroll.y),
		int(m_tInfo.fCX), 
		int(m_tInfo.fCY), 
		m_pBit->GetMemdc(),
		int(m_tInfo.fCX * m_tSprite.iStart), 
		int(m_tInfo.fCY * m_tSprite.iMotion),
		(int)m_tInfo.fCX, 
		(int)m_tInfo.fCY, 
		RGB(255, 255, 250));
}

void CNPC::Release(void)
{
	::Safe_Delete(m_pBit);
}

RECT CNPC::GetRect(void)
{
	RECT rc = {
		long(m_tInfo.fX - m_tInfo.fCX / 2.f),
		long(m_tInfo.fY - m_tInfo.fCY / 2.f),
		long(m_tInfo.fX + m_tInfo.fCX / 2.f),
		long(m_tInfo.fY + m_tInfo.fCY / 2.f)};

	return rc;
}
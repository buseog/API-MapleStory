#include "StdAfx.h"
#include "NPC.h"
#include "Parent.h"
#include "Store.h"
#include "Factory.h"

CNPC::CNPC(void)
:m_pStore(NULL)
{
}


CNPC::~CNPC(void)
{
	Release();
}

void CNPC::Initialize(void)
{
	m_pStore = CFactory<CStore>::CreateUI(400.f, 300.f, "Store");
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
			m_pStore->SetOnOff(true);
		}
	}


	if (m_pStore->GetOnOff())
		m_pStore->Progress(_delta);
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

	if (m_pStore->GetOnOff())
		m_pStore->Render(hdc);
}

void CNPC::Release(void)
{
	::Safe_Delete(m_pBit);
}

RECT CNPC::GetRect(void)
{
	RECT rc = {
		long(m_tInfo.fX + CParent::m_ptScroll.x - 50),
		long(m_tInfo.fY + CParent::m_ptScroll.y - 50),
		long(m_tInfo.fX + CParent::m_ptScroll.x + 90),
		long(m_tInfo.fY + CParent::m_ptScroll.y + 50)};

	return rc;
}
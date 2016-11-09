#include "StdAfx.h"
#include "NPC.h"
#include "Parent.h"
#include "Store.h"
#include "Factory.h"
#include "Qeust.h"

CNPC::CNPC(void)
:m_pUI(NULL)
{
}

CNPC::CNPC(string _strKey)
:m_pUI(NULL)
,m_strKey(_strKey)
{
	m_dwTime = GetTickCount();
	m_bDrag = false;
}

CNPC::~CNPC(void)
{
	Release();
}

void CNPC::Initialize(void)
{
	if (m_strKey == "Store_NPC")
	{
		m_pUI = CFactory<CStore>::CreateUI(400.f, 270.f, "Store");
		m_pBit = (new CBitBmp)->LoadBmp(L"../Texture/Store_NPC.bmp");
		m_tInfo = INFO(580.f, 560.f, 68.f, 56.f);
		m_tSprite = SPRITE(0, 16, 0, 80);
	}
	else if (m_strKey == "Quest_Npc")
	{
		m_pUI = CFactory<CQuest>::CreateUI(400.f, 250.f, "Quest");
		m_pBit = (new CBitBmp)->LoadBmp(L"../Texture/Quest_Npc.bmp");
		m_tInfo = INFO(750.f, 550.f, 69.f, 89.f);
		m_tSprite = SPRITE(0, 30, 0, 80);
	}
	
}

void CNPC::Progress(DWORD _delta)
{
	if (m_dwTime + 30 <= GetTickCount())
	{
		UIPicking();
		m_dwTime = GetTickCount();
	}

	if (m_pUI->GetOnOff())
		m_pUI->Progress(_delta);

	if (m_dwTime + m_tSprite.dwTime < GetTickCount())
	{
		m_dwTime = GetTickCount();

		++m_tSprite.iStart;
	}

	if (m_tSprite.iStart >= m_tSprite.iLast)
	{
		m_tSprite.iStart = 0;
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

	if (m_pUI->GetOnOff())
		m_pUI->Render(hdc);
}

void CNPC::Release(void)
{
	::Safe_Delete(m_pBit);
	::Safe_Delete(m_pUI);
}

RECT CNPC::GetRect(void)
{
	RECT rc = {
		long(m_tInfo.fX - m_tInfo.fCX / 2.f + CParent::m_ptScroll.x),
		long(m_tInfo.fY - m_tInfo.fCY / 2.f + CParent::m_ptScroll.y),
		long(m_tInfo.fX + m_tInfo.fCX / 2.f + CParent::m_ptScroll.x),
		long(m_tInfo.fY + m_tInfo.fCY / 2.f + CParent::m_ptScroll.y)};

	return rc;
}

void CNPC::SetInventory(CUI* _pInventory)
{
	if (m_strKey == "Store_NPC")
		((CStore*)m_pUI)->SetInventory(_pInventory);

	else
		((CQuest*)m_pUI)->SetInventory(_pInventory);
}

void CNPC::UIPicking(void)
{
	float fX = float(GetMouse().x - m_prevPT.x);
	float fY = float(GetMouse().y - m_prevPT.y);


	if(m_bDrag)
	{
		m_pUI->SetPos(m_pUI->GetInfo().fX + fX, m_pUI->GetInfo().fY + fY);
	}

	if (m_pUI->GetOnOff())
	{
		if (GetAsyncKeyState(VK_LBUTTON))
		{
			if(PtInRect(&m_pUI->GetRect(), GetMouse()))
			{
				m_prevPT = GetMouse();
				m_bDrag = true;
			}
		}
		else
		{
			m_bDrag = false;
		}
	}

	
	if(PtInRect(&GetRect(), GetMouse()))
	{
		if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
		{
			if (m_strKey == "Store_NPC")
			{
				m_pUI->SetOnOff(true);
			}
			else if (m_strKey == "Quest_Npc")
			{
				m_pUI->SetOnOff(true);
			}	
		}
	}
}
#include "StdAfx.h"
#include "Equipment.h"

CEquipment::CEquipment(void)
{
	for (int i = 0; i < EQ_END; ++i)
	{
		m_pEquipItem[i] = NULL;
	}
}

CEquipment::~CEquipment(void)
{
}

void CEquipment::Initialize(void)
{
	m_bMouse = false;
	m_strKey = "Equipment";
	m_tInfo = INFO(0, 0, 237.f, 332.f);
}

void CEquipment::Progress(DWORD _delta)
{
	float fX = float(GetMouse().x - m_prevPT.x);
	float fY = float(GetMouse().y - m_prevPT.y);
	
	if(m_bMouse)
	{
		m_tInfo.fX += fX;
		m_tInfo.fY += fY;
	}

	if(PtInRect(&GetRect(), GetMouse()))
	{
		if(GetAsyncKeyState(VK_LBUTTON))
		{
			m_prevPT = GetMouse();
			m_bMouse = true;
		}
		else
			m_bMouse = false;
	}
	else
		m_bMouse = false;
}

void CEquipment::Render(HDC hdc)
{
	BitBlt(hdc,
		int(m_tInfo.fX - m_tInfo.fCX / 2.f),
		int(m_tInfo.fY - m_tInfo.fCY / 2.f),
		int(m_tInfo.fCX),
		int(m_tInfo.fCY),
		(*m_pBitMap)[m_strKey]->GetMemdc(),
		0,
		0,
		SRCCOPY);
}

void CEquipment::Release(void)
{

}
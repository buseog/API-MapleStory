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
	m_strKey = "Equipment";
	m_tInfo = INFO(0, 0, 237.f, 332.f);
}

void CEquipment::Progress(DWORD _delta)
{
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

void CEquipment::EquipItem(CItem*	_pItem)
{

}

RECT CEquipment::GetRect(void)
{
	RECT	rc = {

		int(m_tInfo.fX - m_tInfo.fCX / 2.f),
		int(m_tInfo.fY - m_tInfo.fCY / 2.f),
		int(m_tInfo.fX + m_tInfo.fCX / 2.f),
		int(m_tInfo.fY - m_tInfo.fCY / 2.f + 20)
	};

	return rc;
}
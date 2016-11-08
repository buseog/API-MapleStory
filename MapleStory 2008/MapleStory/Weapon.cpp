#include "StdAfx.h"
#include "Weapon.h"

CWeapon::CWeapon(void)
{
}

CWeapon::CWeapon(wstring _strName, int _iOption, int _iCount, int _iPrice, int _iType)
:CItem(_strName, _iOption, _iCount, _iPrice, _iType)
{
	Initialize();
}

CWeapon::CWeapon(const CItem &_Item) :CItem(_Item)
{
}

CWeapon::~CWeapon(void)
{
	Release();
}

void CWeapon::Initialize(void)
{
	m_tInfo = INFO(0, 0, 32.f, 32.f);
}

void CWeapon::Progress(DWORD _delta)
{
	if (m_DropId == 1)
	{
		m_tInfo.fY += 5.f;
	}

	if(PtInRect(&GetRect(), GetMouse()))
	{
		m_DrawId = 1;
	}
	else
		m_DrawId = 0;

}
void CWeapon::Render(HDC hdc)
{
	string str;

	str.assign(m_tItem.strName.begin(), m_tItem.strName.end());

	if (m_DropId == 0)
	{
		TransparentBlt(hdc,
			int(m_tInfo.fX - m_tInfo.fCX / 2.f),
			int(m_tInfo.fY - m_tInfo.fCY / 2.f),
			int(m_tInfo.fCX),
			int(m_tInfo.fCY),
			(*m_pBitMap)[str]->GetMemdc(),
			0,
			0,
			(int)m_tInfo.fCX,
			(int)m_tInfo.fCY,
			RGB(255, 255, 250));
	}
	else if (m_DropId == 1)
	{
		TransparentBlt(hdc,
			int(m_tInfo.fX - m_tInfo.fCX / 2.f + CParent::m_ptScroll.x),
			int(m_tInfo.fY - m_tInfo.fCY / 2.f + CParent::m_ptScroll.y),
			int(m_tInfo.fCX),
			int(m_tInfo.fCY),
			(*m_pBitMap)[str]->GetMemdc(),
			0,
			0,
			(int)m_tInfo.fCX,
			(int)m_tInfo.fCY,
			RGB(255, 255, 250));
	}

	if (m_DrawId == 1)
	{
		BitBlt(hdc,
		int(m_tInfo.fX - m_tInfo.fCX / 2.f + 30),
		int(m_tInfo.fY - m_tInfo.fCY / 2.f + 30),
		150,
		120,
		(*m_pBitMap)["ItemStat"]->GetMemdc(),
		0,
		0,
		SRCCOPY);

		TCHAR szName[128] = L"";
		TCHAR szOption[128] = L"";
		TCHAR szPrice[128] = L"";

		wsprintf(szName, L"이름 : %s", m_tItem.strName.c_str());
					TextOut(hdc,
						int(m_tInfo.fX + 30), int(m_tInfo.fY + 30),
						szName, lstrlen(szName));

		wsprintf(szOption, L"공격력 : %d", (int)m_tItem.iOption);
					TextOut(hdc, 
						int(m_tInfo.fX + 30), int(m_tInfo.fY + 45),
						szOption, lstrlen(szOption));

		wsprintf(szPrice, L"가격 : %d", (int)m_tItem.iPrice);
					TextOut(hdc, 
						int(m_tInfo.fX + 30), int(m_tInfo.fY + 60),
						szPrice, lstrlen(szPrice));

		if (m_tItem.iType == IT_WEAPON)
		{
			TextOut(hdc, int(m_tInfo.fX + 30), int(m_tInfo.fY + 75),	L"종류 : 무기", 7);
		}
		if (m_tItem.iType == IT_ARMOR)
		{
			TextOut(hdc, int(m_tInfo.fX + 30), int(m_tInfo.fY + 75),	L"종류 : 방어구", 8);
		}
		if (m_tItem.iType == IT_POTION)
		{
			TextOut(hdc, int(m_tInfo.fX + 30), int(m_tInfo.fY + 75),	L"종류 : 포션", 7);
		}

		SetBkMode((*m_pBitMap)["Back"]->GetMemdc(),TRANSPARENT);
	}
}
void CWeapon::Release(void)
{

}

void CWeapon::Status(HDC hdc)
{
}
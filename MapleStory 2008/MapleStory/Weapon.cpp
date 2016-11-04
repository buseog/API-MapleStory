#include "StdAfx.h"
#include "Weapon.h"

CWeapon::CWeapon(void)
{
}

CWeapon::CWeapon(string _strName, int _iOption, int _iCount, int _iPrice, int _iType)
:CItem(_strName, _iOption, _iCount, _iPrice, _iType)
{
	Initialize();
}

CWeapon::~CWeapon(void)
{
	Release();
}

void CWeapon::Initialize(void)
{
	m_tInfo = INFO(0, 0, 30.f, 30.f);
}
void CWeapon::Progress(DWORD _delta)
{
	if(PtInRect(&GetRect(), GetMouse()))
	{
		m_DrawId = 1;
	}
	else
		m_DrawId = 0;

}
void CWeapon::Render(HDC hdc)
{
	TransparentBlt(hdc,
		int(m_tInfo.fX - m_tInfo.fCX / 2.f),
		int(m_tInfo.fY - m_tInfo.fCY / 2.f),
		int(m_tInfo.fCX),
		int(m_tInfo.fCY),
		(*m_pBitMap)["Weapon"]->GetMemdc(),
		0,
		0,
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY,
		RGB(255, 255, 250));

	if (m_DrawId == 1)
	{
		TCHAR szName[128] = L"";
		TCHAR szOption[128] = L"";
		TCHAR szPrice[128] = L"";
		TCHAR szType[128] = L"";


		wsprintf(szOption, L"%d", (int)(LPCWSTR)m_tItem.m_strName.c_str());
					TextOut(hdc, 
					m_tInfo.fX + 30, m_tInfo.fY + 30,
					szName, lstrlen(szName));

		wsprintf(szOption, L"%d", (int)m_tItem.m_iOption);
					TextOut(hdc, 
						m_tInfo.fX + 30, m_tInfo.fY + 45,
						szOption, lstrlen(szOption));



		wsprintf(szPrice, L"%d", (int)m_tItem.m_iPrice);
					TextOut(hdc, 
							m_tInfo.fX + 30, m_tInfo.fY + 60,
						szPrice, lstrlen(szPrice));

		wsprintf(szType, L"%d", (int)m_tItem.m_iType);
					TextOut(hdc, 
							m_tInfo.fX + 30, m_tInfo.fY + 75,
						szType, lstrlen(szType));
	}
}
void CWeapon::Release(void)
{

}

void CWeapon::Status(HDC hdc)
{
}
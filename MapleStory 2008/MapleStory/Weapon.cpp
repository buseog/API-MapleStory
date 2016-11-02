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
}

void CWeapon::Initialize(void)
{
	m_tInfo = INFO(0, 0, 30.f, 30.f);
}
void CWeapon::Progress(DWORD _delta)
{
	
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
}
void CWeapon::Release(void)
{

}
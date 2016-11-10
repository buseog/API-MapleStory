#include "StdAfx.h"
#include "Icon.h"
#include "Parent.h"

CIcon::CIcon(void)
{
}

CIcon::CIcon(ICONID _eID, string _strName)
:m_eID(_eID)
,m_strKey(_strName)
,m_pBit(NULL)
,m_fCoolTime(1)
{
	m_dwTime = GetTickCount();
	m_tInfo = INFO(0.f, 0.f, 32.f, 32.f);
}

CIcon::CIcon(const CIcon &_Icon)
{
	m_tInfo.fX = _Icon.m_tInfo.fX;
	m_tInfo.fY = _Icon.m_tInfo.fY;
	m_tInfo.fCX = _Icon.m_tInfo.fCX;
	m_tInfo.fCY = _Icon.m_tInfo.fCY;
	m_fCoolTime = _Icon.m_fCoolTime;
	m_eID = _Icon.m_eID;
	m_strKey = _Icon.m_strKey;

	switch (m_eID)
	{
	case IC_SKILL:
		if (m_strKey == "Typhoon_ON")
		{
			m_pBit = (new CBitBmp)->LoadBmp(L"../Texture/Skill/Icon/Typhoon_ON.bmp");
			m_fTime = 1500.f;
		}
		else if (m_strKey == "Bolt_ON")
		{
			m_pBit = (new CBitBmp)->LoadBmp(L"../Texture/Skill/Icon/Bolt_ON.bmp");
			m_fTime = 3000.f;
		}
		else if (m_strKey == "Beyond_ON")
		{
			m_pBit = (new CBitBmp)->LoadBmp(L"../Texture/Skill/Icon/Beyond_ON.bmp");
			m_fTime = 100.f;
		}
		else if (m_strKey == "Annihilation_ON")
		{
			m_pBit = (new CBitBmp)->LoadBmp(L"../Texture/Skill/Icon/Annihilation_ON.bmp");
			m_fTime = 800.f;
		}
		else if (m_strKey == "Range_ON")
		{
			m_pBit = (new CBitBmp)->LoadBmp(L"../Texture/Skill/Icon/Range_ON.bmp");
			m_fTime = 5000.f;
		}

		if (m_strKey == "Typhoon_OFF")
		{
			m_pBit = (new CBitBmp)->LoadBmp(L"../Texture/Skill/Icon/Typhoon_OFF.bmp");
		}
		else if (m_strKey == "Bolt_OFF")
		{
			m_pBit = (new CBitBmp)->LoadBmp(L"../Texture/Skill/Icon/Bolt_OFF.bmp");
		}
		else if (m_strKey == "Beyond_OFF")
		{
			m_pBit = (new CBitBmp)->LoadBmp(L"../Texture/Skill/Icon/Beyond_OFF.bmp");
		}
		else if (m_strKey == "Annihilation_OFF")
		{
			m_pBit = (new CBitBmp)->LoadBmp(L"../Texture/Skill/Icon/Annihilation_OFF.bmp");
		}
		else if (m_strKey == "Range_OFF")
		{
			m_pBit = (new CBitBmp)->LoadBmp(L"../Texture/Skill/Icon/Range_OFF.bmp");
		}
		break;

	case IC_ITEM:
		break;
	}
}

CIcon::~CIcon(void)
{
	Release();
}

void	CIcon::Initialize(void)
{
	switch (m_eID)
	{
	case IC_SKILL:
		if (m_strKey == "Typhoon_ON")
		{
			m_pBit = (new CBitBmp)->LoadBmp(L"../Texture/Skill/Icon/Typhoon_ON.bmp");
			m_fTime = 1500.f;
		}
		else if (m_strKey == "Bolt_ON")
		{
			m_pBit = (new CBitBmp)->LoadBmp(L"../Texture/Skill/Icon/Bolt_ON.bmp");
			m_fTime = 3000.f;
		}
		else if (m_strKey == "Beyond_ON")
		{
			m_pBit = (new CBitBmp)->LoadBmp(L"../Texture/Skill/Icon/Beyond_ON.bmp");
			m_fTime = 100.f;
		}
		else if (m_strKey == "Annihilation_ON")
		{
			m_pBit = (new CBitBmp)->LoadBmp(L"../Texture/Skill/Icon/Annihilation_ON.bmp");
			m_fTime = 800.f;
		}
		else if (m_strKey == "Range_ON")
		{
			m_pBit = (new CBitBmp)->LoadBmp(L"../Texture/Skill/Icon/Range_ON.bmp");
			m_fTime = 5000.f;
		}

		if (m_strKey == "Typhoon_OFF")
		{
			m_pBit = (new CBitBmp)->LoadBmp(L"../Texture/Skill/Icon/Typhoon_OFF.bmp");
		}
		else if (m_strKey == "Bolt_OFF")
		{
			m_pBit = (new CBitBmp)->LoadBmp(L"../Texture/Skill/Icon/Bolt_OFF.bmp");
		}
		else if (m_strKey == "Beyond_OFF")
		{
			m_pBit = (new CBitBmp)->LoadBmp(L"../Texture/Skill/Icon/Beyond_OFF.bmp");
		}
		else if (m_strKey == "Annihilation_OFF")
		{
			m_pBit = (new CBitBmp)->LoadBmp(L"../Texture/Skill/Icon/Annihilation_OFF.bmp");
		}
		else if (m_strKey == "Range_OFF")
		{
			m_pBit = (new CBitBmp)->LoadBmp(L"../Texture/Skill/Icon/Range_OFF.bmp");
		}
		break;

	case IC_ITEM:
		break;
	}

}
void	CIcon::Progress(DWORD _dwDelta)
{
}
void	CIcon::Render(HDC hdc)
{
	if (m_strKey == "Empty")
	{

	}
	else
	{
	TransparentBlt(hdc,
			int(m_tInfo.fX - m_tInfo.fCX / 2.f),
			int(m_tInfo.fY - m_tInfo.fCY / 2.f),
			int(m_tInfo.fCX),
			int(m_tInfo.fCY * m_fCoolTime), 
			m_pBit->GetMemdc(),
			0,
			0,
			(int)m_tInfo.fCX, 
			int(m_tInfo.fCY * m_fCoolTime),
			RGB(255, 255, 250));
	}
}
void	CIcon::Release(void)
{
	::Safe_Delete(m_pBit);
}

void	CIcon::SetPos(float _fX, float _fY)
{
	m_tInfo.fX = _fX;
	m_tInfo.fY = _fY;
}

void	CIcon::Picking(void)
{
	
}

INFO	CIcon::GetInfo(void)
{
	return m_tInfo;
}

RECT CIcon::GetRect(void)
{
	RECT rc = {
		long(m_tInfo.fX - m_tInfo.fCX / 2.f),
		long(m_tInfo.fY - m_tInfo.fCY / 2.f),
		long(m_tInfo.fX + m_tInfo.fCX / 2.f),
		long(m_tInfo.fY + m_tInfo.fCY / 2.f)
	};

	return rc;
}

string CIcon::GetStrKey(void)
{
	return m_strKey;
}

void CIcon::SetCoolTime(float _fCool)
{
	m_fCoolTime = _fCool;
}

float CIcon::GetTime(void)
{
	return m_fTime;
}
#include "StdAfx.h"
#include "UI.h"

map<string, CBitBmp*>*		CUI::m_pBitMap = NULL;

CUI::CUI(void)
{
}

CUI::CUI(string _strKey)
:m_strKey(_strKey)
,m_iDrawID(0)
,m_dwTime(0)
{

}

CUI::~CUI(void)
{
}

void CUI::Initialize(void)
{
	if (m_strKey == "UI")
	{
		m_tInfo = INFO(0, 0, 800.f, 600.f);
		m_tSprite = SPRITE(0, 0, 0, 0);
	}

	//if (m_strKey == "Inventory")
	//{
	//	m_tInfo = INFO(0, 0, 172.f, 335.f);
	//	m_tSprite = SPRITE(0, 0, 0, 0);
	//}

	if (m_strKey == "Equipment")
	{
		m_tInfo = INFO(0, 0, 237.f, 332.f);
		m_tSprite = SPRITE(0, 0, 0, 0);
	}

	if (m_strKey == "Skill")
	{
		m_tInfo = INFO(0, 0, 174.f, 300.f);
		m_tSprite = SPRITE(0, 0, 0, 0);
	}
}

void CUI::Progress(DWORD _delta)
{

}

void CUI::Render(HDC hdc)
{
	if (m_strKey == "UI")
	{
		TransparentBlt(hdc,
			int(m_tInfo.fX - m_tInfo.fCX / 2.f),
			int(m_tInfo.fY - m_tInfo.fCY / 2.f),
			int(m_tInfo.fCX),
			int(m_tInfo.fCY),
			(*m_pBitMap)[m_strKey]->GetMemdc(),
			int(m_tInfo.fCX * m_tSprite.iStart),
			int(m_tInfo.fCY * m_tSprite.iMotion),
			(int)m_tInfo.fCX,
			(int)m_tInfo.fCY,
			RGB(255, 255, 250));
	}

	else if (m_strKey == "Inventory" || m_strKey == "Equipment" || m_strKey == "Skill")
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
}

void CUI::Release(void)
{
	
}

void	CUI::SetPos(float _fX, float _fY)
{
	m_tInfo.fX = _fX;
	m_tInfo.fY = _fY;
}


RECT CUI::GetRect(void)
{
	RECT	rc = {

		int(m_tInfo.fX - m_tInfo.fCX / 2.f),
		int(m_tInfo.fY - m_tInfo.fCY / 2.f),
		int(m_tInfo.fX + m_tInfo.fCX / 2.f),
		int(m_tInfo.fY + m_tInfo.fCY / 2.f)
	};

	return rc;
}

void CUI::SetBitMap(map<string, CBitBmp*>* _pBitMap)
{
	m_pBitMap = _pBitMap;
}

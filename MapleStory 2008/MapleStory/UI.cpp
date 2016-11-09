#include "StdAfx.h"
#include "UI.h"

map<string, CBitBmp*>*		CUI::m_pBitMap;
CParent*					CUI::m_pPlayer;

CUI::CUI(void)
{
}

CUI::CUI(string _strKey)
:m_strKey(_strKey)
,m_iDrawID(0)
,m_dwTime(0)
,m_ReturnItem(NULL)
,m_pCloseButton(NULL)
,m_bOnOff(true)
,m_iPriority(0)
{
	m_fPercent[0] = 100.f;
	m_fPercent[1] = 0.f;
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

	if (m_strKey == "Close")
	{
		m_tInfo = INFO(0.f, 0.f, 15.f, 15.f);
	}

	if (m_strKey == "HPBar" || m_strKey == "MPBar")
	{
		m_tInfo = INFO(100, 500, 141.f, 14.f);
	}

	if (m_strKey == "EXPBar")
	{
		m_tInfo = INFO(100, 500, 310.f, 14.f);
	}

	if (m_strKey == "Scroll")
	{
		m_tInfo = INFO(0, 0, 9.f, 26.f);
	}
}

void CUI::Progress(DWORD _delta)
{
	m_fPercent[0] = m_pPlayer->GetStat().fHp / m_pPlayer->GetStat().fFullHp;
	m_fPercent[2] = m_pPlayer->GetStat().fExp / (800 * m_pPlayer->GetStat().iLevel);
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

	if (m_strKey == "HPBar")
	{
		BitBlt(hdc,
			int(m_tInfo.fX),
			int(m_tInfo.fY),
			int(m_tInfo.fCX * m_fPercent[0]),
			int(m_tInfo.fCY),
			(*m_pBitMap)[m_strKey]->GetMemdc(),
			0,
			0,
			SRCCOPY);
	}

	if (m_strKey == "MPBar")
	{
		BitBlt(hdc,
			int(m_tInfo.fX),
			int(m_tInfo.fY),
			int(m_tInfo.fCX),
			int(m_tInfo.fCY),
			(*m_pBitMap)[m_strKey]->GetMemdc(),
			0,
			0,
			SRCCOPY);
	}

	if (m_strKey == "EXPBar")
	{
		BitBlt(hdc,
			int(m_tInfo.fX),
			int(m_tInfo.fY),
			int(m_tInfo.fCX * m_fPercent[2]),
			int(m_tInfo.fCY),
			(*m_pBitMap)[m_strKey]->GetMemdc(),
			0,
			0,
			SRCCOPY);
	}

	if (m_strKey == "Close")
	{
		TransparentBlt(hdc,
			int(m_tInfo.fX - m_tInfo.fCX / 2.f),
			int(m_tInfo.fY - m_tInfo.fCY / 2.f),
			int(m_tInfo.fCX),
			int(m_tInfo.fCY),
			(*m_pBitMap)[m_strKey]->GetMemdc(),
			0,
			0,
			(int)m_tInfo.fCX,
			(int)m_tInfo.fCY,
			RGB(255, 255, 250));
	}

	if (m_strKey == "Scroll")
	{
		TransparentBlt(hdc,
			int(m_tInfo.fX - m_tInfo.fCX / 2.f),
			int(m_tInfo.fY - m_tInfo.fCY / 2.f),
			int(m_tInfo.fCX),
			int(m_tInfo.fCY),
			(*m_pBitMap)[m_strKey]->GetMemdc(),
			0,
			0,
			(int)m_tInfo.fCX,
			(int)m_tInfo.fCY,
			RGB(255, 255, 250));
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

INFO CUI::GetInfo(void)
{
	return m_tInfo;
}

void CUI::UIPicking(void)
{
}

CItem* CUI::GetReturnItem(void)
{
	return m_ReturnItem;
}

void CUI::SetReturnItem(void)
{
	m_ReturnItem = NULL;
}


bool CUI::GetOnOff(void)
{
	return m_bOnOff;
}

void CUI::SetOnOff(bool _YN)
{
	m_bOnOff = _YN;
}

void CUI::SetPlayer(CParent* _pPlayer)
{
	m_pPlayer = _pPlayer;
}

void CUI::SetPriority(int _iInput)
{
	m_iPriority = _iInput;
}

int CUI::GetPriority(void)
{
	return m_iPriority;
}
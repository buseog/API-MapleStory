#include "StdAfx.h"
#include "Status.h"
#include "Player.h"

CStatus::CStatus(void)
{
}

CStatus::~CStatus(void)
{
}

void CStatus::Initialize(void)
{
	m_pPlayer = NULL;
	m_strKey = "Status";
	m_tInfo = INFO(0, 0, 212.f, 373.f);
}

void CStatus::Progress(DWORD _delta)
{

}

void CStatus::Render(HDC hdc)
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

	
	TCHAR szName[128] = L"";
	TCHAR szLevel[128] = L"";
	TCHAR szHp[128] = L"";

		wsprintf(szName, L"%s", L"¿ÀºÎ¼®");
		TextOut(hdc, int(m_tInfo.fX - 25), int(m_tInfo.fY - 155), szName, lstrlen(szName));

		wsprintf(szLevel, L"%d", (int)m_pPlayer->GetStat().iLevel);
					TextOut(hdc, 
						int(m_tInfo.fX - 25), int(m_tInfo.fY - 120),
						szLevel, lstrlen(szLevel));

		wsprintf(szHp, L"%d", (int)m_pPlayer->GetStat().fHp);
					TextOut(hdc, 
						int(m_tInfo.fX -25), int(m_tInfo.fY - 30),
						szHp, lstrlen(szHp));

	SetBkMode((*m_pBitMap)["Back"]->GetMemdc(),TRANSPARENT);
}

void CStatus::Release(void)
{

}

RECT CStatus::GetRect(void)
{
	RECT	rc = {
		int(m_tInfo.fX - m_tInfo.fCX / 2.f),
		int(m_tInfo.fY - m_tInfo.fCY / 2.f),
		int(m_tInfo.fX + m_tInfo.fCX / 2.f),
		int(m_tInfo.fY - m_tInfo.fCY / 2.f + 20)
	};

	return rc;
}

void CStatus::UIPicking(void)
{
}

void CStatus::SetPlayer(CParent* _pPlayer)
{
	m_pPlayer = _pPlayer;
}

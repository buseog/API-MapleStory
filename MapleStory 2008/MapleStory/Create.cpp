#include "StdAfx.h"
#include "Create.h"
#include "MyButton.h"
#include "SceneMgr.h"
#include "Factory.h"

CCreate::CCreate(void)
{
}

CCreate::~CCreate(void)
{
	Release();
}

void CCreate::Initialize(void)
{
	m_dwTime2 = GetTickCount();
	m_dwTime = GetTickCount();

	m_bPick = false;
	m_iPick = 0;

	m_BitMap["Back"] = (new CBitBmp)->LoadBmp(L"../Texture/Back.bmp");
	m_BitMap["Create"] = (new CBitBmp)->LoadBmp(L"../Texture/Create.bmp");
	m_BitMap["BackCreate"] = (new CBitBmp)->LoadBmp(L"../Texture/BackCreate.bmp");

	m_BitMap["Player_LEFT"] = (new CBitBmp)->LoadBmp(L"../Texture/Player/Player_LEFT.bmp");
	m_BitMap["Sworder"] = (new CBitBmp)->LoadBmp(L"../Texture/Sworder.bmp");
	m_BitMap["Archer_Left"] = (new CBitBmp)->LoadBmp(L"../Texture/Player/Archer_Left.bmp");
	m_BitMap["NameTag"] = (new CBitBmp)->LoadBmp(L"../Texture/NameTag.bmp");

	m_vecButton.push_back(CreateButton(55.f, 450.f, "BackCreate"));

	m_tSprite1 = SPRITE(0, 5, 0, 80);
	m_tSprite2 = SPRITE(0, 5, 0, 80);

	m_tInfo[0] = INFO(210.f, 510.f, 70.f, 90.f); 
	m_tInfo[1] = INFO(680.f, 510.f, 50.f, 75.f);


	CUI::SetBitMap(&m_BitMap);
}

void CCreate::Progress(DWORD _delta)
{
	UIPicking(_delta);


	if (m_dwTime + m_tSprite1.dwTime < GetTickCount())
	{
		m_dwTime = GetTickCount();

		++m_tSprite1.iStart;
	}

	if (m_tSprite1.iStart >= m_tSprite1.iLast)
	{
		m_tSprite1.iStart = 0;
	}

	if (m_dwTime2 + m_tSprite2.dwTime < GetTickCount())
	{
		m_dwTime2 = GetTickCount();

		++m_tSprite2.iStart;
	}

	if (m_tSprite2.iStart >= m_tSprite2.iLast)
	{
		m_tSprite2.iStart = 0;
	}


}

void CCreate::Render(HDC hdc)
{
	BitBlt(m_BitMap["Back"]->GetMemdc(), 
		0, 0, 
		WINCX, WINCY, 
		m_BitMap["Create"]->GetMemdc(), 
		0, 0, SRCCOPY);

	SetBkMode(m_BitMap["Back"]->GetMemdc(),TRANSPARENT);

	TCHAR szBuf[128] = L"";
	TCHAR szBuf2[128] = L"";

	wsprintf(szBuf, L"%d", (int)GetMouse().x);
			TextOut(m_BitMap["Back"]->GetMemdc(),
				0,0,
				szBuf, lstrlen(szBuf));

	wsprintf(szBuf, L"%d", (int)GetMouse().y);
			TextOut(m_BitMap["Back"]->GetMemdc(),
				0,20,
				szBuf, lstrlen(szBuf));

	TCHAR Fight[128] = L"";
	TCHAR Sworder[128] = L"";
	TCHAR Archer[128] = L"";

	
	BitBlt(m_BitMap["Back"]->GetMemdc(), 165, 460, 70, 18, m_BitMap["NameTag"]->GetMemdc(), 0, 0, SRCCOPY);
	wsprintf(Fight, L"%s", L"파이터");
	TextOut(m_BitMap["Back"]->GetMemdc(), 185, 460,	Fight, lstrlen(Fight));

	TransparentBlt(m_BitMap["Back"]->GetMemdc(), 
		int(m_tInfo[0].fX - m_tInfo[0].fCX / 2.f),
		int(m_tInfo[0].fY - m_tInfo[0].fCY / 2.f),
		int(m_tInfo[0].fCX),
		int(m_tInfo[0].fCY),
		m_BitMap["Player_LEFT"]->GetMemdc(),
		int(m_tInfo[0].fCX * m_tSprite1.iStart),
		int(m_tInfo[0].fCY),
		int(m_tInfo[0].fCX),
		int(m_tInfo[0].fCY),
		RGB(255, 255, 250));

	BitBlt(m_BitMap["Back"]->GetMemdc(), 400, 460, 70, 18, m_BitMap["NameTag"]->GetMemdc(), 0, 0, SRCCOPY);
	wsprintf(Sworder, L"%s", L"전사");
	TextOut(m_BitMap["Back"]->GetMemdc(), 420, 460,	Sworder, lstrlen(Sworder));

	TransparentBlt(m_BitMap["Back"]->GetMemdc(), 400, 480, 80, 90,
		m_BitMap["Sworder"]->GetMemdc(),
		0, 	0,
		80, 90,
		RGB(255, 255, 250));

	BitBlt(m_BitMap["Back"]->GetMemdc(), 640, 460, 70, 18, m_BitMap["NameTag"]->GetMemdc(), 0, 0, SRCCOPY);
	wsprintf(Archer, L"%s", L"궁수");
	TextOut(m_BitMap["Back"]->GetMemdc(), 660, 460,	Archer, lstrlen(Archer));

	TransparentBlt(m_BitMap["Back"]->GetMemdc(),
		int(m_tInfo[1].fX - m_tInfo[1].fCX / 2.f),
		int(m_tInfo[1].fY - m_tInfo[1].fCY / 2.f),
		int(m_tInfo[1].fCX),
		int(m_tInfo[1].fCY),
		m_BitMap["Archer_Left"]->GetMemdc(),
		int(m_tInfo[1].fCX * m_tSprite2.iStart),
		int(m_tInfo[1].fCY),
		int(m_tInfo[1].fCX),
		int(m_tInfo[1].fCY),
		RGB(255, 255, 250));

	for (size_t i = 0; i < m_vecButton.size(); ++i)
	{
		m_vecButton[i]->Render(m_BitMap["Back"]->GetMemdc());
	}

	BitBlt(hdc, 
			0, 0, 
			WINCX, WINCY, 
			m_BitMap["Back"]->GetMemdc(),
			0, 0, SRCCOPY);
}
void CCreate::Release(void)
{
	for (map<string, CBitBmp*>::iterator iter = m_BitMap.begin(); iter != m_BitMap.end(); ++iter)
	{
		::Safe_Delete(iter->second);
	}
	m_BitMap.clear();

	for (size_t i = 0; i < m_vecButton.size(); ++i)
	{
		::Safe_Delete(m_vecButton[i]);
	}
	m_vecButton.clear();
}

CUI* CCreate::CreateButton(float _fX, float _fY, string _strKey)
{
	CUI* pButton = CFactory<CMyButton>::CreateUI(_fX, _fY, _strKey);

	return pButton;
}

void	CCreate::UIPicking(DWORD _delta)
{
	int iSelect = 0;

	RECT rc = {m_tInfo[0].fX - m_tInfo[0].fCX / 2.f,
		m_tInfo[0].fY - m_tInfo[0].fCY / 2.f,
		m_tInfo[0].fX + m_tInfo[0].fCX / 2.f,
		m_tInfo[0].fY + m_tInfo[0].fCY / 2.f};

	RECT rc2 = {m_tInfo[1].fX - m_tInfo[1].fCX / 2.f,
		m_tInfo[1].fY - m_tInfo[1].fCY / 2.f,
		m_tInfo[1].fX + m_tInfo[1].fCX / 2.f,
		m_tInfo[1].fY + m_tInfo[1].fCY / 2.f};

	if (PtInRect(&rc, GetMouse()))
	{
		if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
		{
			m_tSprite1 = SPRITE(0, 3, 1, 120);
		}
	}

	if (PtInRect(&rc2, GetMouse()))
	{
		if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
		{
			m_tSprite2 = SPRITE(0, 4, 1, 120);
		}
	}


	for (size_t i = 0; i < m_vecButton.size(); ++i)
	{
		m_vecButton[i]->Progress(_delta);
		iSelect = ((CMyButton*)m_vecButton[i])->GetSelect();

		switch (iSelect)
		{
		case SC_LOBBY:
			iSelect = 0;
			CSceneMgr::GetInstance()->SetScene(SC_LOBBY);
			return;
		}
	}
}
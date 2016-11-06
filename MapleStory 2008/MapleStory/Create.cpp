#include "StdAfx.h"
#include "Create.h"

CCreate::CCreate(void)
{

}

CCreate::~CCreate(void)
{
	Release();
}

void CCreate::Initialize(void)
{
	m_BitMap["Back"] = (new CBitBmp)->LoadBmp(L"../Texture/Back.bmp");
	m_BitMap["Create"] = (new CBitBmp)->LoadBmp(L"../Texture/Create.bmp");

	m_BitMap["Fighter"] = (new CBitBmp)->LoadBmp(L"../Texture/Fighter.bmp");
	m_BitMap["Sworder"] = (new CBitBmp)->LoadBmp(L"../Texture/Sworder.bmp");
	m_BitMap["Archer"] = (new CBitBmp)->LoadBmp(L"../Texture/Archer.bmp");
	m_BitMap["NameTag"] = (new CBitBmp)->LoadBmp(L"../Texture/NameTag.bmp");



}

void CCreate::Progress(DWORD _delta)
{

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

	TransparentBlt(m_BitMap["Back"]->GetMemdc(), 180, 480, 50, 70,
		m_BitMap["Fighter"]->GetMemdc(),
		0, 	0,
		50, 70,
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

	TransparentBlt(m_BitMap["Back"]->GetMemdc(), 650, 480, 47, 76,
		m_BitMap["Archer"]->GetMemdc(),
		0, 	0,
		47, 76,
		RGB(255, 255, 250));

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
}

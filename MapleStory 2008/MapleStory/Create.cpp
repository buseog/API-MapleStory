#include "StdAfx.h"
#include "Create.h"
#include "SceneMgr.h"
#include "MyButton.h"
#include "Factory.h"
#include "UI.h"

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

	m_BitMap["Character_CREATE"] = (new CBitBmp)->LoadBmp(L"../Texture/Character_CREATE.bmp");

	m_vecButton.push_back(CreateButton(620.f, 200.f, "Character_CREATE"));

	CParent::SetBitMap(&m_BitMap);
	CUI::SetBitMap(&m_BitMap);
}

void CCreate::Progress(DWORD _delta)
{
	int iSelect = 0;

	for (size_t i = 0; i < m_vecButton.size(); ++i)
	{
		m_vecButton[i]->Progress(_delta);
		iSelect = ((CMyButton*)m_vecButton[i])->GetSelect();

		switch (iSelect)
		{
		case SC_VILLAGE:
			CSceneMgr::GetInstance()->SetScene(SC_VILLAGE);
			return;
		}
	}
}

void CCreate::Render(HDC hdc)
{
	BitBlt(m_BitMap["Back"]->GetMemdc(), 
		0, 0, 
		WINCX, WINCY, 
		m_BitMap["Create"]->GetMemdc(), 
		0, 0, SRCCOPY);

	for (size_t i = 0; i < m_vecButton.size(); ++i)
	{
		m_vecButton[i]->Render(m_BitMap["Back"]->GetMemdc());
	}

	
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


	BitBlt(hdc, 
			0, 0, 
			WINCX, WINCY, 
			m_BitMap["Back"]->GetMemdc(),
			0, 0, SRCCOPY);
}

void CCreate::Release(void)
{
}

CUI* CCreate::CreateButton(float _fX, float _fY, string _strKey)
{
	CUI* pButton = CFactory<CMyButton>::CreateUI(_fX, _fY, _strKey);

	return pButton;
}
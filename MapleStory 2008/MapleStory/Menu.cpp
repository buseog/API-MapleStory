#include "StdAfx.h"
#include "Menu.h"
#include "SceneMgr.h"
#include "MyButton.h"
#include "Factory.h"
#include "UI.h"


CMenu::CMenu(void)
{
}

CMenu::~CMenu(void)
{
	Release();
}

void CMenu::Initialize(void)
{
	m_BitMap["Back"] = (new CBitBmp)->LoadBmp(L"../Texture/Back.bmp");
	m_BitMap["Menu"] = (new CBitBmp)->LoadBmp(L"../Texture/Menu.bmp");

	m_BitMap["Start"] = (new CBitBmp)->LoadBmp(L"../Texture/Start.bmp");
	m_BitMap["Edit"] = (new CBitBmp)->LoadBmp(L"../Texture/Edit.bmp");
	m_BitMap["Exit"] = (new CBitBmp)->LoadBmp(L"../Texture/Exit.bmp");

	m_vecButton.push_back(CreateButton(200.f, 400.f, "Start"));
	m_vecButton.push_back(CreateButton(400.f, 400.f, "Edit"));
	m_vecButton.push_back(CreateButton(600.f, 400.f, "Exit"));

	CParent::SetBitMap(&m_BitMap);
	CUI::SetBitMap(&m_BitMap);
}

void CMenu::Progress(DWORD _delta)
{
	int iSelect = 0;

	for (size_t i = 0; i < m_vecButton.size(); ++i)
	{
		m_vecButton[i]->Progress(_delta);
		iSelect = ((CMyButton*)m_vecButton[i])->GetSelect();

		switch (iSelect)
		{
		case SC_LOBBY:
			CSceneMgr::GetInstance()->SetScene(SC_LOBBY);
			return;

		case SC_MAPEDIT:
			CSceneMgr::GetInstance()->SetScene(SC_MAPEDIT);
			return;

		case SC_END:
			DestroyWindow(g_hWnd);
			return;
		}
	}
}

void CMenu::Render(HDC hdc)
{
	BitBlt(m_BitMap["Back"]->GetMemdc(), 
		0, 0, 
		WINCX, WINCY, 
		m_BitMap["Menu"]->GetMemdc(), 
		0, 0, SRCCOPY);

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
void CMenu::Release(void)
{
	for (size_t i = 0; i < m_vecButton.size(); ++i)
	{
		::Safe_Delete(m_vecButton[i]);
	}
	m_vecButton.clear();

	for (map<string, CBitBmp*>::iterator iter = m_BitMap.begin(); iter != m_BitMap.end(); ++iter)
	{
		::Safe_Delete(iter->second);
	}
	m_BitMap.clear();
}

CUI* CMenu::CreateButton(float _fX, float _fY, string _strKey)
{
	CUI* pButton = CFactory<CMyButton>::CreateUI(_fX, _fY, _strKey);

	return pButton;
}
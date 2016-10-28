#include "StdAfx.h"
#include "Login.h"
#include "MyButton.h"
#include "SceneMgr.h"
#include "Factory.h"


CLogin::CLogin(void)
{
}

CLogin::~CLogin(void)
{
}

void CLogin::Initialize(void)
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
}

void CLogin::Progress(void)
{
	int iSelect = 0;

	for (size_t i = 0; i < m_vecButton.size(); ++i)
	{
		m_vecButton[i]->Progress();
		iSelect = ((CMyButton*)m_vecButton[i])->GetSelect();

		switch (iSelect)
		{
		case SC_VILLAGE:
			CSceneMgr::GetInstance()->SetScene(SC_VILLAGE);
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

void CLogin::Render(HDC hdc)
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
void CLogin::Release(void)
{
	for (size_t i = 0; i < m_vecButton.size(); ++i)
	{
		::Safe_Delete(m_vecButton[i]);
	}
	m_vecButton.clear();
}

CParent* CLogin::CreateButton(float _fX, float _fY, string _BmpKey)
{
	CParent* pButton = CFactory<CMyButton>::CreateParent(_fX, _fY);

	pButton->SetBmpKey(_BmpKey);

	return pButton;
}
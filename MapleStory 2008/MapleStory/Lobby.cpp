#include "StdAfx.h"
#include "Lobby.h"
#include "SceneMgr.h"
#include "MyButton.h"
#include "Factory.h"
#include "UI.h"

CLobby::CLobby(void)
{
}

CLobby::~CLobby(void)
{
	Release();
}

void CLobby::Initialize(void)
{
	m_bPick = false;

	for (int i = 0; i < 3; ++i)
	{
		m_pPlayer[i] = NULL;
	}

	m_BitMap["Back"] = (new CBitBmp)->LoadBmp(L"../Texture/Back.bmp");
	m_BitMap["Lobby"] = (new CBitBmp)->LoadBmp(L"../Texture/Lobby.bmp");

	m_BitMap["Character_SELECT"] = (new CBitBmp)->LoadBmp(L"../Texture/Character_SELECT.bmp");
	m_BitMap["Character_CREATE"] = (new CBitBmp)->LoadBmp(L"../Texture/Character_CREATE.bmp");
	m_BitMap["Character_DELETE"] = (new CBitBmp)->LoadBmp(L"../Texture/Character_DELETE.bmp");
	m_BitMap["BackScene"] = (new CBitBmp)->LoadBmp(L"../Texture/BackScene.bmp");

	m_BitMap["Fighter"] = (new CBitBmp)->LoadBmp(L"../Texture/Fighter.bmp");
	m_BitMap["Sworder"] = (new CBitBmp)->LoadBmp(L"../Texture/Sworder.bmp");
	m_BitMap["Archer"] = (new CBitBmp)->LoadBmp(L"../Texture/Archer.bmp");

	m_vecButton.push_back(CreateButton(628.f, 156.f, "Character_SELECT"));
	m_vecButton.push_back(CreateButton(628.f, 205.f, "Character_CREATE"));
	m_vecButton.push_back(CreateButton(628.f, 262.f, "Character_DELETE"));
	m_vecButton.push_back(CreateButton(100.f, 500.f, "BackScene"));

	HANDLE		hFile = NULL;
	DWORD		dwByte = 0;
	CParent*	p = new CPlayer;
	
		hFile = CreateFile(L"../Data/Character.dat",
							GENERIC_READ, 
							0, 
							NULL, 
							OPEN_EXISTING, 
							FILE_ATTRIBUTE_NORMAL, 
							NULL);

		ReadFile(hFile, p, sizeof(CPlayer), &dwByte, NULL);

		if(dwByte == 0)
		{
			::Safe_Delete(p);
		}
		else
			m_pPlayer[0] = p;
		
		
	CloseHandle(hFile);

	CParent::SetBitMap(&m_BitMap);
	m_pPlayer[0]->SetBitMap(&m_BitMap);
	CUI::SetBitMap(&m_BitMap);
}

void CLobby::Progress(DWORD _delta)
{
	int iSelect = 0;

	RECT rc = {275, 265, 325, 335};

	if (PtInRect(&rc, GetMouse()))
	{
		if (GetAsyncKeyState(VK_LBUTTON))
			m_bPick = true;
	}


	if (m_bPick)
	{
		for (size_t i = 0; i < m_vecButton.size(); ++i)
		{
			m_vecButton[i]->Progress(_delta);
			iSelect = ((CMyButton*)m_vecButton[i])->GetSelect();

			switch (iSelect)
			{
				case SC_CREATE:
					CSceneMgr::GetInstance()->SetScene(SC_CREATE);
					break;
				case SC_VILLAGE:
					CSceneMgr::GetInstance()->SetScene(SC_VILLAGE);
					break;;
			}
		}
	}
	else
	{
		for (size_t i = 0; i < m_vecButton.size(); ++i)
		{
			m_vecButton[i]->Progress(_delta);
			iSelect = ((CMyButton*)m_vecButton[i])->GetSelect();

			switch (iSelect)
			{
				case SC_CREATE:
					CSceneMgr::GetInstance()->SetScene(SC_CREATE);
					break;
			}
		}
	}
}

void CLobby::Render(HDC hdc)
{
	BitBlt(m_BitMap["Back"]->GetMemdc(), 
		0, 0, 
		WINCX, WINCY, 
		m_BitMap["Lobby"]->GetMemdc(), 
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
	if(m_pPlayer[0])
	{
		if (m_pPlayer[0]->GetStrKey() == "Player_LEFT" || m_pPlayer[0]->GetStrKey() == "Player_RIGHT")
		{
			TransparentBlt(m_BitMap["Back"]->GetMemdc(),
				300, 300, 
				50, 70,
				m_BitMap["Fighter"]->GetMemdc(),
				0, 0,
				50, 70,
				RGB(255, 255, 250));
		}
	}

	BitBlt(hdc, 
			0, 0, 
			WINCX, WINCY, 
			m_BitMap["Back"]->GetMemdc(),
			0, 0, SRCCOPY);
}

void CLobby::Release(void)
{
	for (size_t i = 0; i < m_vecButton.size(); ++i)
	{
		::Safe_Delete(m_vecButton[i]);
	}
	m_vecButton.clear();
}

CUI* CLobby::CreateButton(float _fX, float _fY, string _strKey)
{
	CUI* pButton = CFactory<CMyButton>::CreateUI(_fX, _fY, _strKey);

	return pButton;
}
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
	m_iPick = 0;
	m_tSprite[0] = SPRITE(0, 5, 0, 80);
	m_tSprite[1] = SPRITE(0, 5, 0, 80);

	m_BitMap["Back"] = (new CBitBmp)->LoadBmp(L"../Texture/Back.bmp");
	m_BitMap["Lobby"] = (new CBitBmp)->LoadBmp(L"../Texture/Lobby.bmp");
	
	m_BitMap["Character_SELECT"] = (new CBitBmp)->LoadBmp(L"../Texture/Character_SELECT.bmp");
	m_BitMap["Character_CREATE"] = (new CBitBmp)->LoadBmp(L"../Texture/Character_CREATE.bmp");
	m_BitMap["Character_DELETE"] = (new CBitBmp)->LoadBmp(L"../Texture/Character_DELETE.bmp");
	m_BitMap["BackScene"] = (new CBitBmp)->LoadBmp(L"../Texture/BackScene.bmp");

	m_BitMap["Player_LEFT"] = (new CBitBmp)->LoadBmp(L"../Texture/Player/Player_LEFT.bmp");
	m_BitMap["Sworder"] = (new CBitBmp)->LoadBmp(L"../Texture/Sworder.bmp");
	m_BitMap["Archer_LEFT"] = (new CBitBmp)->LoadBmp(L"../Texture/Player/Archer_LEFT.bmp");

	m_vecButton.push_back(CreateButton(628.f, 156.f, "Character_SELECT"));
	m_vecButton.push_back(CreateButton(628.f, 205.f, "Character_CREATE"));
	m_vecButton.push_back(CreateButton(628.f, 262.f, "Character_DELETE"));
	m_vecButton.push_back(CreateButton(63.f, 450.f, "BackScene"));
	CUI::SetBitMap(&m_BitMap);

	CDevice::GetInstance()->LoadWave(L"../Sound/Login.wav");	// 0
	CDevice::GetInstance()->LoadWave(L"../Sound/Village.wav");	// 1
	CDevice::GetInstance()->LoadWave(L"../Sound/Stage.wav");	// 2
	CDevice::GetInstance()->LoadWave(L"../Sound/Stage2.wav");	// 3
	CDevice::GetInstance()->LoadWave(L"../Sound/BossField.wav");// 4
	CDevice::GetInstance()->LoadWave(L"../Sound/RangeSound.wav");// 5
	CDevice::GetInstance()->LoadWave(L"../Sound/BoltSound.wav");// 6
	CDevice::GetInstance()->LoadWave(L"../Sound/TyphoonSound.wav");// 7
	CDevice::GetInstance()->LoadWave(L"../Sound/BeyondSound.wav");// 8

	CDevice::GetInstance()->SoundPlay(0, 1);

}

void CLobby::Progress(DWORD _delta)
{
	int iSelect = 0;

	RECT player = {200, 290, 270, 380};
	RECT archer = {400, 300, 450, 375};

	if (m_bPick)
	{	
		if (m_dwTime + m_tSprite[m_iPick].dwTime < GetTickCount())
		{
			m_dwTime = GetTickCount();

			++m_tSprite[m_iPick].iStart;
		}

		if (m_tSprite[m_iPick].iStart >= m_tSprite[m_iPick].iLast)
		{
 			m_tSprite[m_iPick].iStart = 0;
		}
	}

	if (PtInRect(&player, GetMouse()))
	{
		if (GetAsyncKeyState(VK_LBUTTON))
		{
			m_bPick = true;
			m_tSprite[0] = SPRITE(0, 3, 1, 120);
			m_iPick = 0;
			m_tSprite[1] = SPRITE(0, 5, 0, 80);
		}
	}

	if (PtInRect(&archer, GetMouse()))
	{
		if (GetAsyncKeyState(VK_LBUTTON))
		{
			m_bPick = true;
			m_tSprite[1] = SPRITE(0, 4, 1, 120);
			m_iPick = 1;
			m_tSprite[0] = SPRITE(0, 5, 0, 80);
		}
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
				{
					CSceneMgr::GetInstance()->SetScene(SC_CREATE);
				}
				break;

				case SC_VILLAGE:
				{
					if (m_iPick == 0)
					{
						m_vecParent[PAR_PLAYER].push_back(CFactory<CPlayer>::CreateParent(50.0f, 300.f, "Player_LEFT"));
					}
					else if (m_iPick == 1)
					{
						m_vecParent[PAR_PLAYER].push_back(CFactory<CPlayer>::CreateParent(50.0f, 300.f, "Archer_LEFT"));
					}
					CSceneMgr::GetInstance()->SetScene(SC_VILLAGE);
				}
				break;;
			}
		}
	}
	else
	{
		for (size_t i = 1; i < m_vecButton.size(); ++i)
		{
			m_vecButton[i]->Progress(_delta);
			iSelect = ((CMyButton*)m_vecButton[i])->GetSelect();

			switch (iSelect)
			{
				case SC_CREATE:
				{
					iSelect = 0;
					CSceneMgr::GetInstance()->SetScene(SC_CREATE);
				}
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


	TransparentBlt(m_BitMap["Back"]->GetMemdc(),
		200, 290, 
		70, 90,
		m_BitMap["Player_LEFT"]->GetMemdc(),
		70 * m_tSprite[0].iStart, 90 * m_tSprite[0].iMotion,
		70, 90,
		RGB(255, 255, 250));

	TransparentBlt(m_BitMap["Back"]->GetMemdc(),
		400, 300, 
		50, 75,
		m_BitMap["Archer_LEFT"]->GetMemdc(),
		50 * m_tSprite[1].iStart, 75 * m_tSprite[1].iMotion,
		50, 75,
		RGB(255, 255, 250));


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

	for (map<string, CBitBmp*>::iterator iter = m_BitMap.begin(); iter != m_BitMap.end(); ++iter)
	{
		::Safe_Delete(iter->second);
	}
	m_BitMap.clear();
}

CUI* CLobby::CreateButton(float _fX, float _fY, string _strKey)
{
	CUI* pButton = CFactory<CMyButton>::CreateUI(_fX, _fY, _strKey);

	return pButton;
}
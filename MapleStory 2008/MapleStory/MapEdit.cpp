#include "StdAfx.h"
#include "MapEdit.h"
#include "BitBmp.h"
#include "SceneMgr.h"

CMapEdit::CMapEdit(void)
:m_bType(false)
,m_iTileOption(0)
{
	m_strKey = "Village";
	m_ptScroll.x = 0;
	m_ptScroll.y = 0;
}

CMapEdit::~CMapEdit(void)
{
	Release();
}



void CMapEdit::Initialize(void)
{
	if (m_strKey == "Village")
		m_tInfo = INFO(0, 0, 1920, 680);

	if (m_strKey == "Stage1")
		m_tInfo = INFO(0, 0, 1773, 1464);
		
	if (m_strKey == "Stage2")
		m_tInfo = INFO(0, 0, 1890, 941);

	if (m_strKey == "BossField")
		m_tInfo = INFO(0, 0, 1372, 1200);

	m_iTILEX = int(m_tInfo.fCX / TILECX);
	m_iTILEY = int(m_tInfo.fCY / TILECY);

	LoadMap();

	if (m_vecTile.size() == 0)
	{
		for(int i = 0; i < m_iTILEY; ++i)
		{
			for(int j = 0; j < m_iTILEX; ++j)
			{
				float fX = float((TILECX * j) + (TILECX / 2));
				float fY = float((TILECY * i) + (TILECY / 2));

				m_vecTile.push_back(CreateTile(fX, fY));
			}
		}
	}

	m_tStat.fSpeed = 10.f;
}

void CMapEdit::Progress(DWORD _delta)
{
	KeyCheck();	
	Scroll();
}

void CMapEdit::Render(HDC hdc)
{
	TCHAR szBuf[128] = L"";

	BitBlt((*m_pBitMap)["Back"]->GetMemdc(), 
		int(m_tInfo.fX + m_ptScroll.x), 
		int(m_tInfo.fY + m_ptScroll.y), 
		(int)m_tInfo.fCX, 
		(int)m_tInfo.fCY, 
		(*m_pBitMap)[m_strKey]->GetMemdc(), 
		0, 
		0, 
		SRCCOPY);

	if (m_bType)
	{
		for (int i = 0; i < m_iTILEY; ++i)
		{
			for (int j = 0; j < m_iTILEX; ++j)
			{
				int iIndex = i * m_iTILEX + j;
					
				{
					TransparentBlt((*m_pBitMap)["Back"]->GetMemdc(),
						int((m_vecTile[iIndex]->fX - TILECX / 2.f) + m_ptScroll.x),
						int((m_vecTile[iIndex]->fY - TILECY / 2.f) + m_ptScroll.y),
						TILECX,
						TILECY,
						(*m_pBitMap)["Tile"]->GetMemdc(),
						m_vecTile[iIndex]->iDrawID * TILECX,
						0,
						TILECX,
						TILECY,
						RGB(255, 255, 250));

					//wsprintf(szBuf, L"%d", iIndex);

					wsprintf(szBuf, L"%d", (int)iIndex);
					SetBkMode((*m_pBitMap)["Back"]->GetMemdc(),TRANSPARENT);
					TextOut((*m_pBitMap)["Back"]->GetMemdc(), 
						int((m_vecTile[iIndex]->fX - TILECX / 2.f) + m_ptScroll.x),
						int((m_vecTile[iIndex]->fY - TILECY / 2.f) + m_ptScroll.y),
						szBuf, lstrlen(szBuf));
				}
			}
		}
	}

	BitBlt(hdc, 0, 0, WINCX, WINCY, (*m_pBitMap)["Back"]->GetMemdc(), 0, 0, SRCCOPY);
}

void CMapEdit::Release(void)
{
	for (size_t i = 0; i < m_vecTile.size(); ++i)
	{
		::Safe_Delete(m_vecTile[i]);
	}
	m_vecTile.clear();

}

TILE* CMapEdit::CreateTile(float _fX, float _fY)
{
	TILE* pTile = new TILE;

	pTile->fX = _fX;
	pTile->fY = _fY;
	pTile->fCX = TILECX;
	pTile->fCY = TILECY;
	pTile->iOption  = 0;
	pTile->iDrawID  = 0;

	return pTile;
}

void CMapEdit::PickingOn(void)
{
	int	iX = (GetMouse().x - (int)m_ptScroll.x) / TILECX;
	int	iY = (GetMouse().y - (int)m_ptScroll.y) / TILECY;

	int	iIndex = iY * m_iTILEX + iX;

	if(iIndex < 0 || iIndex >= m_iTILEX * m_iTILEY)
		return;

	m_vecTile[iIndex]->iOption = m_iTileOption;
	m_vecTile[iIndex]->iDrawID = m_iTileOption;
}

void CMapEdit::PickingOff(void)
{
	int	iX = (GetMouse().x - (int)m_ptScroll.x) / TILECX;
	int	iY = (GetMouse().y - (int)m_ptScroll.y) / TILECY;

	int	iIndex = iY * m_iTILEX + iX;

	if(iIndex < 0 || iIndex >= m_iTILEX * m_iTILEY)
		return;

	m_vecTile[iIndex]->iOption = 0;
	m_vecTile[iIndex]->iDrawID = 0;
}

void CMapEdit::KeyCheck(void)
{
	if (GetAsyncKeyState(VK_LBUTTON) && m_bType)
	{
		PickingOn();
	}

	if (GetAsyncKeyState(VK_RBUTTON) && m_bType)
	{
		PickingOff();
	}

	if (GetAsyncKeyState(VK_F5) & 0x8001)
	{
		if (m_bType)
		{
			m_bType = false;
		}
		else
		{
			m_bType = true;
		}
	}

	if (GetAsyncKeyState(VK_F8) & 0x8001)
	{
		SaveMap();
		return;
	}

	if ((GetAsyncKeyState(VK_F1) & 0x8001) == 0x8001)
	{
		m_strKey = "Village";
		Initialize();
		return;
	}

	if ((GetAsyncKeyState(VK_F2) & 0x8001) == 0x8001)
	{
		m_strKey = "Stage1";
		Initialize();
		return;
	}

	if ((GetAsyncKeyState(VK_F3) & 0x8001) == 0x8001)
	{
		m_strKey = "Stage2";
		Initialize();
		return;
	}

	if ((GetAsyncKeyState(VK_F4) & 0x8001) == 0x8001)
	{
		m_strKey = "BossField";
		Initialize();
		return;
	}

	if ((GetAsyncKeyState(VK_F12) & 0x8001) == 0x8001)
	{
		CSceneMgr::GetInstance()->SetScene(SC_MENU);
		m_ptScroll.x = 0;
		m_ptScroll.y = 0;
		return;
	}


	if (GetAsyncKeyState('1'))
	{
		m_iTileOption = 0;
	}

	if (GetAsyncKeyState('2'))
	{
		m_iTileOption = 1;
	}

	if (GetAsyncKeyState('3'))
	{
		m_iTileOption = 2;
	}

	if (GetAsyncKeyState('4'))
	{
		m_iTileOption = 3;
	}

	if (GetAsyncKeyState('5'))
	{
		m_iTileOption = 4;
	}

	if(GetAsyncKeyState(VK_LEFT))
		m_ptScroll.x += (long)m_tStat.fSpeed;

	if(GetAsyncKeyState(VK_RIGHT))
		m_ptScroll.x -= (long)m_tStat.fSpeed;

	if(GetAsyncKeyState(VK_UP))
		m_ptScroll.y += (long)m_tStat.fSpeed;

	if(GetAsyncKeyState(VK_DOWN))
		m_ptScroll.y -= (long)m_tStat.fSpeed;
}

void CMapEdit::Scroll(void)
{
	if(m_ptScroll.x > 0)
		m_ptScroll.x = 0;

	if(m_ptScroll.y > 0)
		m_ptScroll.y = 0;

	if(m_ptScroll.x < WINCX - (TILECX * m_iTILEX))
		m_ptScroll.x = WINCX - (TILECX * m_iTILEX);

	if(m_ptScroll.y < WINCY - (TILECY * m_iTILEY))
		m_ptScroll.y = WINCY - (TILECY * m_iTILEY);
}


void CMapEdit::SaveMap(void)
{
	HANDLE hFile = NULL;
	DWORD dwByte = 0;
	
	if (m_strKey == "Village")
	{
		hFile = CreateFile(L"../Data/Village.dat",
							GENERIC_WRITE,
							0,
							NULL,
							CREATE_ALWAYS,
							FILE_ATTRIBUTE_NORMAL,
							NULL);
	}
	
	if (m_strKey == "Stage1")
	{
		hFile = CreateFile(L"../Data/Stage1.dat",
							GENERIC_WRITE,
							0,
							NULL,
							CREATE_ALWAYS,
							FILE_ATTRIBUTE_NORMAL,
							NULL);
	}

	if (m_strKey == "Stage2")
	{
		hFile = CreateFile(L"../Data/Stage2.dat",
							GENERIC_WRITE,
							0,
							NULL,
							CREATE_ALWAYS,
							FILE_ATTRIBUTE_NORMAL,
							NULL);
	}

	if (m_strKey == "BossField")
	{
		hFile = CreateFile(L"../Data/BossField.dat",
							GENERIC_WRITE,
							0,
							NULL,
							CREATE_ALWAYS,
							FILE_ATTRIBUTE_NORMAL,
							NULL);
	}

	for (size_t i = 0; i < m_vecTile.size(); ++i)
	{
		if (m_vecTile[i]->iOption)
		WriteFile(hFile, m_vecTile[i], sizeof(TILE), &dwByte, NULL);
	}

	CloseHandle(hFile);

	MessageBox(g_hWnd,L"저장됨.", L"메세지", MB_OK);
}

void CMapEdit::LoadMap(void)
{
	for(size_t i = 0; i < m_vecTile.size(); ++i)
	{
		::Safe_Delete(m_vecTile[i]);
	}
	m_vecTile.clear();
	vector<TILE*>().swap(m_vecTile);



	HANDLE		hFile = NULL;
	DWORD		dwByte = 0;

	if (m_strKey == "Village")
	{
		hFile = CreateFile(L"../Data/Village.dat",
							GENERIC_READ, 
							0, 
							NULL, 
							OPEN_EXISTING, 
							FILE_ATTRIBUTE_NORMAL, 
							NULL);
	}

	if (m_strKey == "Stage1")
	{
		hFile = CreateFile(L"../Data/Stage1.dat", 
							GENERIC_READ, 
							0, 
							NULL, 
							OPEN_EXISTING, 
							FILE_ATTRIBUTE_NORMAL, 
							NULL);
	}

	if (m_strKey == "Stage2")
	{
		hFile = CreateFile(L"../Data/Stage2.dat", 
							GENERIC_READ, 
							0, 
							NULL, 
							OPEN_EXISTING, 
							FILE_ATTRIBUTE_NORMAL, 
							NULL);
	}

	if (m_strKey == "BossField")
	{
		hFile = CreateFile(L"../Data/BossField.dat", 
							GENERIC_READ, 
							0, 
							NULL, 
							OPEN_EXISTING, 
							FILE_ATTRIBUTE_NORMAL, 
							NULL);
	}

	while(true)
	{
		TILE*		pTile = new TILE;

		ReadFile(hFile, pTile, sizeof(TILE), &dwByte, NULL);

		if(dwByte == 0)
		{
			::Safe_Delete(pTile);
			break;
		}

		m_vecTile.push_back(pTile);
	}

	CloseHandle(hFile);
}
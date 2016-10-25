#include "StdAfx.h"
#include "MapEdit.h"
#include "BitBmp.h"

CMapEdit::CMapEdit(void)
:m_bType(true)
{
	m_fScrollX = 0.f;
	m_fScrollY = 0.f;
}

CMapEdit::~CMapEdit(void)
{
	Release();
}


void CMapEdit::Initialize(void)
{
	for(int i = 0; i < TILEY; ++i)
	{
		for(int j = 0; j < TILEX; ++j)
		{
			float fX = float((TILECX * j) + (TILECX / 2));
			float fY = float((TILECY * i) + (TILECY / 2));

			m_vecTile.push_back(CreateTile(fX, fY));
		}
	}

	m_vecBmp.push_back((new CBitBmp)->LoadBmp(L"../Texture/Back.bmp"));
	m_vecBmp.push_back((new CBitBmp)->LoadBmp(L"../Texture/Tile.bmp"));
	m_vecBmp.push_back((new CBitBmp)->LoadBmp(L"../Texture/Field2.bmp"));

	m_tStat.fSpeed = 10.f;
}

void CMapEdit::Progress(void)
{
	KeyCheck();	
	Scroll();
}

void CMapEdit::Render(HDC hdc)
{
	TCHAR szBuf[128] = L"";

	BitBlt(m_vecBmp[0]->GetMemdc(), 0 + m_fScrollX, 0 + m_fScrollY, 1773, 1464, m_vecBmp[2]->GetMemdc(), 0, 0, SRCCOPY);

	if (m_bType)
	{
		for(int i = 0; i < TILEY; ++i)
		{
			for(int j = 0; j < TILEX; ++j)
			{
				int iIndex = i * TILEX + j;

				TransparentBlt(m_vecBmp[0]->GetMemdc(),
					int((m_vecTile[iIndex]->fX - TILECX / 2.f) + m_fScrollX),
					int((m_vecTile[iIndex]->fY - TILECY / 2.f) + m_fScrollY),
					TILECX,
					TILECY,
					m_vecBmp[1]->GetMemdc(),
					m_vecTile[iIndex]->iDrawID * TILECX,
					0,
					TILECX,
					TILECY,
					RGB(0, 255, 0));

				//BitBlt(m_vecBmp[0]->GetMemdc(), 
				//	int((m_vecTile[iIndex]->fX - TILECX / 2.f) + m_fScrollX),
				//	int((m_vecTile[iIndex]->fY - TILECY / 2.f) + m_fScrollY),
				//	TILECX, 
				//	TILECY,
				//	m_vecBmp[1]->GetMemdc(),
				//	m_vecTile[iIndex]->iDrawID * TILECX, 
				//	0, SRCCOPY);

				wsprintf(szBuf, L"%d", iIndex);

				TextOut(m_vecBmp[0]->GetMemdc(), 
					int((m_vecTile[iIndex]->fX - TILECX / 2.f) + m_fScrollX),
					int((m_vecTile[iIndex]->fY - TILECY / 2.f) + m_fScrollY),
					szBuf, lstrlen(szBuf));

			}
		}
	}

	BitBlt(hdc, 0, 0, WINCX, WINCY, m_vecBmp[0]->GetMemdc(), 0, 0, SRCCOPY);
}

void CMapEdit::Release(void)
{
	for(size_t i = 0; i < m_vecBmp.size(); ++i)
	{
		::Safe_Delete(m_vecBmp[i]);
	}
	m_vecBmp.clear();
	vector<CBitBmp*>().swap(m_vecBmp);

	for(size_t i = 0; i < m_vecTile.size(); ++i)
	{
		::Safe_Delete(m_vecTile[i]);
	}
	m_vecTile.clear();
	vector<TILE*>().swap(m_vecTile);	
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
	int	iX = (GetMouse().x -(int)m_fScrollX) / TILECX;
	int	iY = (GetMouse().y -(int)m_fScrollY) / TILECY;

	int	iIndex = iY * TILEX + iX;

	if(iIndex < 0 || iIndex >= TILEX * TILEY)
		return;

	m_vecTile[iIndex]->iOption = 1;
	m_vecTile[iIndex]->iDrawID = 1;
}

void CMapEdit::PickingOff(void)
{
	int	iX = (GetMouse().x -(int)m_fScrollX) / TILECX;
	int	iY = (GetMouse().y -(int)m_fScrollY) / TILECY;

	int	iIndex = iY * TILEX + iX;

	if(iIndex < 0 || iIndex >= TILEX * TILEY)
		return;

	m_vecTile[iIndex]->iOption = 0;
	m_vecTile[iIndex]->iDrawID = 0;
}

void CMapEdit::KeyCheck(void)
{
	if (GetAsyncKeyState(VK_LBUTTON))
	{
		PickingOn();
		return;
	}

	if (GetAsyncKeyState(VK_RBUTTON))
	{
		PickingOff();
		return;
	}

	if (GetAsyncKeyState(VK_F5))
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

	if(GetAsyncKeyState(VK_LEFT))
		m_fScrollX += m_tStat.fSpeed;

	if(GetAsyncKeyState(VK_RIGHT))
		m_fScrollX -= m_tStat.fSpeed;

	if(GetAsyncKeyState(VK_UP))
		m_fScrollY += m_tStat.fSpeed;

	if(GetAsyncKeyState(VK_DOWN))
		m_fScrollY -= m_tStat.fSpeed;
}

void CMapEdit::Scroll(void)
{
	if(m_fScrollX > 0)
		m_fScrollX = 0.f;

	if(m_fScrollY > 0)
		m_fScrollY = 0.f;

	if(m_fScrollX < WINCX - (TILECX * TILEX))
		m_fScrollX = WINCX - (TILECX * TILEX);

	if(m_fScrollY < WINCY - (TILECY * TILEY))
		m_fScrollY = WINCY - (TILECY * TILEY);
}

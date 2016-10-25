#include "StdAfx.h"
#include "MainGame.h"
#include "MapEdit.h"
#include "Factory.h"

CMainGame::CMainGame(void)
:m_pMapEdit(NULL)
{
}

CMainGame::~CMainGame(void)
{
}


void CMainGame::Initialize(void)
{
	m_hdc = GetDC(g_hWnd);
	m_pMapEdit = CFactory<CMapEdit>::CreateParent();
}

void CMainGame::Progress(void)
{
	m_pMapEdit->Progress();
}

void CMainGame::Render(void)
{
	m_pMapEdit->Render(m_hdc);
}

void CMainGame::Release(void)
{
	ReleaseDC(g_hWnd, m_hdc);
}
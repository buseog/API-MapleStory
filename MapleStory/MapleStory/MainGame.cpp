#include "StdAfx.h"
#include "MainGame.h"

#include "Player.h"
#include "Factory.h"
#include "SceneMgr.h"

CMainGame::CMainGame(void)
:m_pPlayer(NULL)
,m_pSceneMgr(CSceneMgr::GetInstance())
{
}

CMainGame::~CMainGame(void)
{
	Release();
}


void CMainGame::Initialize(void)
{
	m_hdc = GetDC(g_hWnd);
	m_pPlayer = CFactory<CPlayer>::CreateParent();
	m_pSceneMgr->SetScene(SC_STAGE1);
	m_pSceneMgr->SetPlayer(m_pPlayer);
}

void CMainGame::Progress(void)
{
	m_pSceneMgr->Progress();
	m_pPlayer->Progress();
}

void CMainGame::Render(void)
{
	m_pSceneMgr->Render(m_hdc);
	m_pPlayer->Render(m_hdc);
}

void CMainGame::Release(void)
{
	ReleaseDC(g_hWnd, m_hdc);
	m_pSceneMgr->DestroyInstance();
	Safe_Delete(m_pPlayer);
}
#include "StdAfx.h"
#include "SceneMgr.h"
#include "Start.h"
#include "Menu.h"
#include "Lobby.h"
#include "Create.h"
#include "Village.h"
#include "Stage1.h"
#include "Stage2.h"
#include "BossField.h"
#include "MapEditor.h"
#include "Parent.h"
#include "Player.h"

CSceneMgr* CSceneMgr::m_pInstance = NULL;

CSceneMgr::CSceneMgr(void)
: m_pScene(NULL)
,m_eStage(SC_MENU)
{
	for (int i = 0; i < SC_END; ++i)
	{
		m_pSaveScene[i] = NULL;
	}
}

CSceneMgr::~CSceneMgr(void)
{
	Release();
}

void CSceneMgr::SetScene(SCENEID eScene)
{
	if(m_pScene != NULL)
	{
		if (eScene == SC_LOBBY || eScene == SC_CREATE)
			::Safe_Delete(m_pScene);
	}

	switch(eScene)
	{
	case SC_START:
		if (!m_pSaveScene[eScene])
		{
			m_pScene = new CStart;
			m_pSaveScene[eScene] = m_pScene;
		}
		else
		{
			m_pScene = m_pSaveScene[eScene];
		}
		break;

	case SC_MENU:
		m_pScene = new CMenu;
		break;

	case SC_LOBBY:
		m_pScene = new CLobby;
		break;

	case SC_CREATE:
		m_pScene = new CCreate;
		break;

	case SC_VILLAGE:
		if (!m_pSaveScene[eScene])
		{
			m_pScene = new CVillage;
			m_pSaveScene[eScene] = m_pScene;
		}
		else
		{
			m_pScene = m_pSaveScene[SC_VILLAGE];
		}

		// Æ÷Å» ÀÌµ¿ºÎ
		if (m_eStage == SC_BOSS)
		{
			m_pScene->GetPlayer()->SetPos(50.f, 300.f);
			((CPlayer*)m_pScene->GetPlayer())->SetScroll(0.f, -190.f);
			((CPlayer*)m_pScene->GetPlayer())->SetOffset(400.f, 490.f);
		}
		else if (m_eStage == SC_STAGE1)
		{
			m_pScene->GetPlayer()->SetPos(1700.f, 470.f);
			((CPlayer*)m_pScene->GetPlayer())->SetScroll(-1120.f, -77.f);
			((CPlayer*)m_pScene->GetPlayer())->SetOffset(1520.f, 377.f);
		}
		break;

	case SC_STAGE1:
		if (!m_pSaveScene[eScene])
		{
			m_pScene = new CStage1;
			m_pSaveScene[eScene] = m_pScene;
		}
		else
		{
			m_pScene = m_pSaveScene[SC_STAGE1];
		}

		// Æ÷Å» ÀÌµ¿ºÎ
		if (m_eStage == SC_VILLAGE)
		{
			m_pScene->GetPlayer()->SetPos(150.f, 1140.f);
			((CPlayer*)m_pScene->GetPlayer())->SetScroll(0.f, -860.f);
			((CPlayer*)m_pScene->GetPlayer())->SetOffset(400.f, 1160.f);
		}
		else if (m_eStage == SC_STAGE2)
		{
			m_pScene->GetPlayer()->SetPos(1550.f, 1140.f);
			((CPlayer*)m_pScene->GetPlayer())->SetScroll(-973.f, -860.f);
			((CPlayer*)m_pScene->GetPlayer())->SetOffset(1373.f, 1160.f);
		}
		break; 

	case SC_STAGE2:
		if (!m_pSaveScene[eScene])
		{
			m_pScene = new CStage2;
			m_pSaveScene[eScene] = m_pScene;
		}
		else
		{
			m_pScene = m_pSaveScene[SC_STAGE2];
		}

		// Æ÷Å» ÀÌµ¿ºÎ
		if (m_eStage == SC_STAGE1)
		{
			m_pScene->GetPlayer()->SetPos(150.f, 570.f);
			((CPlayer*)m_pScene->GetPlayer())->SetScroll(0.f, -400.f);
			((CPlayer*)m_pScene->GetPlayer())->SetOffset(400.f, 700.f);
		}
		break;

	case SC_BOSS:
		if (!m_pSaveScene[eScene])
		{
			m_pScene = new CBossField;
			m_pSaveScene[eScene] = m_pScene;
		}
		else
		{
			m_pScene = m_pSaveScene[SC_BOSS];
		}

		// Æ÷Å» ÀÌµ¿ºÎ
		if (m_eStage == SC_STAGE2)
		{
			m_pScene->GetPlayer()->SetPos(170.f, 900.f);
			((CPlayer*)m_pScene->GetPlayer())->SetScroll(0.f, -600.f);
			((CPlayer*)m_pScene->GetPlayer())->SetOffset(400.f, 900.f);
		}
		break;

	case SC_MAPEDIT:
		m_pScene = new CMapEditor;
		break;
	}

	m_eStage = eScene;
	m_pScene->Initialize();
}

void CSceneMgr::Progress(DWORD _delta)
{
	if(m_pScene)
		m_pScene->Progress(_delta);
}

void CSceneMgr::Render(HDC hdc)
{
	if(m_pScene)
		m_pScene->Render(hdc);
}

void CSceneMgr::Release(void)
{
	for (int i = 0; i < SC_END; ++i)
	{
		if(m_pSaveScene[i])
			::Safe_Delete(m_pSaveScene[i]);
	}
}

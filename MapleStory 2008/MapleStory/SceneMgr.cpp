#include "StdAfx.h"
#include "SceneMgr.h"
#include "Start.h"
#include "Login.h"
#include "Create.h"
#include "Village.h"
#include "Stage1.h"
#include "Stage2.h"
#include "BossField.h"
#include "MapEditor.h"
#include "Parent.h"

CSceneMgr* CSceneMgr::m_pInstance = NULL;

CSceneMgr::CSceneMgr(void)
: m_pScene(NULL)
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
		if (eScene == SC_Start || eScene == SC_LOGIN || eScene == SC_MAPEDIT)
			Release();
	}


	switch(eScene)
	{
	case SC_Start:
		m_pScene = new CStart;
		break;

	case SC_LOGIN:
		m_pScene = new CLogin;
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
			m_pScene = m_pSaveScene[SC_VILLAGE];

		break;

	case SC_STAGE1:
		if (!m_pSaveScene[eScene])
		{
			m_pScene = new CStage1;
			m_pSaveScene[eScene] = m_pScene;
		}
		else
			m_pScene = m_pSaveScene[SC_STAGE1];
		break; 

	case SC_STAGE2:
		if (!m_pSaveScene[eScene])
		{
			m_pScene = new CStage2;
			m_pSaveScene[eScene] = m_pScene;
		}
		else
			m_pScene = m_pSaveScene[SC_STAGE2];
		break;

	case SC_BOSS:
		if (!m_pSaveScene[eScene])
		{
			m_pScene = new CBossField;
			m_pSaveScene[eScene] = m_pScene;
		}
		else
			m_pScene = m_pSaveScene[SC_BOSS];
		break;

	case SC_MAPEDIT:
		m_pScene = new CMapEditor;
		break;
	}

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
	::Safe_Delete(m_pScene);
}

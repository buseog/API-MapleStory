#include "StdAfx.h"
#include "SceneMgr.h"
#include "Loading.h"
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
}

CSceneMgr::~CSceneMgr(void)
{
	Release();
}

void CSceneMgr::SetScene(SCENEID eScene)
{
	if(m_pScene != NULL)
		Release();


	switch(eScene)
	{
	case SC_LOADING:
		m_pScene = new CLoading;
		break;

	case SC_LOGIN:
		m_pScene = new CLogin;
		break;

	case SC_CREATE:
		m_pScene = new CCreate;
		break;

	case SC_VILLAGE:
		m_pScene = new CVillage;
		break;

	case SC_STAGE1:
		m_pScene = new CStage1;
		break; 

	case SC_STAGE2:
		m_pScene = new CStage2;
		break;

	case SC_BOSS:
		m_pScene = new CBossField;
		break;

	case SC_MAPEDIT:
		m_pScene = new CMapEditor;
		break;
	}

	m_pScene->Initialize();
}

void CSceneMgr::Progress(void)
{
	if(m_pScene)
		m_pScene->Progress();
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

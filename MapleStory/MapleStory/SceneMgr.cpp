#include "StdAfx.h"
#include "SceneMgr.h"
#include "Stage1.h"
#include "Stage2.h"


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
	case SC_STAGE1:
		m_pScene = new CStage1;
		break;

	case SC_STAGE2:
		m_pScene = new CStage2;
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


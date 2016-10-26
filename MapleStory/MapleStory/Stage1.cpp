#include "StdAfx.h"
#include "Stage1.h"
#include "SceneMgr.h"
#include "Factory.h"
#include "MapEdit.h"

CStage1::CStage1(void)
{
}

CStage1::~CStage1(void)
{
	Release();
}


void CStage1::Initialize(void)
{
	m_pEdit = new CMapEdit;
	((CMapEdit*)m_pEdit)->SetStage(SC_STAGE1);
	m_pEdit->Initialize();
}

void CStage1::Progress(void)
{

	m_pEdit->Progress();

	if(GetAsyncKeyState('2'))
	{
		CSceneMgr::GetInstance()->SetScene(SC_STAGE2);
		return;
	}
}

void CStage1::Render(HDC hdc)
{
	m_pEdit->Render(hdc);
	m_pPlayer->Render(hdc);
}

void CStage1::Release(void)
{
	::Safe_Delete(m_pEdit);	
}


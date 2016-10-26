#include "StdAfx.h"
#include "Stage2.h"
#include "SceneMgr.h"
#include "Factory.h"
#include "MapEdit.h"

CStage2::CStage2(void)
:m_pEdit(NULL)
{
}

CStage2::~CStage2(void)
{
	Release();
}

void CStage2::Initialize(void)
{
	m_pEdit = new CMapEdit;
	((CMapEdit*)m_pEdit)->SetStage(SC_STAGE2);
	m_pEdit->Initialize();
}

void CStage2::Progress(void)
{

	m_pEdit->Progress();

	if(GetAsyncKeyState('1'))
	{
		CSceneMgr::GetInstance()->SetScene(SC_STAGE1);
		return;
	}
}

void CStage2::Render(HDC hdc)
{
	m_pEdit->Render(hdc);
}

void CStage2::Release(void)
{
	::Safe_Delete(m_pEdit);	
}


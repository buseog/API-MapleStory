#include "StdAfx.h"
#include "Stage2.h"
#include "SceneMgr.h"
#include "Factory.h"
#include "MapEdit.h"

CStage2::CStage2(void)
{
}

CStage2::~CStage2(void)
{
	Release();
}

void CStage2::Initialize(void)
{
}

void CStage2::Progress(void)
{
	if ((GetAsyncKeyState('1') & 0x8001) == 0x8001)
	{
		CSceneMgr::GetInstance()->SetScene(SC_STAGE1);
		return;
	}
}

void CStage2::Render(HDC hdc)
{
}

void CStage2::Release(void)
{	
}
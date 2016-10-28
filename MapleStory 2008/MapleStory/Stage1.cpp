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
}

void CStage1::Progress(void)
{
	if ((GetAsyncKeyState('2') & 0x8001) == 0x8001)
	{
		CSceneMgr::GetInstance()->SetScene(SC_STAGE2);
		return;
	}
}

void CStage1::Render(HDC hdc)
{
	
}

void CStage1::Release(void)
{
	
}


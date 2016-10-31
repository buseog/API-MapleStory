#include "StdAfx.h"
#include "Stage1.h"
#include "SceneMgr.h"
#include "Factory.h"
#include "MapEdit.h"

CStage1::CStage1(void)
{
	m_strKey = "Stage1";
}

CStage1::~CStage1(void)
{
	Release();
}


void CStage1::Initialize(void)
{
	LoadMap();
	LoadBmp();

}

void CStage1::Progress(DWORD _delta)
{

}

void CStage1::Render(HDC hdc)
{
	
}

void CStage1::Release(void)
{
	
}
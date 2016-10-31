#include "StdAfx.h"
#include "Stage2.h"
#include "SceneMgr.h"
#include "Factory.h"
#include "MapEdit.h"

CStage2::CStage2(void)
{
	m_strKey = "Stage2";
}

CStage2::~CStage2(void)
{
	Release();
}

void CStage2::Initialize(void)
{
	LoadMap();
	LoadBmp();
}

void CStage2::Progress(DWORD _delta)
{

}

void CStage2::Render(HDC hdc)
{
}

void CStage2::Release(void)
{	
}
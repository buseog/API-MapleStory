#include "StdAfx.h"
#include "BossField.h"

CBossField::CBossField(void)
{
	m_strKey = "BossField";
}

CBossField::~CBossField(void)
{
	Release();
}

void CBossField::Initialize(void)
{
	LoadMap();
	LoadBmp();

}

void CBossField::Progress(DWORD _delta)
{

}

void CBossField::Render(HDC hdc)
{

}

void CBossField::Release(void)
{
}
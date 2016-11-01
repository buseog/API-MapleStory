#include "StdAfx.h"
#include "Potion.h"

CPotion::CPotion(void)
{
}

CPotion::CPotion(string _strName, int _iAttack, int _iDeffense, int _iCount, int _iPrice, int _iType)
:CItem(_strName, _iAttack, _iDeffense, _iCount, _iPrice, _iType)
{

}

CPotion::~CPotion(void)
{
}

void CPotion::Initialize(void)
{

}

void CPotion::Progress(DWORD _delta)
{

}

void CPotion::Render(HDC hdc)
{

}

void CPotion::Release(void)
{

}
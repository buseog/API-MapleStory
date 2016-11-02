#include "StdAfx.h"
#include "Armor.h"

CArmor::CArmor(void)
{
}

CArmor::CArmor(string _strName, int _iOption, int _iCount, int _iPrice, int _iType)
:CItem(_strName, _iOption, _iCount, _iPrice, _iType)
{

}
CArmor::~CArmor(void)
{
}

void CArmor::Initialize(void)
{

}

void CArmor::Progress(DWORD _delta)
{

}

void CArmor::Render(HDC hdc)
{

}

void CArmor::Release(void)
{

}
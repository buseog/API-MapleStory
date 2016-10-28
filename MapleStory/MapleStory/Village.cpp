#include "StdAfx.h"
#include "Village.h"
#include "Player.h"


CVillage::CVillage(void)
{
}

CVillage::~CVillage(void)
{
	Release();
}

void CVillage::Initialize(void)
{
	m_BitMap["Back"] = (new CBitBmp)->LoadBmp(L"../Texture/Back.bmp");
	m_BitMap["Village"] = (new CBitBmp)->LoadBmp(L"../Texture/Village.bmp");

	m_BitMap["Player_LEFT"] = (new CBitBmp)->LoadBmp(L"../Texture/Player/Player_LEFT.bmp");
	m_BitMap["Player_RIGHT"] = (new CBitBmp)->LoadBmp(L"../Texture/Player/Player_RIGHT.bmp");
	
	m_pPlayer = new CPlayer;
	m_pPlayer->Initialize();
	m_pPlayer->SetBitMap(&m_BitMap);
}

void CVillage::Progress(void)
{
	m_pPlayer->Progress();
	int a;

}

void CVillage::Render(HDC hdc)
{
	BitBlt(m_BitMap["Back"]->GetMemdc(), 
			0, 0, 
			WINCX, WINCY, 
			m_BitMap["Village"]->GetMemdc(),
			0, 0, SRCCOPY);

	m_pPlayer->Render(m_BitMap["Back"]->GetMemdc());

	BitBlt(hdc, 
			0, 0, 
			WINCX, WINCY, 
			m_BitMap["Back"]->GetMemdc(),
			0, 0, SRCCOPY);
}

void CVillage::Release(void)
{
}
#include "StdAfx.h"
#include "Village.h"
#include "Player.h"
#include "Factory.h"
#include "UI.h"


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
	m_BitMap["UI"] = (new CBitBmp)->LoadBmp(L"../Texture/UI/UI.bmp");


	m_BitMap["Player_LEFT"] = (new CBitBmp)->LoadBmp(L"../Texture/Player/Player_LEFT.bmp");
	m_BitMap["Player_RIGHT"] = (new CBitBmp)->LoadBmp(L"../Texture/Player/Player_RIGHT.bmp");
	
	m_BitMap["Annihilation_LEFT"] = (new CBitBmp)->LoadBmp(L"../Texture/Skill/Annihilation_LEFT.bmp");
	m_BitMap["Annihilation_RIGHT"] = (new CBitBmp)->LoadBmp(L"../Texture/Skill/Annihilation_RIGHT.bmp");
	m_BitMap["Typhoon_LEFT"] = (new CBitBmp)->LoadBmp(L"../Texture/Skill/Typhoon_LEFT.bmp");
	m_BitMap["Typhoon_RIGHT"] = (new CBitBmp)->LoadBmp(L"../Texture/Skill/Typhoon_RIGHT.bmp");
	m_BitMap["Range_LEFT"] = (new CBitBmp)->LoadBmp(L"../Texture/Skill/Range_LEFT.bmp");

	m_vecParent[OBJ_PLAYER].push_back(CFactory<CPlayer>::CreateParent(300.f, 300.f));
	m_vecParent[OBJ_UI].push_back(CFactory<CUI>::CreateParent(WINCX / 2.f, WINCY / 2.f, "UI"));

	((CPlayer*)m_vecParent[OBJ_PLAYER].back())->SetSkill(&m_vecParent[OBJ_SKILL]);
	m_vecParent[OBJ_PLAYER].back()->SetBitMap(&m_BitMap);
}

void CVillage::Progress(void)
{
	for (size_t i = 0; i < OBJ_END; ++i)
	{
		for (vector<CParent*>::iterator iter = m_vecParent[i].begin(); iter != m_vecParent[i].end();)
		{
			(*iter)->Progress();

			if ((*iter)->GetSprite().iStart > (*iter)->GetSprite().iLast)
			{
				::Safe_Delete(*iter);
				iter = m_vecParent[i].erase(iter);

				if (iter == m_vecParent[i].end())
					break;
			}
			else
				++iter;
		}
	}
}

void CVillage::Render(HDC hdc)
{
	BitBlt(m_BitMap["Back"]->GetMemdc(), 
			0, 0, 
			WINCX, WINCY, 
			m_BitMap["Village"]->GetMemdc(),
			0, 0, SRCCOPY);

	for (size_t i = 0; i < OBJ_END; ++i)
	{
		for (vector<CParent*>::iterator iter = m_vecParent[i].begin(); iter != m_vecParent[i].end(); )
		{
			(*iter)->Render(m_BitMap["Back"]->GetMemdc());

			if (iter == m_vecParent[i].end())
				break;

			else
				++iter;
		}
	}
	

	BitBlt(hdc, 
			0, 0, 
			WINCX, WINCY, 
			m_BitMap["Back"]->GetMemdc(),
			0, 0, SRCCOPY);
}

void CVillage::Release(void)
{
}
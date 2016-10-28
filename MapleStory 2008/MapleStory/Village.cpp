#include "StdAfx.h"
#include "Village.h"
#include "Player.h"
#include "Factory.h"


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
	
	m_BitMap["Annihilation_LEFT"] = (new CBitBmp)->LoadBmp(L"../Texture/Skill/Annihilation_LEFT.bmp");

	m_vecParent[OBJ_PLAYER].push_back(CFactory<CPlayer>::CreateParent(300.f, 300.f));

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
		for (vector<CParent*>::iterator iter = m_vecParent[i].begin(); iter != m_vecParent[i].end(); ++iter)
		{
			(*iter)->Render(m_BitMap["Back"]->GetMemdc());
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
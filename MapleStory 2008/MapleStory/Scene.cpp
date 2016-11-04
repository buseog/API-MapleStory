#include "StdAfx.h"
#include "Scene.h"
#include "MapEdit.h"
#include "Parent.h"
#include "KeyMgr.h"


vector<CParent*>	CScene::m_vecParent[PAR_END];
vector<CUI*>	CScene::m_vecUI[UI_END];
bool			CScene::m_bUIView[UI_END];
bool			CScene::m_bMouse;
POINT			CScene::m_prevPT;
CUI*			CScene::m_pUI;

CScene::CScene(void)
:m_dwKey(0)
,m_pLoading(NULL)
{
	
}

CScene::~CScene(void)
{

}

void CScene::KeyInput(void)
{
	m_dwKey = CKeyMgr::GetInstance()->GetKey();
	if (m_dwKey & KEY_F5)	// 인벤토리
	{
		CItem*	pWeapon = new CArmor("Armor", 10, 1, 1, 1);
		((CInventory*)m_vecUI[UI_INVENTORY].back())->AddItem(pWeapon);
	}

	if (m_dwKey & KEY_I)	// 인벤토리
	{
		if (m_bUIView[UI_INVENTORY])
			m_bUIView[UI_INVENTORY] = false;
		
		else
			m_bUIView[UI_INVENTORY] = true;
	}

	if (m_dwKey & KEY_U)	// 장비창
	{
		if (m_bUIView[UI_EQUIPMENT])
			m_bUIView[UI_EQUIPMENT] = false;
		
		else
			m_bUIView[UI_EQUIPMENT] = true;
	}

	if (m_dwKey & KEY_K)	// 스킬창
	{
		if (m_bUIView[UI_SKILLPANEL])
			m_bUIView[UI_SKILLPANEL] = false;
		
		else
			m_bUIView[UI_SKILLPANEL] = true;
	}
}

void CScene::UIDrag(void)
{
	float fX = float(GetMouse().x - m_prevPT.x);
	float fY = float(GetMouse().y - m_prevPT.y);
	
	if(m_bMouse && m_pUI)
	{
		m_pUI->SetPos(m_pUI->GetInfo().fX + fX, m_pUI->GetInfo().fY + fY);
	}

	for (int i = 1; i < UI_END; ++i)
	{
		if(PtInRect(&m_vecUI[i].back()->GetRect(), GetMouse()))
		{
			if(GetAsyncKeyState(VK_LBUTTON))
			{
				if (m_bUIView[i])
				{
					m_prevPT = GetMouse();
					m_bMouse = true;
					m_pUI = m_vecUI[i].back();
				}
			}

			else
			{
				m_bMouse = false;
				m_pUI = NULL;
			}
		}
	}

	m_vecUI[UI_INVENTORY].back()->UIPicking();
	CItem* pSwap = m_vecUI[UI_INVENTORY].back()->GetReturnItem();
	if(pSwap)
	{
		((CEquipment*)m_vecUI[UI_EQUIPMENT].back())->EquipItem(pSwap);
		m_vecUI[UI_INVENTORY].back()->SetReturnItem();
	}

	m_vecUI[UI_EQUIPMENT].back()->UIPicking();
	CItem* pSwap2 = m_vecUI[UI_EQUIPMENT].back()->GetReturnItem();
	if(pSwap2)
	{
		((CInventory*)m_vecUI[UI_INVENTORY].back())->AddItem(pSwap2);
		m_vecUI[UI_EQUIPMENT].back()->SetReturnItem();
	}
}

void CScene::LoadMap(void)
{
	for(size_t i = 0; i < m_vecTile.size(); ++i)
	{
		::Safe_Delete(m_vecTile[i]);
	}
	m_vecTile.clear();
	vector<TILE*>().swap(m_vecTile);


	HANDLE		hFile = NULL;
	DWORD		dwByte = 0;

	if (m_strKey == "Village")
	{
		hFile = CreateFile(L"../Data/Village.dat",
							GENERIC_READ, 
							0, 
							NULL, 
							OPEN_EXISTING, 
							FILE_ATTRIBUTE_NORMAL, 
							NULL);
	}

	if (m_strKey == "Stage1")
	{
		hFile = CreateFile(L"../Data/Stage1.dat", 
							GENERIC_READ, 
							0, 
							NULL, 
							OPEN_EXISTING, 
							FILE_ATTRIBUTE_NORMAL, 
							NULL);
	}

	if (m_strKey == "Stage2")
	{
		hFile = CreateFile(L"../Data/Stage2.dat", 
							GENERIC_READ, 
							0, 
							NULL, 
							OPEN_EXISTING, 
							FILE_ATTRIBUTE_NORMAL, 
							NULL);
	}

	if (m_strKey == "BossField")
	{
		hFile = CreateFile(L"../Data/BossField.dat", 
							GENERIC_READ, 
							0, 
							NULL, 
							OPEN_EXISTING, 
							FILE_ATTRIBUTE_NORMAL, 
							NULL);
	}

	while(true)
	{
		TILE*		pTile = new TILE;

		ReadFile(hFile, pTile, sizeof(TILE), &dwByte, NULL);

		if(dwByte == 0)
		{
			::Safe_Delete(pTile);
			break;
		}

		m_vecTile.push_back(pTile);
	}

	CloseHandle(hFile);
}

void CScene::LoadBmp(void)
{
	// 백버퍼, 스테이지, 타일 추가
	m_BitMap["Back"] = (new CBitBmp)->LoadBmp(L"../Texture/Back.bmp");
	m_BitMap["Tile"] = (new CBitBmp)->LoadBmp(L"../Texture/Tile.bmp");
	m_BitMap["Village"] = (new CBitBmp)->LoadBmp(L"../Texture/Village.bmp");
	m_BitMap["Stage1"] = (new CBitBmp)->LoadBmp(L"../Texture/Stage1.bmp");
	m_BitMap["Stage2"] = (new CBitBmp)->LoadBmp(L"../Texture/Stage2.bmp");
	m_BitMap["BossField"] = (new CBitBmp)->LoadBmp(L"../Texture/BossField.bmp");
	m_BitMap["NPC"] = (new CBitBmp)->LoadBmp(L"../Texture/NPC.bmp");
	m_BitMap["Mouse"] = (new CBitBmp)->LoadBmp(L"../Texture/Mouse.bmp");

	
	m_BitMap["DamageEffect"] = (new CBitBmp)->LoadBmp(L"../Texture/DamageEffect.bmp");
	m_BitMap["CriticalEffect"] = (new CBitBmp)->LoadBmp(L"../Texture/CriticalEffect.bmp");
	m_BitMap["HitEffect"] = (new CBitBmp)->LoadBmp(L"../Texture/HitEffect.bmp");


	//UI 추가
	m_BitMap["UI"] = (new CBitBmp)->LoadBmp(L"../Texture/UI/UI.bmp");
	m_BitMap["Inventory"] = (new CBitBmp)->LoadBmp(L"../Texture/UI/Inventory.bmp");
	m_BitMap["Equipment"] = (new CBitBmp)->LoadBmp(L"../Texture/UI/Equipment.bmp");
	m_BitMap["SkillPanel"] = (new CBitBmp)->LoadBmp(L"../Texture/UI/SkillPanel.bmp");
	m_BitMap["QuickSlot"] = (new CBitBmp)->LoadBmp(L"../Texture/UI/QuickSlot.bmp");
	


	//플레이어 추가
	m_BitMap["Player_LEFT"] = (new CBitBmp)->LoadBmp(L"../Texture/Player/Player_LEFT.bmp");
	m_BitMap["Player_RIGHT"] = (new CBitBmp)->LoadBmp(L"../Texture/Player/Player_RIGHT.bmp");
	
	//스킬 추가
	m_BitMap["Annihilation_LEFT"] = (new CBitBmp)->LoadBmp(L"../Texture/Skill/Annihilation_LEFT.bmp");
	m_BitMap["Annihilation_RIGHT"] = (new CBitBmp)->LoadBmp(L"../Texture/Skill/Annihilation_RIGHT.bmp");

	m_BitMap["Ascend_LEFT"] = (new CBitBmp)->LoadBmp(L"../Texture/Skill/Ascend_LEFT.bmp");
	m_BitMap["Ascend_RIGHT"] = (new CBitBmp)->LoadBmp(L"../Texture/Skill/Ascend_RIGHT.bmp");

	m_BitMap["Typhoon_LEFT"] = (new CBitBmp)->LoadBmp(L"../Texture/Skill/Typhoon_LEFT.bmp");
	m_BitMap["Typhoon_RIGHT"] = (new CBitBmp)->LoadBmp(L"../Texture/Skill/Typhoon_RIGHT.bmp");

	m_BitMap["Range"] = (new CBitBmp)->LoadBmp(L"../Texture/Skill/Range.bmp");

	m_BitMap["Bolt_LEFT"] = (new CBitBmp)->LoadBmp(L"../Texture/Skill/Bolt_LEFT.bmp");
	m_BitMap["Bolt_RIGHT"] = (new CBitBmp)->LoadBmp(L"../Texture/Skill/Bolt_RIGHT.bmp");

	m_BitMap["Beyond_LEFT"] = (new CBitBmp)->LoadBmp(L"../Texture/Skill/Beyond_LEFT.bmp");
	m_BitMap["Beyond_RIGHT"] = (new CBitBmp)->LoadBmp(L"../Texture/Skill/Beyond_RIGHT.bmp");

	m_BitMap["Beyond2_LEFT"] = (new CBitBmp)->LoadBmp(L"../Texture/Skill/Beyond2_LEFT.bmp");
	m_BitMap["Beyond2_RIGHT"] = (new CBitBmp)->LoadBmp(L"../Texture/Skill/Beyond2_RIGHT.bmp");

	m_BitMap["Beyond3_LEFT"] = (new CBitBmp)->LoadBmp(L"../Texture/Skill/Beyond3_LEFT.bmp");
	m_BitMap["Beyond3_RIGHT"] = (new CBitBmp)->LoadBmp(L"../Texture/Skill/Beyond3_RIGHT.bmp");

	//몬스터 추가
	m_BitMap["GreenMushRoom_LEFT"] = (new CBitBmp)->LoadBmp(L"../Texture/Monster/GreenMushRoom_LEFT.bmp");
	m_BitMap["GreenMushRoom_RIGHT"] = (new CBitBmp)->LoadBmp(L"../Texture/Monster/GreenMushRoom_RIGHT.bmp");

	m_BitMap["BlueMushRoom_LEFT"] = (new CBitBmp)->LoadBmp(L"../Texture/Monster/BlueMushRoom_LEFT.bmp");
	m_BitMap["BlueMushRoom_RIGHT"] = (new CBitBmp)->LoadBmp(L"../Texture/Monster/BlueMushRoom_RIGHT.bmp");

	m_BitMap["PurpleMushRoom_LEFT"] = (new CBitBmp)->LoadBmp(L"../Texture/Monster/PurpleMushRoom_LEFT.bmp");
	m_BitMap["PurpleMushRoom_RIGHT"] = (new CBitBmp)->LoadBmp(L"../Texture/Monster/PurpleMushRoom_RIGHT.bmp");

	m_BitMap["CoupleMushRoom_LEFT"] = (new CBitBmp)->LoadBmp(L"../Texture/Monster/CoupleMushRoom_LEFT.bmp");
	m_BitMap["CoupleMushRoom_RIGHT"] = (new CBitBmp)->LoadBmp(L"../Texture/Monster/CoupleMushRoom_RIGHT.bmp");

	//이펙트 추가
	m_BitMap["Bolt_EFFECT"] = (new CBitBmp)->LoadBmp(L"../Texture/Skill/Bolt_EFFECT.bmp");
	m_BitMap["Typhoon_EFFECT"] = (new CBitBmp)->LoadBmp(L"../Texture/Skill/Typhoon_EFFECT.bmp");
	m_BitMap["Annihilation_EFFECT"] = (new CBitBmp)->LoadBmp(L"../Texture/Skill/Annihilation_EFFECT.bmp");
	m_BitMap["Ascend_EFFECT"] = (new CBitBmp)->LoadBmp(L"../Texture/Skill/Ascend_EFFECT.bmp");
	m_BitMap["Beyond1_EFFECT"] = (new CBitBmp)->LoadBmp(L"../Texture/Skill/Beyond1_EFFECT.bmp");
	m_BitMap["Beyond2_EFFECT"] = (new CBitBmp)->LoadBmp(L"../Texture/Skill/Beyond2_EFFECT.bmp");
	m_BitMap["Beyond3_EFFECT"] = (new CBitBmp)->LoadBmp(L"../Texture/Skill/Beyond3_EFFECT.bmp");

	//아이템 추가
	m_BitMap["Weapon"] = (new CBitBmp)->LoadBmp(L"../Texture/Item/Weapon.bmp");
	m_BitMap["Armor"] = (new CBitBmp)->LoadBmp(L"../Texture/Item/Armor.bmp");
	m_BitMap["Gold"] = (new CBitBmp)->LoadBmp(L"../Texture/Item/Gold.bmp");

}

void CScene::SetEffect(CParent*	_Effect)
{
	m_vecParent[PAR_EFFECT].push_back(_Effect);
}

void CScene::ParentClear(void)
{
	for (int i = 1; i < PAR_END; ++i)
	{
		for (vector<CParent*>::iterator iter = m_vecParent[i].begin(); iter != m_vecParent[i].end();)
		{
			::Safe_Delete(*iter);
			iter = m_vecParent[i].erase(iter);

			if (iter == m_vecParent[i].end())
				break;

			else
				++iter;
		}
		m_vecParent[i].clear();
	}
}

CParent* CScene::GetPlayer(void)
{
	return m_vecParent[PAR_PLAYER].back();
}
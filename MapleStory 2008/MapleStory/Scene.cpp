#include "StdAfx.h"
#include "Scene.h"
#include "MapEdit.h"
#include "Parent.h"
#include "KeyMgr.h"
#include "Weapon.h"
#include "Armor.h"
#include "Potion.h"
#include "CollisionMgr.h"


vector<CParent*>	CScene::m_vecParent[PAR_END];
vector<CUI*>	CScene::m_vecUI[UI_END];
bool			CScene::m_bDrag;
POINT			CScene::m_prevPT;
CUI*			CScene::m_pUI;

CScene::CScene(void)
:m_dwKey(0)
,m_pLoading(NULL)
,m_iFPS(0)
,m_dwTime(GetTickCount())
{
	memset(m_szFPS, 0, sizeof(TCHAR) * 128);
}

CScene::~CScene(void)
{

}

void CScene::KeyInput(void)
{
	m_dwKey = CKeyMgr::GetInstance()->GetKey();
	if (m_dwKey & KEY_F5)
	{
		CItem*	pWeapon = new CWeapon(L"Weapon", 10, 1, 1, IT_WEAPON);
		((CInventory*)m_vecUI[UI_INVENTORY].back())->AddItem(pWeapon);
	}

	if (m_dwKey & KEY_F6)
	{
		CItem*	pArmor = new CArmor(L"Armor", 10, 1, 1, IT_ARMOR);
		((CInventory*)m_vecUI[UI_INVENTORY].back())->AddItem(pArmor);
	}

	if (m_dwKey & KEY_F7)
	{
		CItem*	pPotion = new CPotion(L"HPPotion", 1000, 1, 1, IT_POTION);
		((CInventory*)m_vecUI[UI_INVENTORY].back())->AddItem(pPotion);
	}

	if (m_dwKey & KEY_F8)
	{

	}

	if (m_dwKey & KEY_I)	// 인벤토리
	{
		if (m_vecUI[UI_INVENTORY].back()->GetOnOff())
			m_vecUI[UI_INVENTORY].back()->SetOnOff(false);
		
		else
			m_vecUI[UI_INVENTORY].back()->SetOnOff(true);
	}

	if (m_dwKey & KEY_U)	// 장비창
	{
		if (m_vecUI[UI_EQUIPMENT].back()->GetOnOff())
			m_vecUI[UI_EQUIPMENT].back()->SetOnOff(false);
		
		else
			m_vecUI[UI_EQUIPMENT].back()->SetOnOff(true);
	}

	if (m_dwKey & KEY_K)	// 스킬창
	{
		if (m_vecUI[UI_SKILLPANEL].back()->GetOnOff())
			m_vecUI[UI_SKILLPANEL].back()->SetOnOff(false);
		
		else
			m_vecUI[UI_SKILLPANEL].back()->SetOnOff(true);
	}

	if (m_dwKey & KEY_J)	// 스텟
	{
		if (m_vecUI[UI_STATUS].back()->GetOnOff())
			m_vecUI[UI_STATUS].back()->SetOnOff(false);
		
		else
			m_vecUI[UI_STATUS].back()->SetOnOff(true);
	}

	if (m_dwKey & KEY_P)	// 퀵슬롯
	{
		((CQuickSlot*)m_vecUI[UI_QUICKSLOT].back())->SetExpress();
	}

	if (m_dwKey & KEY_Z)
	{
		CCollisionMgr::CollisionItem(&m_vecParent[PAR_PLAYER], &m_vecItem, &m_vecUI[UI_INVENTORY]);
	}
}

void CScene::UIDrag(void)
{
	float fX = float(GetMouse().x - m_prevPT.x);
	float fY = float(GetMouse().y - m_prevPT.y);
	
	if(m_bDrag && m_pUI)
	{
		m_pUI->SetPos(m_pUI->GetInfo().fX + fX, m_pUI->GetInfo().fY + fY);
	}

	for (int i = 0; i < UI_END; ++i)
	{
		if (i == UI_MAIN || i == UI_QUICKSLOT)
		{
		}
		else if (m_vecUI[i].back()->GetOnOff())
		{
			if(GetAsyncKeyState(VK_LBUTTON))
			{
				m_prevPT = GetMouse();
				if (m_bDrag)
					break;

				if(PtInRect(&m_vecUI[i].back()->GetRect(), GetMouse()))
				{
					m_bDrag = true;
					m_pUI = m_vecUI[i].back();
				}
			}
			else
			{
				m_bDrag = false;
				m_pUI = NULL;
			}
		}
	}

	CItem* pDrop = ((CInventory*)m_vecUI[UI_INVENTORY].back())->GetDropItem();
	if(pDrop)
	{
		pDrop->SetPos(m_vecParent[PAR_PLAYER].back()->GetInfo().fX, m_vecParent[PAR_PLAYER].back()->GetInfo().fY - 40.f);
		m_vecItem.push_back(pDrop);
		((CInventory*)m_vecUI[UI_INVENTORY].back())->SetDropItem();
	}

	CItem* pSwap = m_vecUI[UI_INVENTORY].back()->GetReturnItem();
	if(pSwap)
	{
		if (pSwap->GetItem().iType == IT_POTION)
		{
			m_vecParent[PAR_PLAYER].back()->HavePotion(pSwap);
			m_vecUI[UI_INVENTORY].back()->SetReturnItem();
			::Safe_Delete(pSwap);
		}
		else
		{
			((CEquipment*)m_vecUI[UI_EQUIPMENT].back())->EquipItem(pSwap);
			m_vecUI[UI_INVENTORY].back()->SetReturnItem();
			pSwap = NULL;
		}
	}

	CItem* pSwap2 = m_vecUI[UI_EQUIPMENT].back()->GetReturnItem();
	if(pSwap2)
	{
		((CInventory*)m_vecUI[UI_INVENTORY].back())->AddItem(pSwap2);
		m_vecUI[UI_EQUIPMENT].back()->SetReturnItem();
		pSwap2 = NULL;
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
	m_BitMap["Mouse"] = (new CBitBmp)->LoadBmp(L"../Texture/Mouse.bmp");

	
	m_BitMap["DamageEffect"] = (new CBitBmp)->LoadBmp(L"../Texture/DamageEffect.bmp");
	m_BitMap["CriticalEffect"] = (new CBitBmp)->LoadBmp(L"../Texture/CriticalEffect.bmp");
	m_BitMap["HitEffect"] = (new CBitBmp)->LoadBmp(L"../Texture/HitEffect.bmp");
	m_BitMap["LevelUpEFFECT"] = (new CBitBmp)->LoadBmp(L"../Texture/LevelUpEFFECT.bmp");


	//UI 추가
	m_BitMap["UI"] = (new CBitBmp)->LoadBmp(L"../Texture/UI/UI.bmp");
	m_BitMap["Status"] = (new CBitBmp)->LoadBmp(L"../Texture/UI/Status.bmp");
	m_BitMap["Inventory"] = (new CBitBmp)->LoadBmp(L"../Texture/UI/Inventory.bmp");
	m_BitMap["Equipment"] = (new CBitBmp)->LoadBmp(L"../Texture/UI/Equipment.bmp");
	m_BitMap["SkillPanel"] = (new CBitBmp)->LoadBmp(L"../Texture/UI/SkillPanel.bmp");
	m_BitMap["QuickSlot"] = (new CBitBmp)->LoadBmp(L"../Texture/UI/QuickSlot.bmp");
	m_BitMap["HPBar"] = (new CBitBmp)->LoadBmp(L"../Texture/UI/HPBar.bmp");
	m_BitMap["MPBar"] = (new CBitBmp)->LoadBmp(L"../Texture/UI/MPBar.bmp");
	m_BitMap["EXPBar"] = (new CBitBmp)->LoadBmp(L"../Texture/UI/EXPBar.bmp");
	m_BitMap["ItemStat"] = (new CBitBmp)->LoadBmp(L"../Texture/UI/ItemStat.bmp");
	m_BitMap["Dead"] = (new CBitBmp)->LoadBmp(L"../Texture/UI/Dead.bmp");
	m_BitMap["Close"] = (new CBitBmp)->LoadBmp(L"../Texture/UI/Close.bmp");
	m_BitMap["Store"] = (new CBitBmp)->LoadBmp(L"../Texture/UI/Store.bmp");
	


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

	m_BitMap["Boss"] = (new CBitBmp)->LoadBmp(L"../Texture/Monster/Boss.bmp");

	//이펙트 추가
	m_BitMap["Bolt_EFFECT"] = (new CBitBmp)->LoadBmp(L"../Texture/Skill/Bolt_EFFECT.bmp");
	m_BitMap["Typhoon_EFFECT"] = (new CBitBmp)->LoadBmp(L"../Texture/Skill/Typhoon_EFFECT.bmp");
	m_BitMap["Annihilation_EFFECT"] = (new CBitBmp)->LoadBmp(L"../Texture/Skill/Annihilation_EFFECT.bmp");
	m_BitMap["Ascend_EFFECT"] = (new CBitBmp)->LoadBmp(L"../Texture/Skill/Ascend_EFFECT.bmp");
	m_BitMap["Range_EFFECT"] = (new CBitBmp)->LoadBmp(L"../Texture/Skill/Range_EFFECT.bmp");
	m_BitMap["Beyond_EFFECT"] = (new CBitBmp)->LoadBmp(L"../Texture/Skill/Beyond_EFFECT.bmp");
	m_BitMap["Beyond2_EFFECT"] = (new CBitBmp)->LoadBmp(L"../Texture/Skill/Beyond2_EFFECT.bmp");
	m_BitMap["Beyond3_EFFECT"] = (new CBitBmp)->LoadBmp(L"../Texture/Skill/Beyond3_EFFECT.bmp");

	//아이템 추가
	m_BitMap["Weapon"] = (new CBitBmp)->LoadBmp(L"../Texture/Item/Weapon.bmp");
	m_BitMap["Armor"] = (new CBitBmp)->LoadBmp(L"../Texture/Item/Armor.bmp");
	m_BitMap["Gold"] = (new CBitBmp)->LoadBmp(L"../Texture/Item/Gold.bmp");
	m_BitMap["Gold2"] = (new CBitBmp)->LoadBmp(L"../Texture/Item/Gold2.bmp");
	m_BitMap["Gold3"] = (new CBitBmp)->LoadBmp(L"../Texture/Item/Gold3.bmp");
	m_BitMap["HPPotion"] = (new CBitBmp)->LoadBmp(L"../Texture/Item/HPPotion.bmp");
	m_BitMap["MPPotion"] = (new CBitBmp)->LoadBmp(L"../Texture/Item/MPPotion.bmp");

}

void CScene::SetEffect(CParent*	_Effect)
{
	m_vecParent[PAR_EFFECT].push_back(_Effect);
}

void CScene::ParentClear(void)
{
	for (int i = 0; i < PAR_END; ++i)
	{
		if (i != PAR_PLAYER)
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
}

CParent* CScene::GetPlayer(void)
{
	return m_vecParent[PAR_PLAYER].back();
}

void CScene::SetDropItem(CItem* _pItem)
{
	m_vecItem.push_back(_pItem);
}

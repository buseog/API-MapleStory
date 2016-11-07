#include "StdAfx.h"
#include "UiMgr.h"
#include "Factory.h"
#include "Inventory.h"
#include "Equipment.h"
#include "Status.h"
#include "QuickSlot.h"
#include "SkillPanel.h"
#include "KeyMgr.h"

#include "Weapon.h"
#include "Armor.h"
#include "Potion.h"

CUiMgr*	CUiMgr::m_pInstance;

CUiMgr::CUiMgr(void)
:m_dwKey(0)
,m_pUI(NULL)
{
}

CUiMgr::~CUiMgr(void)
{
	Release();
}

void	CUiMgr::Initialize(void)
{
	m_vecUI[UI_UI].push_back(CFactory<CUI>::CreateUI(WINCX / 2.f, WINCY / 2.f, "UI"));
	m_vecUI[UI_UI].push_back(CFactory<CUI>::CreateUI(250, 560, "HPBar"));
	m_vecUI[UI_UI].push_back(CFactory<CUI>::CreateUI(420, 560, "MPBar"));
	m_vecUI[UI_UI].push_back(CFactory<CUI>::CreateUI(250, 576, "EXPBar"));

	m_vecUI[UI_INVENTORY].push_back(CFactory<CInventory>::CreateUI(600.f, 300.f));
	m_vecUI[UI_EQUIPMENT].push_back(CFactory<CEquipment>::CreateUI(500.f, 300.f));
	m_vecUI[UI_SKILLPANEL].push_back(CFactory<CSkillPanel>::CreateUI(600.f, 400.f));
	m_vecUI[UI_QUICKSLOT].push_back(CFactory<CQuickSlot>::CreateUI(730.f, 490.f));
	m_vecUI[UI_STATUS].push_back(CFactory<CStatus>::CreateUI(400.f, 450.f));
}

void CUiMgr::Progress(DWORD _delta)
{
	KeyInput();
	UIDrag();


	for (int i = 0; i < UI_END; ++i)
	{
		for (size_t j = 0; j < m_vecUI[i].size(); ++j)
		{
			if (m_vecUI[i][j]->GetOnOff())
			{
				m_vecUI[i][j]->Progress(_delta);
			}
		}
	}
}

void CUiMgr::Render(HDC hdc)
{
	for (int i = 0; i < UI_END; ++i)
	{
		for (size_t j = 0; j < m_vecUI[i].size(); ++j)
		{
			if (m_vecUI[i][j]->GetOnOff())
			{
				m_vecUI[i][j]->Render(hdc);
			}
		}
	}
}

void CUiMgr::Release(void)
{
	for (int i = 0; i < UI_END; ++i)
	{
		for (size_t j = 0; j < m_vecUI[i].size(); ++j)
		{
			if (m_vecUI[i][j])
			{
				::Safe_Delete(m_vecUI[i][j]);
			}
		}
		m_vecUI[i].clear();
	}
}

void CUiMgr::KeyInput(void)
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

	//if (m_dwKey & KEY_Z)
	//{
	//	CCollisionMgr::CollisionItem(&m_vecParent[PAR_PLAYER], &m_vecItem, &m_vecUI[UI_INVENTORY]);
	//}
}

void CUiMgr::UIDrag(void)
{
	float fX = float(GetMouse().x - m_prevPT.x);
	float fY = float(GetMouse().y - m_prevPT.y);
	
	if(m_bDrag && m_pUI)
	{
		m_pUI->SetPos(m_pUI->GetInfo().fX + fX, m_pUI->GetInfo().fY + fY);
	}

	for (int i = 1; i < UI_QUICKSLOT; ++i)
	{
		if (m_vecUI[i].back()->GetOnOff())
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

	//m_vecUI[UI_INVENTORY].back()->UIPicking();
	//CItem* pDrop = ((CInventory*)m_vecUI[UI_INVENTORY].back())->GetDropItem();
	//if(pDrop)
	//{
	//	pDrop->SetPos(m_vecParent[PAR_PLAYER].back()->GetInfo().fX, m_vecParent[PAR_PLAYER].back()->GetInfo().fY - 20.f);
	//	m_vecItem.push_back(pDrop);
	//	((CInventory*)m_vecUI[UI_INVENTORY].back())->SetDropItem();
	//}

	//CItem* pSwap = m_vecUI[UI_INVENTORY].back()->GetReturnItem();
	//if(pSwap)
	//{
	//	if (pSwap->GetItem().iType == IT_POTION)
	//	{
	//		m_vecParent[PAR_PLAYER].back()->HavePotion(pSwap);
	//		m_vecUI[UI_INVENTORY].back()->SetReturnItem();
	//		::Safe_Delete(pSwap);
	//	}
	//	else
	//	{
	//		((CEquipment*)m_vecUI[UI_EQUIPMENT].back())->EquipItem(pSwap);
	//		m_vecUI[UI_INVENTORY].back()->SetReturnItem();
	//		pSwap = NULL;
	//	}
	//}

	//m_vecUI[UI_EQUIPMENT].back()->UIPicking();
	//CItem* pSwap2 = m_vecUI[UI_EQUIPMENT].back()->GetReturnItem();

	//if(pSwap2)
	//{
	//	((CInventory*)m_vecUI[UI_INVENTORY].back())->AddItem(pSwap2);
	//	m_vecUI[UI_EQUIPMENT].back()->SetReturnItem();
	//	pSwap2 = NULL;
	//}
}
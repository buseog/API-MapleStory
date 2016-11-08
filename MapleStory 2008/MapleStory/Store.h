#pragma once
#include "UI.h"
#include "Weapon.h"
#include "Armor.h"
#include "Potion.h"

class CItem;

class CStore	:
	public CUI
{
private:
	vector<CItem*>		m_vecItemList;
	CUI*				m_pInventory;
	bool				m_bDrag;
	POINT				m_prevPT;

public:
	void	SetInventory(CUI*	_pInventory);

public:
	virtual void UIPicking(void);
	virtual RECT GetRect(void);
	virtual void Initialize(void);
	virtual void Progress(DWORD _delta);
	virtual void Render(HDC hdc);
	virtual void Release(void);

public:
	CStore(void);
	CStore(string _strKey);
	~CStore(void);
};

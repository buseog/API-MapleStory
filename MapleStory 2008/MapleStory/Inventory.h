#pragma once
#include "Item.h"
#include "UI.h"

class CInventory	:
	public CUI
{
private:
	vector<CItem*>	m_vecItem;
	CItem*			m_pPick;
	int				m_iSwap;

private:
	void ItemPos(void);

public:
	void AddItem(CItem*	_pItem);

public:
	virtual void UIPicking(void);
	virtual RECT GetRect(void);
	virtual void Initialize(void);
	virtual void Progress(DWORD _delta);
	virtual void Render(HDC hdc);
	virtual void Release(void);

public:
	CInventory(void);
	CInventory(string _strKey);
	~CInventory(void);
};

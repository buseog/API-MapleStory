#pragma once
#include "Item.h"
#include "UI.h"

class CInventory	:
	public CUI
{
private:
	vector<CItem*>	m_vecItem;
	bool			m_bMouse;
	POINT			m_prevPT;

public:
	void AddItem(CItem*	_pItem);

public:
	virtual void Initialize(void);
	virtual void Progress(DWORD _delta);
	virtual void Render(HDC hdc);
	virtual void Release(void);

public:
	CInventory(void);
	CInventory(string _strKey);
	~CInventory(void);
};

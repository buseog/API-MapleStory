#pragma once
#include "Ui.h"
#include "Item.h"

class CEquipment	:
	public CUI
{
private:
	CItem*			m_pEquipItem[EQ_END];
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
	CEquipment(void);
	~CEquipment(void);
};

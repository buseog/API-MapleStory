#pragma once
#include "Ui.h"
#include "Item.h"

class CEquipment	:
	public CUI
{
private:
	CItem*			m_pEquipItem[EQ_END];

public:
	void EquipItem(CItem*	_pItem);
public:
	virtual RECT GetRect(void);
	virtual void Initialize(void);
	virtual void Progress(DWORD _delta);
	virtual void Render(HDC hdc);
	virtual void Release(void);

public:
	CEquipment(void);
	~CEquipment(void);
};

#pragma once
#include "Ui.h"

class CEquipment	:
	public CUI
{
public:
	virtual void Initialize(void);
	virtual void Progress(DWORD _delta);
	virtual void Render(HDC hdc);
	virtual void Release(void);

public:
	CEquipment(void);
	~CEquipment(void);
};

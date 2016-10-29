#pragma once
#include "UI.h"

class CInventory :
	public CUI
{
public:
	virtual void Initialize(void);
	virtual void Progress(void);
	virtual void Render(HDC hdc);
	virtual void Release(void);

public:
	CInventory(void);
	~CInventory(void);
};

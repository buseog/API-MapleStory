#pragma once
#include "ui.h"

class CQuickSlot :
	public CUI
{
public:
	virtual void Initialize(void);
	virtual void Progress(DWORD _delta);
	virtual void Render(HDC hdc);
	virtual void Release(void);

public:
	CQuickSlot(void);
	~CQuickSlot(void);
};

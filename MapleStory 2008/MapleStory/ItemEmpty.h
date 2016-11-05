#pragma once
#include "item.h"

class CItemEmpty :
	public CItem
{
public:
	virtual void Initialize(void);
	virtual void Progress(DWORD _delta);
	virtual void Render(HDC hdc);
	virtual void Release(void);

public:
	CItemEmpty(void);
	~CItemEmpty(void);
};

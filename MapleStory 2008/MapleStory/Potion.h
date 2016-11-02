#pragma once
#include "item.h"

class CPotion :
	public CItem
{
public:
	virtual void Initialize(void);
	virtual void Progress(DWORD _delta);
	virtual void Render(HDC hdc);
	virtual void Release(void);

public:
	CPotion(void);
	CPotion(string _strName, int _iOption, int _iCount, int _iPrice, int _iType);
	~CPotion(void);
};

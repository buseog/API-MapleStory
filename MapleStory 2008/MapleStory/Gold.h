#pragma once
#include "item.h"

class CGold :
	public CItem
{
public:
	virtual void Initialize(void);
	virtual void Progress(DWORD _delta);
	virtual void Render(HDC hdc);
	virtual void Release(void);
public:
	CGold(void);
	CGold(wstring _strName, int _iOption, int _iCount, int _iPrice, int _iType);
	~CGold(void);
};

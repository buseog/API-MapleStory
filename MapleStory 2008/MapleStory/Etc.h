#pragma once
#include "Item.h"

class CEtc	:
	public CItem
{
public:
	virtual void Initialize(void);
	virtual void Progress(DWORD _delta);
	virtual void Render(HDC hdc);
	virtual void Release(void);

public:
	CEtc(void);
	CEtc(wstring _strName, int _iOption, int _iCount, int _iPrice, int _iType);
	CEtc(const CItem &_Item);
	~CEtc(void);
};

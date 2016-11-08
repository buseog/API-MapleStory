#pragma once
#include "item.h"

class CArmor :
	public CItem
{
public:
	virtual void Initialize(void);
	virtual void Progress(DWORD _delta);
	virtual void Render(HDC hdc);
	virtual void Release(void);

public:
	CArmor(void);
	CArmor(wstring _strName, int _iOption, int _iCount, int _iPrice, int _iType);
	CArmor(const CItem &_Item);
	~CArmor(void);
};

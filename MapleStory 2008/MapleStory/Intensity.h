#pragma once
#include "Item.h"

class CIntensity	:
	public CItem
{
public:
	void	IntensityItem(CItem* _pItem);

public:
	virtual void Initialize(void);
	virtual void Progress(DWORD _delta);
	virtual void Render(HDC hdc);
	virtual void Release(void);


public:
	CIntensity(void);
	CIntensity(wstring _strName, int _iOption, int _iCount, int _iPrice, int _iType);
	CIntensity(const CItem &_Item);
	~CIntensity(void);
};

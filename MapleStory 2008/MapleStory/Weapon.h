#pragma once
#include "item.h"

class CWeapon :
	public CItem
{
public:
	virtual void Status(HDC hdc);
	virtual void Initialize(void);
	virtual void Progress(DWORD _delta);
	virtual void Render(HDC hdc);
	virtual void Release(void);

public:
	CWeapon(void);
	CWeapon(wstring _strName, int _iOption, int _iCount, int _iPrice, int _iType);
	CWeapon(const CItem &_Item);
	~CWeapon(void);
};

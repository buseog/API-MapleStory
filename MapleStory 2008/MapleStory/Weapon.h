#pragma once
#include "item.h"

class CWeapon :
	public CItem
{
public:
	virtual void Initialize(void);
	virtual void Progress(DWORD _delta);
	virtual void Render(HDC hdc);
	virtual void Release(void);

public:
	CWeapon(void);
	CWeapon(string _strName, int _iOption, int _iCount, int _iPrice, int _iType);
	~CWeapon(void);
};

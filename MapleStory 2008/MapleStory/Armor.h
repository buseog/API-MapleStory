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
	CArmor(string _strName, int _iAttack, int _iDeffense, int _iCount, int _iPrice, int _iType);
	~CArmor(void);
};

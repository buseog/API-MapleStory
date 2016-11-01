#pragma once
#include "bigheader.h"

class CItem
{
protected:
	ITEM	m_tItem;

public:
	virtual void Initialize(void)	PURE;
	virtual void Progress(DWORD _delta)		PURE;
	virtual void Render(HDC hdc)	PURE;
	virtual void Release(void)		PURE;

public:
	CItem(void);
	CItem(int _iAttack, int _iDeffense, int _iCount, int _iPrice, int _iType);
	virtual ~CItem(void);
};

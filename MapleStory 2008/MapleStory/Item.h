#pragma once
#include "bigheader.h"

class CItem
{
protected:
	INFO						m_tInfo;
	ITEM						m_tItem;
	DWORD						m_DrawId;

	static	map<string, CBitBmp*>*		m_pBitMap;

public:
	INFO	GetInfo(void);
	ITEM	GetItem(void);
	RECT	GetRect(void);
	DWORD	GetDraw(void);
	void	SetPos(float _fX, float _fY);
	static void SetBitMap(map<string, CBitBmp*>* _pBitMap);

public:
	virtual void Status(HDC hdc);
	virtual void Initialize(void)	PURE;
	virtual void Progress(DWORD _delta)		PURE;
	virtual void Render(HDC hdc)	PURE;
	virtual void Release(void)		PURE;

public:
	CItem(void);
	CItem(string _strName, int _iOption, int _iCount, int _iPrice, int _iType);
	virtual ~CItem(void);
};

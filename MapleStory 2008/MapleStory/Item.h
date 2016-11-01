#pragma once
#include "bigheader.h"

class CItem
{
protected:
	INFO						m_tInfo;
	ITEM						m_tItem;

	static	map<string, CBitBmp*>*		m_pBitMap;

public:
	INFO	GetInfo(void);
	ITEM	GetItem(void);
	void	SetPos(float _fX, float _fY);
	static void SetBitMap(map<string, CBitBmp*>* _pBitMap);

public:
	virtual void Initialize(void)	PURE;
	virtual void Progress(DWORD _delta)		PURE;
	virtual void Render(HDC hdc)	PURE;
	virtual void Release(void)		PURE;

public:
	CItem(void);
	CItem(string _strName, int _iAttack, int _iDeffense, int _iCount, int _iPrice, int _iType);
	virtual ~CItem(void);
};

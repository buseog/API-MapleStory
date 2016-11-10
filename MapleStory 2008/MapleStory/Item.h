#pragma once
#include "bigheader.h"
#include "Parent.h"

class CItem
{
protected:
	INFO						m_tInfo;
	ITEM						m_tItem;
	DWORD						m_DrawId;
	DWORD						m_DropId;
	int							m_iIntensity;

	static	map<string, CBitBmp*>*		m_pBitMap;

public:
	INFO	GetInfo(void);
	ITEM	GetItem(void);
	RECT	GetRect(void);
	DWORD	GetDraw(void);
	void	SetPos(float _fX, float _fY);
	void	SetDrawID(int _Draw);
	void	SetDropID(int _Draw);
	void	SetIntensity(int _iOption);
	static void SetBitMap(map<string, CBitBmp*>* _pBitMap);

public:
	virtual void Initialize(void)	PURE;
	virtual void Progress(DWORD _delta)		PURE;
	virtual void Render(HDC hdc)	PURE;
	virtual void Release(void)		PURE;

public:
	CItem(void);
	CItem(wstring _strName, int _iOption, int _iCount, int _iPrice, int _iType);
	CItem(const CItem &_Item);
	virtual ~CItem(void);
};

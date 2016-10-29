#pragma once
#include "Bigheader.h"

class CBitBmp;

class CParent
{
protected:
	INFO	m_tInfo;
	STAT	m_tStat;
	SPRITE	m_tSprite;
	float	m_fJpower;
	bool	m_bLand;
	int		m_iDrawID;

	DWORD	m_dwTime;
	DWORD	m_dwState;
	DWORD	m_dwKey;
	string	m_strKey;
	static  POINT m_ptScroll;
	static	map<string, CBitBmp*>*	m_pBitMap;

public:
	INFO	GetInfo(void);
	STAT	GetStat(void);
	SPRITE	GetSprite(void);
	RECT	GetRect(void);
	POINT	GetScroll(void);
	
public:
	static void SetBitMap(map<string, CBitBmp*>* _pBitMap);
	void	SetStrKey(string _strKey);
	void	Gravity(void);
	void	SetPos(float _fX, float _fY);

public:
	virtual void Initialize(void)	PURE;
	virtual void Progress(void)		PURE;
	virtual void Render(HDC hdc)	PURE;
	virtual void Release(void)		PURE;

public:
	CParent(void);
	CParent(float _fX, float _fY);
	virtual ~CParent(void);
};

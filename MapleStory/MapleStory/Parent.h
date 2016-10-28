#pragma once
#include "Bigheader.h"

class CBitBmp;

class CParent
{
protected:
	INFO	m_tInfo;
	STAT	m_tStat;
	float	m_fScrollX;
	float	m_fScrollY;
	float	m_fJpower;
	bool	m_bLand;
	int		m_iDrawID;

	string	m_BmpKey;
	static	map<string, CBitBmp*>*	m_pBitMap;

public:
	INFO	GetInfo(void);
	STAT	GetStat(void);
	RECT	GetRect(void);
	
public:
	static void SetBitMap(map<string, CBitBmp*>* _pBitMap);
	void	SetBmpKey(string _BmpKey);
	void	Gravity(void);
	void	SetPos(float _fX, float _fY);

public:
	virtual void Initialize(void)	PURE;
	virtual void Progress(void)		PURE;
	virtual void Render(HDC hdc)	PURE;
	virtual void Release(void)		PURE;

public:
	CParent(void);
	virtual ~CParent(void);
};

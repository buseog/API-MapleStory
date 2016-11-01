#pragma once
#include "Bigheader.h"
#include "Timer.h"


class CParent
{
protected:
	INFO	m_tInfo;
	STAT	m_tStat;
	SPRITE	m_tSprite;
	CTimer	m_cTimer;
	float	m_fJpower;
	float	m_fGravity;
	bool	m_bLand;
	bool	m_bDestroy;

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
	bool	GetDestroy(void);
	string	GetStrKey(void);
	float	GetJumpPower(void);
	void	SetLand(bool YN);
	void	SetDestroy(bool _YN);
	void	SetDamage(float _fDamage);
	
public:
	static void SetBitMap(map<string, CBitBmp*>* _pBitMap);
	void	SetScroll(void);
	void	SetStrKey(string _strKey);
	void	Gravity(void);
	void	SetPos(float _fX, float _fY);

public:
	virtual void Initialize(void)	PURE;
	virtual void Progress(DWORD _delta)		PURE;
	virtual void Render(HDC hdc)	PURE;
	virtual void Release(void)		PURE;

public:
	CParent(void);
	CParent(float _fX, float _fY);
	virtual ~CParent(void);
};

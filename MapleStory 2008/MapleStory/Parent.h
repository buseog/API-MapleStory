#pragma once
#include "Bigheader.h"
#include "Timer.h"

class CItem;

class CParent
{
protected:
	INFO	m_tInfo;
	STAT	m_tStat;
	SPRITE	m_tSprite;
	CTimer	m_cTimer;
	float	m_fJpower;
	float	m_fGravity;
	float	m_fOriginAttack;
	float	m_fOriginDefense;
	bool	m_bLand;
	bool	m_bDestroy;
	bool	m_bUnbeatable;

	DWORD	m_dwTime;
	DWORD	m_dwState;
	DWORD	m_dwKey;
	string	m_strKey;

	static	POINT					m_ptMapSize;
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
	DWORD	GetState(void);
	bool	GetUnbeatable(void);

public:
	void	SetMapSize(float _fX, float _fY);
	void	HavePotion(CItem* _pPotion);
	void	SetGold(int _iGold);
	void	SetLevel(void);
	void	SetExp(float _fExp);
	void	SetLand(bool YN);
	void	SetDestroy(bool _YN);
	void	SetUnbeatable(bool _YN);
	void	SetDamage(float _fDamage);
	void	SetState(DWORD _dwState);

	
public:
	static	void	SetBitMap(map<string, CBitBmp*>* _pBitMap);
	static	POINT	m_ptScroll;
	void	SetScroll(float _fX, float _fY);
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

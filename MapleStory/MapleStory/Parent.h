#pragma once
#include "define.h"

class CParent
{
protected:
	INFO	m_tInfo;
	STAT	m_tStat;
	float	m_fScrollX;
	float	m_fScrollY;
	bool	m_bLand;
	float	m_fJpower;
public:
	INFO	GetInfo(void);
	STAT	GetStat(void);
	void	SetPos(float _fX, float _fY);
	void	Gravity(void);
public:
	virtual void Initialize(void)	PURE;
	virtual void Progress(void)		PURE;
	virtual void Render(HDC hdc)	PURE;
	virtual void Release(void)		PURE;

public:
	CParent(void);
	virtual ~CParent(void);
};

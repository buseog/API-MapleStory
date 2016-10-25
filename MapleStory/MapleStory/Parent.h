#pragma once
#include "define.h"

class CParent
{
private:
	INFO	m_tInfo;
	STAT	m_tStat;

public:
	INFO	GetInfo(void);
	STAT	GetStat(void);
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

#pragma once
#include "Parent.h"

class CSkill	:
	public CParent
{
private:
	bool	m_bHit;
	int		m_iHitCount;
	float	m_fTime;

public:
	void	SetDamage(float _fDamage);
	void	SetHit(bool _YN);
	bool	GetHit(void);
	void	SetHitCount(void);
	int		GetHitCount(void);
	float	GetCoolTime(void);

public:
	virtual void Initialize(void);
	virtual void Progress(DWORD _delta);
	virtual void Render(HDC hdc);
	virtual void Release(void);

public:
	CSkill();
	~CSkill();
};


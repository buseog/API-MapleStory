#pragma once
#include "effect.h"

class CDamageEffect :
	public CEffect
{
private:
	int			m_iDamage;
	int			m_iPrintDamage[5];

public:
	void	SetDamage(int _Damage);

public:
	virtual void Initialize(void);
	virtual void Progress(DWORD _delta);
	virtual void Render(HDC hdc);
	virtual void Release(void);

public:
	CDamageEffect(void);
	~CDamageEffect(void);
};

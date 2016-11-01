#pragma once
#include "effect.h"

class CDamageEffect :
	public CEffect
{
private:
	int		m_iNumber;

public:
	virtual void Initialize(void);
	virtual void Progress(DWORD _delta);
	virtual void Render(HDC hdc);
	virtual void Release(void);

public:
	CDamageEffect(void);
	~CDamageEffect(void);
};

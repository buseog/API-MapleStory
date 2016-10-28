#pragma once
#include "Parent.h"

class CMyButton	:
	public CParent
{
private:
	int		m_iButton;

public:
	int		GetSelect(void);

public:
	virtual void Initialize(void);
	virtual void Progress(void);
	virtual void Render(HDC hdc);
	virtual void Release(void);

public:
	CMyButton(void);
	~CMyButton(void);
};

#pragma once
#include "Parent.h"

class CUI	:
	public CParent
{
private:
	int		m_iDrawID;
	int		m_iButton;

public:
	virtual void Initialize(void);
	virtual void Progress(void);
	virtual void Render(HDC hdc);
	virtual void Release(void);

public:
	CUI(void);
	~CUI(void);
};

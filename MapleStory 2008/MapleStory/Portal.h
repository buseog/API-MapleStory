#pragma once
#include "Ui.h"

class CPortal	:
	public CUI
{
private:
	int		m_iButton;

public:
	int		GetSelect(void);

public:
	virtual void Initialize(void);
	virtual void Progress(DWORD _delta);
	virtual void Render(HDC hdc);
	virtual void Release(void);

public:
	CPortal(void);
	CPortal(string _strKey);
	~CPortal(void);
};

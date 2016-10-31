#pragma once
#include "UI.h"

class CMyButton	:
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
	CMyButton(void);
	CMyButton(string _strKey);
	~CMyButton(void);
};

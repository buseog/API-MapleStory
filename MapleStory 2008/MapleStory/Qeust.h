#pragma once
#include "ui.h"

class CQeust :
	public CUI
{
private:
	TCHAR szName[128];

private:
	void	QeustStart(void);

public:
	virtual void UIPicking(void);
	virtual RECT GetRect(void);
	virtual void Initialize(void);
	virtual void Progress(DWORD _delta);
	virtual void Render(HDC hdc);
	virtual void Release(void);

public:
	CQeust(void);
	CQeust(string _strKey);
	~CQeust(void);
};

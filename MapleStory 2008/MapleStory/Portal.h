#pragma once
#include "Parent.h"

class CPortal	:
	public CParent
{
private:
	int		m_iPortal;

public:
	void		SetPortal(int _iPortal);
	SCENEID		GetPortal(void);

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

#pragma once
#include "Parent.h"

class CPet	:
	public CParent
{
public:
	virtual void Initialize(void);
	virtual void Progress(DWORD _delta);
	virtual void Render(HDC hdc);
	virtual void Release(void);

public:
	CPet(void);
	~CPet(void);
};

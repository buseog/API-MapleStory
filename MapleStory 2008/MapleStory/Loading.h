#pragma once
#include "Parent.h"

class CLoading	:
	public CParent
{
public:
	virtual void Initialize(void);
	virtual void Progress(DWORD _delta);
	virtual void Render(HDC hdc);
	virtual void Release(void);

public:
	CLoading(void);
	~CLoading(void);
};

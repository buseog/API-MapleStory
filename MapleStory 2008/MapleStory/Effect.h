#pragma once
#include "parent.h"

class CEffect :
	public CParent
{
public:
	virtual void Initialize(void);
	virtual void Progress(DWORD _delta);
	virtual void Render(HDC hdc);
	virtual void Release(void);

public:
	CEffect(void);
	~CEffect(void);
};

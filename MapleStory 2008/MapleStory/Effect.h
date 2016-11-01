#pragma once
#include "parent.h"

class CEffect :
	public CParent
{
public:
	virtual void Initialize(void)		PURE;
	virtual void Progress(DWORD _delta)	PURE;
	virtual void Render(HDC hdc)		PURE;
	virtual void Release(void)			PURE;

public:
	CEffect(void);
	~CEffect(void);
};

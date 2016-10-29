#pragma once
#include "Parent.h"

class CUI	:
	public CParent
{
public:
	virtual void Initialize(void);
	virtual void Progress(void);
	virtual void Render(HDC hdc);
	virtual void Release(void);

public:
	CUI(void);
	~CUI(void);
};

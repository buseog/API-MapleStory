#pragma once
#include "parent.h"

class CMonster :
	public CParent
{
public:
	virtual void Initialize(void);
	virtual void Progress(void);
	virtual void Render(HDC hdc);
	virtual void Release(void);

public:
	CMonster(void);
	~CMonster(void);
};

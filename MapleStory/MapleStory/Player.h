#pragma once
#include "Parent.h"

class CPlayer:
	public CParent
{
public:
	void KeyInput(void);

public:
	virtual void Initialize(void);
	virtual void Progress(void);
	virtual void Render(HDC hdc);
	virtual void Release(void);

public:
	CPlayer(void);
	~CPlayer(void);
};

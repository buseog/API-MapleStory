#pragma once
#include "scene.h"

class CCreate :
	public CScene
{
public:
	virtual void Initialize(void);
	virtual void Progress(DWORD _delta);
	virtual void Render(HDC hdc);
	virtual void Release(void);

public:
	CCreate(void);
	~CCreate(void);
};

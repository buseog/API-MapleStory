#pragma once
#include "Scene.h"

class CCreate	:
	public CScene
{
public:
	virtual void Initialize(void);
	virtual void Progress(void);
	virtual void Render(HDC hdc);
	virtual void Release(void);

public:
	CCreate(void);
	~CCreate(void);
};

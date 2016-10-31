#pragma once
#include "Scene.h"

class CParent;

class CVillage	:
	public CScene
{
public:
	virtual void Initialize(void);
	virtual void Progress(DWORD _delta);
	virtual void Render(HDC hdc);
	virtual void Release(void);

public:
	CVillage(void);
	~CVillage(void);
};

#pragma once
#include "Scene.h"

class CBossField	:
	public CScene
{
public:
	virtual void Initialize(void);
	virtual void Progress(void);
	virtual void Render(HDC hdc);
	virtual void Release(void);

public:
	CBossField(void);
	~CBossField(void);
};

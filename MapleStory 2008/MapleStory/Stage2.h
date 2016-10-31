#pragma once
#include "Scene.h"

class CStage2	:
	public CScene
{
public:
	virtual void Initialize(void);
	virtual void Progress(DWORD _delta);
	virtual void Render(HDC hdc);
	virtual void Release(void);

public:
	CStage2(void);
	~CStage2(void);
};

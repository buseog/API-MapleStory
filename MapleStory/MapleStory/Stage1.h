#pragma once
#include "Scene.h"

class CParent;

class CStage1	:
	public CScene
{
private:
	CParent*	m_pEdit;

public:
	virtual void Initialize(void);
	virtual void Progress(void);
	virtual void Render(HDC hdc);
	virtual void Release(void);

public:
	CStage1(void);
	~CStage1(void);
};

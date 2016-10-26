#pragma once
#include "Scene.h"

class CParent;

class CStage2	:
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
	CStage2(void);
	~CStage2(void);
};

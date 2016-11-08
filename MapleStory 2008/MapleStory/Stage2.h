#pragma once
#include "Scene.h"

class CStage2	:
	public CScene
{
private:
	void	Regen(void);
	float	m_fRegenTime;

public:
	virtual void Initialize(void);
	virtual void Progress(DWORD _delta);
	virtual void Render(HDC hdc);
	virtual void Release(void);

public:
	CStage2(void);
	~CStage2(void);
};

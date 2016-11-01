#pragma once
#include "Scene.h"

class CStart	:
	public CScene
{
private:
	HWND	m_hVideo;

public:
	virtual void Initialize(void);
	virtual void  Progress(DWORD _delta);
	virtual void Render(HDC hdc);
	virtual void Release(void);

public:
	CStart(void);
	~CStart(void);
};

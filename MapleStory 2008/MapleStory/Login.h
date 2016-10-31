#pragma once
#include "Scene.h"

class CUI;

class CLogin	:
	public CScene
{
private:
	CUI* CreateButton(float _fX, float _fY, string _StrKey);

public:
	virtual void Initialize(void);
	virtual void Progress(DWORD _delta);
	virtual void Render(HDC hdc);
	virtual void Release(void);

public:
	CLogin(void);
	~CLogin(void);
};

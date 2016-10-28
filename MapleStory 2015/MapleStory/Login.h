#pragma once
#include "Scene.h"

class CParent;

class CLogin	:
	public CScene
{
private:
	vector<CParent*>	m_vecButton;

private:
	CParent* CreateButton(float _fX, float _fY, string _StrKey);

public:
	virtual void Initialize(void);
	virtual void Progress(void);
	virtual void Render(HDC hdc);
	virtual void Release(void);

public:
	CLogin(void);
	~CLogin(void);
};

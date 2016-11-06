#pragma once
#include "scene.h"

class CCreate :
	public CScene
{
private:
	vector<CUI*>	m_vecButton;
	CUI* CreateButton(float _fX, float _fY, string _StrKey);

public:
	virtual void Initialize(void);
	virtual void Progress(DWORD _delta);
	virtual void Render(HDC hdc);
	virtual void Release(void);

public:
	CCreate(void);
	~CCreate(void);
};

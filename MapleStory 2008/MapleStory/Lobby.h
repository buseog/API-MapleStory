#pragma once
#include "Scene.h"

class CLobby	:
	public CScene
{
private:
	vector<CUI*>	m_vecButton;
	SPRITE			m_tSprite[2];
	bool			m_bPick;
	int				m_iPick;

private:
	CUI* CreateButton(float _fX, float _fY, string _StrKey);

public:
	virtual void Initialize(void);
	virtual void Progress(DWORD _delta);
	virtual void Render(HDC hdc);
	virtual void Release(void);

public:
	CLobby(void);
	~CLobby(void);
};

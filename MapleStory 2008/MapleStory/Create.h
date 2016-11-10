#pragma once
#include "scene.h"

class CCreate :
	public CScene
{
private:
	vector<CUI*>	m_vecButton;
	SPRITE			m_tSprite;
	bool			m_bPick;
	SPRITE			m_tSprite1;
	SPRITE			m_tSprite2;
	INFO			m_tInfo[2];
	int				m_iPick;
	DWORD			m_dwTime2;

private:
	CUI* CreateButton(float _fX, float _fY, string _StrKey);
	void	UIPicking(DWORD _delta);

public:
	virtual void Initialize(void);
	virtual void Progress(DWORD _delta);
	virtual void Render(HDC hdc);
	virtual void Release(void);

public:
	CCreate(void);
	~CCreate(void);
};

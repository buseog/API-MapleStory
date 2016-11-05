#pragma once
#include "ui.h"

class CParent;

class CStatus :
	public CUI
{
private:
	CParent*	m_pPlayer;

public:
	void	SetPlayer(CParent* _pPlayer);

public:
	virtual void UIPicking(void);
	virtual RECT GetRect(void);
	virtual void Initialize(void);
	virtual void Progress(DWORD _delta);
	virtual void Render(HDC hdc);
	virtual void Release(void);

public:
	CStatus(void);
	~CStatus(void);
};

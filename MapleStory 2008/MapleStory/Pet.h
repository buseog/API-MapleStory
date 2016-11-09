#pragma once
#include "Parent.h"

class CPet	:
	public CParent
{
private:
	CParent*	m_pPlayer;

private:
	void	SetState(DWORD _dwState, int _iLast, int _iMotion, DWORD _dwTime);
	void	KeyInput(void);

public:
	void	SetPlayer(CParent*	_pPlayer);

public:
	virtual void Initialize(void);
	virtual void Progress(DWORD _delta);
	virtual void Render(HDC hdc);
	virtual void Release(void);

public:
	CPet(void);
	~CPet(void);
};

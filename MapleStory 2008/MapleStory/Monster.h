#pragma once
#include "parent.h"

class CMonster :
	public CParent
{
private:
	DWORD	m_dwDrop;

private:
	void SetState(DWORD _dwState, int _iLast, int _iMotion, DWORD _dwTime);

public:
	void	SetDrop(int _dwDrop);
	DWORD	GetDrop(void);
	CItem*	GetDropItem(void);

public:
	virtual void Initialize(void);
	virtual void Progress(DWORD _delta);
	virtual void Render(HDC hdc);
	virtual void Release(void);

public:
	CMonster(void);
	~CMonster(void);
};

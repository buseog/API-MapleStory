#pragma once
#include "parent.h"

class CBoss :
	public CParent
{
private:
	void SetState(DWORD _dwState, int _iLast, int _iMotion, DWORD _dwTime);

public:
	virtual void Initialize(void);
	virtual void Progress(DWORD _delta);
	virtual void Render(HDC hdc);
	virtual void Release(void);

public:
	CBoss(void);
	~CBoss(void);
};

#pragma once
#include "define.h"
#include "Parent.h"

class CScene
{
protected:
	CParent*	m_pEdit;
	CParent*	m_pPlayer;

public:
	void	SetPlayer(CParent*	_pPlayer);
public:
	virtual void Initialize(void)	PURE;
	virtual void Progress(void)		PURE;
	virtual void Render(HDC hdc)	PURE;
	virtual void Release(void)		PURE;

public:
	CScene(void);
	virtual ~CScene(void);
};

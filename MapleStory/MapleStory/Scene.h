#pragma once
#include "define.h"
#include "Parent.h"

class CScene
{
protected:
	map<string, CBitBmp*>	m_BitMap;
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

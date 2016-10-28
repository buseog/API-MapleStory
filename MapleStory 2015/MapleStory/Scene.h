#pragma once
#include "bigheader.h"
#include "Parent.h"

class CScene
{
protected:
	map<string, CBitBmp*>	m_BitMap;
	static	vector<CParent*>	m_vecParent[OBJ_END];

public:
	virtual void Initialize(void)	PURE;
	virtual void Progress(void)		PURE;
	virtual void Render(HDC hdc)	PURE;
	virtual void Release(void)		PURE;

public:
	CScene(void);
	virtual ~CScene(void);
};
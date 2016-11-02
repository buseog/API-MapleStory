#pragma once
#include "bigheader.h"
#include "UI.h"

class CUI;
class CParent;

class CScene
{
protected:
	map<string, CBitBmp*>		m_BitMap;
	vector<TILE*>				m_vecTile;
	vector<CUI*>				m_vecUI;
	string						m_strKey;
	vector<CParent*>			m_vecPortal;
	static	vector<CParent*>	m_vecParent[PAR_END];

protected:
	void	ParentClear(void);
	void	LoadMap(void);
	void	LoadBmp(void);

public:
	static void SetEffect(CParent* _Effect);

public:
	virtual void Initialize(void)	PURE;
	virtual void Progress(DWORD _delta)		PURE;
	virtual void Render(HDC hdc)	PURE;
	virtual void Release(void)		PURE;

public:
	CScene(void);
	virtual ~CScene(void);
};

#pragma once
#include "bigheader.h"
#include "UI.h"
#include "Inventory.h"
#include "Equipment.h"
#include "SkillPanel.h"
#include "QuickSlot.h"
#include "Item.h"
#include "Loading.h"

class CUI;
class CParent;

class CScene
{
protected:
	DWORD						m_dwKey;
	CLoading*					m_pLoading;
	map<string, CBitBmp*>		m_BitMap;
	vector<TILE*>				m_vecTile;
	string						m_strKey;
	vector<CParent*>			m_vecPortal;

protected:
	static	CUI*				m_pUI;
	static	bool				m_bMouse;
	static	POINT				m_prevPT;
	static	bool				m_bUIView[UI_END];
	static	vector<CUI*>		m_vecUI[UI_END];
	static	vector<CParent*>	m_vecParent[PAR_END];

protected:
	void	UIDrag(void);
	void	KeyInput(void);
	void	ParentClear(void);
	void	LoadMap(void);
	void	LoadBmp(void);

public:
	CParent*	GetPlayer(void);
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

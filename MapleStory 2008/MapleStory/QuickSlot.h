#pragma once
#include "ui.h"
#include "Icon.h"

class CQuickSlot :
	public CUI
{
private:
	bool			m_bExpress;
	CUI*			m_pPanel;
	vector<CIcon*>	m_vecSlot;
	vector<CIcon*>	m_vecCool;
	CIcon*			m_pPick;
	float			m_fCoolTime[8];

public:
	void	SetPanel(CUI*	_pPanel);
	void	SetExpress(void);
	void	IconPos(void);
	void	SetCooltime(int _iNum, float _fCool);
	void	SetSkillOff(void);
	vector<CIcon*>*	GetSlot(void);

public:
	virtual void UIPicking(void);
	virtual RECT GetRect(void);
	virtual void Initialize(void);
	virtual void Progress(DWORD _delta);
	virtual void Render(HDC hdc);
	virtual void Release(void);

public:
	CQuickSlot(void);
	~CQuickSlot(void);
};

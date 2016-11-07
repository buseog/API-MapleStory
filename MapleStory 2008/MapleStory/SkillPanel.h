#pragma once
#include "Ui.h"
#include "Icon.h"

class CSkillPanel	:
	public CUI
{
private:
	CIcon*	m_pIcon[SKILLPANELSLOT];
	CIcon*	m_pPick;

public:
	CIcon*	GetPickIcon(void);
	void	SetPickIcon(void);

public:
	virtual void UIPicking(void);
	virtual RECT GetRect(void);
	virtual void Initialize(void);
	virtual void Progress(DWORD _delta);
	virtual void Render(HDC hdc);
	virtual void Release(void);

public:
	CSkillPanel(void);
	~CSkillPanel(void);
};

#pragma once
#include "Ui.h"

class CSkillPanel	:
	public CUI
{
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

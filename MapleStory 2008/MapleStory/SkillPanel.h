#pragma once
#include "Ui.h"

class CSkillPanel	:
	public CUI
{
private:
	bool			m_bMouse;
	POINT			m_prevPT;

public:
	virtual void Initialize(void);
	virtual void Progress(DWORD _delta);
	virtual void Render(HDC hdc);
	virtual void Release(void);

public:
	CSkillPanel(void);
	~CSkillPanel(void);
};

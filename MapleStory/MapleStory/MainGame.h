#pragma once
#include "define.h"
#include "MapEdit.h"

class CParent;

class CMainGame
{
private:
	HDC		m_hdc;
	CParent*	m_pMapEdit;

public:
	void Initialize(void);
	void Progress(void);
	void Render(void);
	void Release(void);
public:
	CMainGame(void);
	~CMainGame(void);
};

#pragma once
#include "define.h"
#include "MapEdit.h"

class CParent;
class CSceneMgr;

class CMainGame
{
private:
	HDC		m_hdc;
	CSceneMgr*	m_pSceneMgr;

public:
	void Initialize(void);
	void Progress(void);
	void Render(void);
	void Release(void);
public:
	CMainGame(void);
	~CMainGame(void);
};
